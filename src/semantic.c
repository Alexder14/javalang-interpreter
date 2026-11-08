#include "semantic.h"
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* ========================================================================
 * Analizador semántico de JavaLang
 *
 * Valida declaraciones, tipos (incluyendo arreglos de N dimensiones), ámbitos,
 * constantes (final), llamadas a funciones y sentencias de control.
 * Cada expresión se tipa con un par (tipo base, dimensiones): int -> (INT, 0),
 * int[][] -> (INT, 2).
 * ===================================================================== */

#define MAX_ARGS 64

static SemanticAnalyzer *global_analyzer = NULL;
static bool is_builtin_function(const char *name);
int block_counter = 0;

static bool expr(SemanticAnalyzer *an, ASTNode *n, DataType *t, int *dims);

/* ------------------------------------------------------------------------
 * Utilidades
 * --------------------------------------------------------------------- */

static bool num_like(DataType t) { return is_numeric_type(t) || t == TYPE_CHAR; }

/* "int", "int[]", "int[][]" (4 búferes rotativos para poder usarlo varias veces en un printf) */
static const char *type_str(DataType t, int dims) {
    static char bufs[4][64];
    static int k = 0;
    char *b = bufs[k++ % 4];
    snprintf(b, 64, "%s", data_type_to_string(t));
    for (int i = 0; i < dims && strlen(b) < 58; i++) strcat(b, "[]");
    return b;
}

static char *scope_root(const char *scope) {
    char *s = strdup(scope && *scope ? scope : "Global");
    char *slash = strchr(s, '/');
    if (slash) *slash = '\0';
    return s;
}

/* ------------------------------------------------------------------------
 * Creación y destrucción
 * --------------------------------------------------------------------- */

SemanticAnalyzer* create_semantic_analyzer() {
    SemanticAnalyzer *analyzer = malloc(sizeof(SemanticAnalyzer));
    if (!analyzer) {
        fprintf(stderr, "Error: No se pudo crear el analizador semántico\n");
        exit(1);
    }

    analyzer->symbol_table = NULL;
    analyzer->current_scope = strdup("Global");
    analyzer->scope_level = 0;
    analyzer->current_function = NULL;
    analyzer->errors = NULL;
    analyzer->error_count = 0;
    analyzer->in_loop = false;
    analyzer->in_function = false;
    analyzer->in_switch = false;
    block_counter = 0;  // numeración de bloques por análisis

    global_analyzer = analyzer;
    return analyzer;
}

void destroy_semantic_analyzer(SemanticAnalyzer *analyzer) {
    if (!analyzer) return;

    Symbol *current = analyzer->symbol_table;
    while (current) {
        Symbol *next = current->next;
        free(current->id);
        free(current->scope);
        free(current);
        current = next;
    }

    SemanticError *error = analyzer->errors;
    while (error) {
        SemanticError *next = error->next;
        free(error->message);
        free(error->context);
        free(error->scope);
        free(error);
        error = next;
    }

    free(analyzer->current_scope);
    free(analyzer);
}

Symbol* create_symbol(const char *id, SymbolType type, DataType data_type,
                     const char *scope, int line, int col) {
    Symbol *symbol = malloc(sizeof(Symbol));
    if (!symbol) {
        fprintf(stderr, "Error: No se pudo crear símbolo\n");
        exit(1);
    }

    symbol->id = strdup(id);
    symbol->symbol_type = type;
    symbol->data_type = data_type;
    symbol->scope = strdup(scope);
    symbol->line = line;
    symbol->column = col;
    symbol->is_initialized = false;
    symbol->is_array = false;
    symbol->array_size = 0;
    symbol->dims = 0;
    symbol->is_const = false;
    symbol->decl = NULL;
    symbol->parameters = NULL;
    symbol->value = NULL;
    symbol->next = NULL;

    return symbol;
}

/* ------------------------------------------------------------------------
 * Tabla de símbolos con ámbitos jerárquicos ("main/bloque1/bloque2")
 * --------------------------------------------------------------------- */

// Busca en el ámbito actual, luego en los padres y por último en Global
Symbol* lookup_symbol(SemanticAnalyzer *analyzer, const char *id) {
    char *scope = strdup(analyzer->current_scope);
    while (1) {
        for (Symbol *cur = analyzer->symbol_table; cur; cur = cur->next) {
            if (strcmp(cur->id, id) == 0 && strcmp(cur->scope, scope) == 0) {
                free(scope);
                return cur;
            }
        }
        char *slash = strrchr(scope, '/');
        if (!slash) break;
        *slash = '\0';
    }
    free(scope);

    for (Symbol *cur = analyzer->symbol_table; cur; cur = cur->next) {
        if (strcmp(cur->id, id) == 0 && strcmp(cur->scope, "Global") == 0) {
            return cur;
        }
    }
    return NULL;
}

bool add_symbol(SemanticAnalyzer *analyzer, Symbol *symbol) {
    Symbol *existing = lookup_symbol(analyzer, symbol->id);
    if (existing && strcmp(existing->scope, symbol->scope) == 0) {
        add_semantic_error(analyzer, "Ya existe una declaración con ese nombre en este ámbito",
                          symbol->id, symbol->line, symbol->column);
        return false;
    }

    symbol->next = analyzer->symbol_table;
    analyzer->symbol_table = symbol;
    return true;
}

void add_semantic_error(SemanticAnalyzer *analyzer, const char *message,
                       const char *context, int line, int col) {
    SemanticError *error = malloc(sizeof(SemanticError));
    if (!error) return;

    error->message = strdup(message);
    error->context = strdup(context ? context : "");
    error->scope = scope_root(analyzer->current_scope);
    error->line = line;
    error->column = col;
    error->next = analyzer->errors;

    analyzer->errors = error;
    analyzer->error_count++;
}

// Error con mensaje formateado en la posición de un nodo
static void sem_err(SemanticAnalyzer *an, ASTNode *n, const char *fmt, ...) {
    char msg[512];
    va_list ap;
    va_start(ap, fmt);
    vsnprintf(msg, sizeof msg, fmt, ap);
    va_end(ap);
    add_semantic_error(an, msg, "", n ? n->line : 0, n ? n->column : 0);
}

void enter_scope(SemanticAnalyzer *analyzer, const char *scope_name) {
    char *new_scope;
    if (strcmp(analyzer->current_scope, "Global") == 0) {
        new_scope = strdup(scope_name);
    } else {
        size_t len = strlen(analyzer->current_scope) + strlen(scope_name) + 2;
        new_scope = malloc(len);
        snprintf(new_scope, len, "%s/%s", analyzer->current_scope, scope_name);
    }
    free(analyzer->current_scope);
    analyzer->current_scope = new_scope;
    analyzer->scope_level++;
}

void exit_scope(SemanticAnalyzer *analyzer) {
    if (analyzer->scope_level > 0) analyzer->scope_level--;
    char *slash = strrchr(analyzer->current_scope, '/');
    if (slash) {
        *slash = '\0';
    } else {
        free(analyzer->current_scope);
        analyzer->current_scope = strdup("Global");
    }
}

static void enter_block_scope(SemanticAnalyzer *analyzer) {
    char name[32];
    snprintf(name, sizeof(name), "bloque%d", ++block_counter);
    enter_scope(analyzer, name);
}

/* ------------------------------------------------------------------------
 * Reglas de tipos
 * --------------------------------------------------------------------- */

// Conversiones implícitas (widening): char -> int -> float -> double
bool is_compatible_types(DataType type1, DataType type2) {
    if (type1 == type2) return true;
    if (type1 == TYPE_INT && type2 == TYPE_CHAR) return true;
    if (type1 == TYPE_FLOAT && (type2 == TYPE_INT || type2 == TYPE_CHAR)) return true;
    if (type1 == TYPE_DOUBLE && (type2 == TYPE_INT || type2 == TYPE_FLOAT || type2 == TYPE_CHAR)) return true;
    return false;
}

// ¿Se puede asignar un valor (st, sd) a un destino (dt, dd)?
static bool assignable(DataType dt, int dd, DataType st, int sd) {
    if (st == TYPE_UNKNOWN || dt == TYPE_UNKNOWN) return true;   // evita errores en cascada
    if (st == TYPE_NULL) return dd > 0 || dt == TYPE_STRING;
    if (dd != sd) return false;
    if (dd > 0) return dt == st;                                 // arreglos: mismo tipo base exacto
    if (dt == TYPE_VOID || st == TYPE_VOID) return false;
    return is_compatible_types(dt, st);
}

DataType get_binary_operation_result_type(const char *op, DataType l, DataType r) {
    if (l == TYPE_VOID || r == TYPE_VOID || l == TYPE_UNKNOWN || r == TYPE_UNKNOWN) return TYPE_UNKNOWN;
    bool ln = num_like(l), rn = num_like(r);

    // Concatenación: String + cualquier tipo
    if (strcmp(op, "+") == 0 && (l == TYPE_STRING || r == TYPE_STRING)) return TYPE_STRING;

    if (strcmp(op, "+") == 0 || strcmp(op, "-") == 0 || strcmp(op, "*") == 0 ||
        strcmp(op, "/") == 0 || strcmp(op, "%") == 0) {
        if (ln && rn) {
            if (l == TYPE_DOUBLE || r == TYPE_DOUBLE) return TYPE_DOUBLE;
            if (l == TYPE_FLOAT || r == TYPE_FLOAT) return TYPE_FLOAT;
            return TYPE_INT;
        }
        return TYPE_UNKNOWN;
    }

    // Igualdad: solo entre expresiones del mismo tipo (o numéricas entre sí)
    if (strcmp(op, "==") == 0 || strcmp(op, "!=") == 0) {
        if (ln && rn) return TYPE_BOOLEAN;
        if (l == r) return TYPE_BOOLEAN;
        if ((l == TYPE_NULL && r == TYPE_STRING) || (r == TYPE_NULL && l == TYPE_STRING)) return TYPE_BOOLEAN;
        return TYPE_UNKNOWN;
    }

    // Relacionales: solo numéricos o caracteres
    if (strcmp(op, "<") == 0 || strcmp(op, "<=") == 0 || strcmp(op, ">") == 0 || strcmp(op, ">=") == 0) {
        return (ln && rn) ? TYPE_BOOLEAN : TYPE_UNKNOWN;
    }

    if (strcmp(op, "&&") == 0 || strcmp(op, "||") == 0) {
        return (l == TYPE_BOOLEAN && r == TYPE_BOOLEAN) ? TYPE_BOOLEAN : TYPE_UNKNOWN;
    }

    if (strcmp(op, "&") == 0 || strcmp(op, "|") == 0 || strcmp(op, "^") == 0) {
        if (l == TYPE_BOOLEAN && r == TYPE_BOOLEAN) return TYPE_BOOLEAN;
        if ((l == TYPE_INT || l == TYPE_CHAR) && (r == TYPE_INT || r == TYPE_CHAR)) return TYPE_INT;
        return TYPE_UNKNOWN;
    }

    if (strcmp(op, "<<") == 0 || strcmp(op, ">>") == 0) {
        if ((l == TYPE_INT || l == TYPE_CHAR) && (r == TYPE_INT || r == TYPE_CHAR)) return TYPE_INT;
        return TYPE_UNKNOWN;
    }

    return TYPE_UNKNOWN;
}

/* ------------------------------------------------------------------------
 * Funciones integradas
 * --------------------------------------------------------------------- */

static bool is_builtin_function(const char *name) {
    static const char *builtins[] = {"println", "print", "System.out.println", "System.out.print",
                                     "Integer.parseInt", "Float.parseFloat", "Double.parseDouble",
                                     "String.valueOf", "String.join", "Arrays.indexOf", NULL};
    for (int i = 0; builtins[i]; i++)
        if (strcmp(builtins[i], name) == 0) return true;
    return false;
}

// Reúne los argumentos de una llamada (lista, expresión suelta o ninguno)
static int collect_args(ASTNode *args, ASTNode **out) {
    if (!args) return 0;
    if (args->type == NODE_LIST) {
        int n = args->data.list.count < MAX_ARGS ? args->data.list.count : MAX_ARGS;
        for (int i = 0; i < n; i++) out[i] = args->data.list.items[i];
        return n;
    }
    out[0] = args;
    return 1;
}

// Analiza una llamada a función y devuelve su tipo
static bool call_expr(SemanticAnalyzer *an, ASTNode *node, DataType *t, int *dims) {
    const char *name = node->data.func_call.name;
    ASTNode *args[MAX_ARGS];
    int argc = collect_args(node->data.func_call.arguments, args);
    DataType at[MAX_ARGS];
    int ad[MAX_ARGS];
    bool ok = true;
    *dims = 0;
    *t = TYPE_UNKNOWN;

    for (int i = 0; i < argc; i++) {
        if (!expr(an, args[i], &at[i], &ad[i])) { ok = false; at[i] = TYPE_UNKNOWN; ad[i] = 0; }
    }

    if (is_builtin_function(name)) {
        if (!strcmp(name, "println") || !strcmp(name, "print") ||
            !strcmp(name, "System.out.println") || !strcmp(name, "System.out.print")) {
            *t = TYPE_VOID;
            return ok;
        }
        if (!strcmp(name, "Integer.parseInt") || !strcmp(name, "Float.parseFloat") ||
            !strcmp(name, "Double.parseDouble")) {
            *t = name[0] == 'I' ? TYPE_INT : (name[0] == 'F' ? TYPE_FLOAT : TYPE_DOUBLE);
            if (argc != 1) { sem_err(an, node, "%s espera 1 argumento y recibió %d", name, argc); return false; }
            if (ok && (at[0] != TYPE_STRING || ad[0] != 0)) {
                sem_err(an, node, "%s requiere una cadena (String) y recibió %s", name, type_str(at[0], ad[0]));
                return false;
            }
            return ok;
        }
        if (!strcmp(name, "String.valueOf")) {
            *t = TYPE_STRING;
            if (argc != 1) { sem_err(an, node, "String.valueOf espera 1 argumento y recibió %d", argc); return false; }
            return ok;
        }
        if (!strcmp(name, "String.join")) {
            *t = TYPE_STRING;
            if (argc < 2) { sem_err(an, node, "String.join requiere un delimitador y al menos un elemento"); return false; }
            if (!ok) return false;
            if (at[0] != TYPE_STRING || ad[0] != 0) {
                sem_err(an, node, "El delimitador de String.join debe ser String y es %s", type_str(at[0], ad[0]));
                return false;
            }
            if (argc == 2 && ad[1] == 1 && at[1] == TYPE_STRING) return true;   // String.join(d, String[])
            for (int i = 1; i < argc; i++) {
                if (at[i] != TYPE_STRING || ad[i] != 0) {
                    sem_err(an, node, "Los elementos de String.join deben ser String (argumento %d es %s)", i + 1, type_str(at[i], ad[i]));
                    return false;
                }
            }
            return true;
        }
        if (!strcmp(name, "Arrays.indexOf")) {
            *t = TYPE_INT;
            if (argc != 2) { sem_err(an, node, "Arrays.indexOf espera (arreglo, valor) y recibió %d argumentos", argc); return false; }
            if (!ok) return false;
            if (ad[0] < 1) { sem_err(an, node, "El primer argumento de Arrays.indexOf debe ser un arreglo y es %s", type_str(at[0], ad[0])); return false; }
            if (!assignable(at[0], ad[0] - 1, at[1], ad[1])) {
                sem_err(an, node, "Arrays.indexOf: no se puede buscar un %s en un %s", type_str(at[1], ad[1]), type_str(at[0], ad[0]));
                return false;
            }
            return true;
        }
    }

    // Función definida por el usuario
    Symbol *fs = lookup_symbol(an, name);
    if (!fs) {
        sem_err(an, node, "La función '%s' no está declarada", name);
        return false;
    }
    if (fs->symbol_type != SYMBOL_FUNCTION) {
        sem_err(an, node, "'%s' no es una función", name);
        return false;
    }
    *t = fs->data_type;

    ASTNode *params = fs->parameters;
    int np = (params && params->type == NODE_LIST) ? params->data.list.count : 0;
    if (np != argc) {
        sem_err(an, node, "La función '%s' espera %d argumento(s) y recibió %d", name, np, argc);
        return false;
    }
    for (int i = 0; i < np && ok; i++) {
        ASTNode *p = params->data.list.items[i];
        DataType pt = string_to_data_type(p->data.parameter.data_type);
        int pd = p->data.parameter.dims;
        if (!assignable(pt, pd, at[i], ad[i])) {
            sem_err(an, args[i], "Argumento %d de '%s': se esperaba %s y se recibió %s",
                    i + 1, name, type_str(pt, pd), type_str(at[i], ad[i]));
            ok = false;
        }
    }
    return ok;
}

bool analyze_function_call(SemanticAnalyzer *analyzer, ASTNode *node) {
    if (!node || node->type != NODE_FUNCTION_CALL) return false;
    DataType t;
    int d;
    return call_expr(analyzer, node, &t, &d);
}

/* ------------------------------------------------------------------------
 * Expresiones
 * --------------------------------------------------------------------- */

// Evalúa una expresión que debe ser un valor escalar
static bool scalar_expr(SemanticAnalyzer *an, ASTNode *n, DataType *t) {
    int d;
    if (!expr(an, n, t, &d)) return false;
    if (d > 0) {
        sem_err(an, n, "Se esperaba un valor simple y se obtuvo un arreglo (%s)", type_str(*t, d));
        return false;
    }
    return true;
}

// Asignación como expresión; devuelve el tipo del destino
static bool assign_expr(SemanticAnalyzer *an, ASTNode *node, DataType *t, int *dims);

static bool expr(SemanticAnalyzer *an, ASTNode *node, DataType *t, int *dims) {
    *dims = 0;
    *t = TYPE_UNKNOWN;
    if (!node) return false;

    switch (node->type) {
        case NODE_INT_LITERAL:     *t = TYPE_INT; return true;
        case NODE_FLOAT_LITERAL:   *t = TYPE_FLOAT; return true;
        case NODE_STRING_LITERAL:  *t = TYPE_STRING; return true;
        case NODE_CHAR_LITERAL:    *t = TYPE_CHAR; return true;
        case NODE_BOOLEAN_LITERAL: *t = TYPE_BOOLEAN; return true;
        case NODE_NULL_LITERAL:    *t = TYPE_NULL; return true;

        case NODE_IDENTIFIER: {
            const char *name = node->data.identifier.name;
            Symbol *symbol = lookup_symbol(an, name);
            if (!symbol) {
                sem_err(an, node, "La variable '%s' no está declarada", name);
                return false;
            }
            if (symbol->symbol_type == SYMBOL_FUNCTION) {
                sem_err(an, node, "'%s' es una función y se usó como variable", name);
                return false;
            }
            if (!symbol->is_initialized) {
                sem_err(an, node, "La variable '%s' se usa antes de ser inicializada", name);
            }
            *t = symbol->data_type;
            *dims = symbol->dims;
            return true;
        }

        case NODE_BINARY_OP: {
            const char *op = node->data.binary_op.operator;
            DataType lt, rt;
            int ld, rd;
            bool a = expr(an, node->data.binary_op.left, &lt, &ld);
            bool b = expr(an, node->data.binary_op.right, &rt, &rd);
            if (!a || !b) return false;
            bool eq = !strcmp(op, "==") || !strcmp(op, "!=");
            if (ld > 0 || rd > 0) {
                if (eq && ((ld == rd && lt == rt) || lt == TYPE_NULL || rt == TYPE_NULL)) {
                    *t = TYPE_BOOLEAN;
                    return true;
                }
                sem_err(an, node, "El operador '%s' no se puede aplicar a arreglos completos (%s y %s)",
                        op, type_str(lt, ld), type_str(rt, rd));
                return false;
            }
            *t = get_binary_operation_result_type(op, lt, rt);
            if (*t == TYPE_UNKNOWN) {
                sem_err(an, node, "Operación '%s' no válida entre %s y %s", op, type_str(lt, 0), type_str(rt, 0));
                return false;
            }
            return true;
        }

        case NODE_UNARY_OP: {
            const char *op = node->data.unary_op.operator;
            ASTNode *operand = node->data.unary_op.operand;
            DataType ot;

            if (op[0] == '(') {                                   // casting: (tipo) expresión
                char tn[24];
                size_t len = strcspn(op + 1, ")");
                snprintf(tn, sizeof tn, "%.*s", (int)(len < 23 ? len : 23), op + 1);
                DataType ct = string_to_data_type(tn);
                if (!scalar_expr(an, operand, &ot)) return false;
                bool ok = (num_like(ct) && num_like(ot)) ||
                          (ct == TYPE_BOOLEAN && ot == TYPE_BOOLEAN) ||
                          (ct == TYPE_STRING && (ot == TYPE_STRING || ot == TYPE_NULL));
                if (!ok) {
                    sem_err(an, node, "No se puede convertir (cast) de %s a %s", type_str(ot, 0), type_str(ct, 0));
                    return false;
                }
                *t = ct;
                return true;
            }

            if (!strcmp(op, "++") || !strcmp(op, "--")) {
                if (operand->type != NODE_IDENTIFIER && operand->type != NODE_ARRAY_ACCESS) {
                    sem_err(an, node, "El operador '%s' requiere una variable", op);
                    return false;
                }
                if (operand->type == NODE_IDENTIFIER) {
                    Symbol *s = lookup_symbol(an, operand->data.identifier.name);
                    if (s && s->is_const) {
                        sem_err(an, node, "No se puede modificar la constante '%s'", s->id);
                        return false;
                    }
                }
            }
            if (!scalar_expr(an, operand, &ot)) return false;
            if (!strcmp(op, "!")) {
                if (ot != TYPE_BOOLEAN) { sem_err(an, node, "El operador ! requiere boolean y recibió %s", type_str(ot, 0)); return false; }
                *t = TYPE_BOOLEAN;
            } else if (!strcmp(op, "~")) {
                if (ot != TYPE_INT && ot != TYPE_CHAR) { sem_err(an, node, "El operador ~ requiere int y recibió %s", type_str(ot, 0)); return false; }
                *t = TYPE_INT;
            } else {
                if (!num_like(ot)) { sem_err(an, node, "El operador '%s' requiere un tipo numérico y recibió %s", op, type_str(ot, 0)); return false; }
                *t = (ot == TYPE_CHAR && (op[0] == '-' || op[0] == '+') && op[1] == '\0') ? TYPE_INT : ot;
            }
            return true;
        }

        case NODE_FUNCTION_CALL:
            return call_expr(an, node, t, dims);

        case NODE_ARRAY_ACCESS: {
            DataType bt, it;
            int bd;
            bool ok = expr(an, node->data.array_access.array, &bt, &bd);
            bool iok = scalar_expr(an, node->data.array_access.index, &it);
            if (iok && it != TYPE_INT && it != TYPE_CHAR) {
                sem_err(an, node, "El índice de un arreglo debe ser int y es %s", type_str(it, 0));
                iok = false;
            }
            if (!ok) return false;
            if (bd < 1) {
                sem_err(an, node, "Se usa [] sobre algo que no es un arreglo (%s)", type_str(bt, bd));
                return false;
            }
            *t = bt;
            *dims = bd - 1;
            return iok;
        }

        case NODE_MEMBER_ACCESS: {
            DataType ot;
            int od;
            if (!expr(an, node->data.member_access.object, &ot, &od)) return false;
            if (od >= 1 && !strcmp(node->data.member_access.member, "length")) {
                *t = TYPE_INT;
                return true;
            }
            sem_err(an, node, "El miembro '%s' no existe en %s", node->data.member_access.member, type_str(ot, od));
            return false;
        }

        case NODE_METHOD_CALL: {
            const char *mname = node->data.method_call.name;
            DataType ot;
            int od;
            ASTNode *args[MAX_ARGS];
            int argc = collect_args(node->data.method_call.arguments, args);
            DataType at[MAX_ARGS];
            int ad[MAX_ARGS];
            bool ok = expr(an, node->data.method_call.object, &ot, &od);
            for (int i = 0; i < argc; i++)
                if (!expr(an, args[i], &at[i], &ad[i])) ok = false;
            if (!ok) return false;

            if (!strcmp(mname, "add") && od >= 1) {                 // arreglo.add(x) -> nuevo arreglo
                if (argc != 1) { sem_err(an, node, "add espera 1 argumento y recibió %d", argc); return false; }
                if (!assignable(ot, od - 1, at[0], ad[0])) {
                    sem_err(an, node, "No se puede agregar un %s a un %s", type_str(at[0], ad[0]), type_str(ot, od));
                    return false;
                }
                *t = ot;
                *dims = od;
                return true;
            }
            if (!strcmp(mname, "equals") && od == 0 && ot == TYPE_STRING) {
                if (argc != 1) { sem_err(an, node, "equals espera 1 argumento y recibió %d", argc); return false; }
                if (!((at[0] == TYPE_STRING || at[0] == TYPE_NULL) && ad[0] == 0)) {
                    sem_err(an, node, "equals sobre String requiere un String y recibió %s", type_str(at[0], ad[0]));
                    return false;
                }
                *t = TYPE_BOOLEAN;
                return true;
            }
            sem_err(an, node, "El método '%s' no existe en %s", mname, type_str(ot, od));
            return false;
        }

        case NODE_ASSIGNMENT:
            return assign_expr(an, node, t, dims);

        default:
            sem_err(an, node, "Expresión no válida en este contexto");
            return false;
    }
}

bool analyze_expression(SemanticAnalyzer *analyzer, ASTNode *node, DataType *result_type) {
    int d;
    DataType t;
    bool ok = expr(analyzer, node, &t, &d);
    if (result_type) *result_type = t;
    return ok;
}

/* ------------------------------------------------------------------------
 * Asignaciones
 * --------------------------------------------------------------------- */

static bool assign_expr(SemanticAnalyzer *an, ASTNode *node, DataType *t, int *dims) {
    ASTNode *left = node->data.assignment.left;
    ASTNode *right = node->data.assignment.right;
    const char *op = node->data.assignment.operator ? node->data.assignment.operator : "=";
    bool compound = strcmp(op, "=") != 0;
    DataType lt = TYPE_UNKNOWN, rt;
    int ld = 0, rd;
    const char *target = "arreglo";
    Symbol *sym = NULL;
    bool ok = true;

    if (left->type == NODE_IDENTIFIER) {
        target = left->data.identifier.name;
        sym = lookup_symbol(an, target);
        if (!sym) {
            sem_err(an, left, "La variable '%s' no está declarada", target);
            analyze_expression(an, right, &rt);
            *t = TYPE_UNKNOWN; *dims = 0;
            return false;
        }
        if (sym->symbol_type == SYMBOL_FUNCTION) {
            sem_err(an, left, "No se puede asignar a '%s' porque es una función", target);
            return false;
        }
        if (sym->is_const) {
            sem_err(an, left, "No se puede modificar la constante '%s'", target);
            ok = false;
        }
        if (compound && !sym->is_initialized) {
            sem_err(an, left, "La variable '%s' se usa antes de ser inicializada", target);
        }
        lt = sym->data_type;
        ld = sym->dims;
    } else if (left->type == NODE_ARRAY_ACCESS) {
        if (!expr(an, left, &lt, &ld)) ok = false;
    } else {
        sem_err(an, left, "El lado izquierdo de la asignación no es una variable");
        return false;
    }

    bool rok = expr(an, right, &rt, &rd);
    *t = lt;
    *dims = ld;
    if (!rok || !ok) return false;

    if (!compound) {
        if (!assignable(lt, ld, rt, rd)) {
            sem_err(an, node, "No se puede asignar %s a '%s' de tipo %s", type_str(rt, rd), target, type_str(lt, ld));
            return false;
        }
        if (sym) sym->is_initialized = true;
        return true;
    }

    // Asignación compuesta: x op= y equivale a x = x op y (con cast implícito al tipo de x)
    char bop[4] = {0};
    size_t n = strlen(op) - 1;
    memcpy(bop, op, n < 3 ? n : 3);
    if (ld > 0 || rd > 0) {
        sem_err(an, node, "El operador '%s' no se puede aplicar a arreglos completos", op);
        return false;
    }
    DataType res = get_binary_operation_result_type(bop, lt, rt);
    if (res == TYPE_UNKNOWN || (lt == TYPE_STRING && strcmp(bop, "+") != 0) ||
        (lt == TYPE_BOOLEAN && res != TYPE_BOOLEAN)) {
        sem_err(an, node, "Operación '%s' no válida entre %s y %s", op, type_str(lt, 0), type_str(rt, 0));
        return false;
    }
    if (sym) sym->is_initialized = true;
    return true;
}

bool analyze_assignment(SemanticAnalyzer *analyzer, ASTNode *node) {
    if (!node || node->type != NODE_ASSIGNMENT) return false;
    DataType t;
    int d;
    return assign_expr(analyzer, node, &t, &d);
}

/* ------------------------------------------------------------------------
 * Declaraciones
 * --------------------------------------------------------------------- */

// Valida un literal de arreglo anidado: {1, 2} para dims=1, {{1}, {2}} para dims=2...
static bool check_array_literal(SemanticAnalyzer *an, ASTNode *lit, DataType base, int dims, const char *name) {
    ASTNode *vals = lit->data.array_init.values;
    bool ok = true;
    if (!vals || vals->type != NODE_LIST) return true;
    for (int i = 0; i < vals->data.list.count; i++) {
        ASTNode *el = vals->data.list.items[i];
        if (dims == 1) {
            if (el->type == NODE_ARRAY_INIT) {
                sem_err(an, el, "'%s': demasiados niveles de llaves en la inicialización", name);
                ok = false;
                continue;
            }
            DataType et;
            if (!scalar_expr(an, el, &et)) { ok = false; continue; }
            if (!assignable(base, 0, et, 0)) {
                sem_err(an, el, "'%s': el elemento %d es %s y el arreglo es de %s", name, i + 1,
                        type_str(et, 0), type_str(base, 0));
                ok = false;
            }
        } else if (el->type == NODE_ARRAY_INIT && !el->data.array_init.size) {
            ok = check_array_literal(an, el, base, dims - 1, name) && ok;
        } else {
            DataType et;
            int ed;
            if (!expr(an, el, &et, &ed)) { ok = false; continue; }
            if (!assignable(base, dims - 1, et, ed)) {
                sem_err(an, el, "'%s': el elemento %d es %s y se esperaba %s", name, i + 1,
                        type_str(et, ed), type_str(base, dims - 1));
                ok = false;
            }
        }
    }
    return ok;
}

bool analyze_variable_declaration(SemanticAnalyzer *analyzer, ASTNode *node) {
    if (!node || node->type != NODE_VAR_DECL) return false;

    char *name = node->data.var_decl.name;
    ASTNode *init_value = node->data.var_decl.init_value;
    bool is_array = node->data.var_decl.is_array;
    int dims = is_array ? node->data.var_decl.array_size : 0;
    DataType data_type = string_to_data_type(node->data.var_decl.data_type);

    if (data_type == TYPE_VOID || data_type == TYPE_UNKNOWN) {
        sem_err(analyzer, node, "Tipo no válido para la variable '%s'", name);
        return false;
    }

    Symbol *var_symbol = create_symbol(name, node->data.var_decl.is_const ? SYMBOL_CONSTANT : SYMBOL_VARIABLE,
                                       data_type, analyzer->current_scope, node->line, node->column);
    var_symbol->is_array = is_array;
    var_symbol->dims = dims;
    var_symbol->array_size = dims;
    var_symbol->is_const = node->data.var_decl.is_const;
    // Sin inicializador, un escalar toma su valor por defecto; un arreglo queda nulo
    var_symbol->is_initialized = (init_value != NULL) || !is_array;
    var_symbol->decl = node;

    // El inicializador se analiza ANTES de declarar la variable (int x = x + 1 es un error)
    bool ok = true;
    if (init_value) {
        if (init_value->type == NODE_ARRAY_INIT) {
            ASTNode *sizes = init_value->data.array_init.size;
            if (sizes) {                                         // new tipo[a][b]...
                DataType nt = string_to_data_type(init_value->data.array_init.type);
                int nd = (sizes->type == NODE_LIST) ? sizes->data.list.count : 0;
                if (nt != data_type) {
                    sem_err(analyzer, init_value, "'%s': se declaró %s pero se crea un arreglo de %s",
                            name, type_str(data_type, dims), type_str(nt, nd));
                    ok = false;
                } else if (nd != dims) {
                    sem_err(analyzer, init_value, "'%s': se declaró %s pero se crea un arreglo de %d dimensión(es)",
                            name, type_str(data_type, dims), nd);
                    ok = false;
                }
                for (int i = 0; i < nd; i++) {
                    DataType st;
                    if (!scalar_expr(analyzer, sizes->data.list.items[i], &st)) { ok = false; continue; }
                    if (st != TYPE_INT && st != TYPE_CHAR) {
                        sem_err(analyzer, sizes->data.list.items[i], "'%s': el tamaño de la dimensión %d debe ser int y es %s",
                                name, i + 1, type_str(st, 0));
                        ok = false;
                    }
                }
            } else {                                              // literal {...}
                ok = check_array_literal(analyzer, init_value, data_type, dims, name);
            }
        } else {
            DataType it;
            int id;
            if (expr(analyzer, init_value, &it, &id)) {
                if (!assignable(data_type, dims, it, id)) {
                    sem_err(analyzer, node, "No se puede asignar %s a '%s' de tipo %s",
                            type_str(it, id), name, type_str(data_type, dims));
                    ok = false;
                }
            } else {
                ok = false;
            }
        }
    }

    if (!add_symbol(analyzer, var_symbol)) return false;
    return ok;
}

/* ------------------------------------------------------------------------
 * Funciones
 * --------------------------------------------------------------------- */

static Symbol *new_function_symbol(SemanticAnalyzer *an, ASTNode *node) {
    Symbol *fs = create_symbol(node->data.func_decl.name, SYMBOL_FUNCTION,
                               string_to_data_type(node->data.func_decl.return_type),
                               an->current_scope, node->line, node->column);
    fs->parameters = node->data.func_decl.parameters;
    fs->is_initialized = true;
    fs->decl = node;
    return fs;
}

// Declara las funciones de una lista antes de analizar su contenido (permite llamadas hacia adelante)
static void predeclare_functions(SemanticAnalyzer *an, ASTNode *list) {
    if (!list || list->type != NODE_LIST) return;
    for (int i = 0; i < list->data.list.count; i++) {
        ASTNode *it = list->data.list.items[i];
        if (it && it->type == NODE_FUNCTION_DECL) add_symbol(an, new_function_symbol(an, it));
    }
}

bool analyze_function_declaration(SemanticAnalyzer *analyzer, ASTNode *node) {
    if (!node || node->type != NODE_FUNCTION_DECL) return false;

    char *name = node->data.func_decl.name;
    ASTNode *parameters = node->data.func_decl.parameters;
    ASTNode *body = node->data.func_decl.body;

    // ¿ya fue declarada por predeclare_functions?
    Symbol *func_symbol = NULL;
    for (Symbol *s = analyzer->symbol_table; s; s = s->next)
        if (s->decl == node) { func_symbol = s; break; }
    if (!func_symbol) {
        func_symbol = new_function_symbol(analyzer, node);
        if (!add_symbol(analyzer, func_symbol)) return false;
    }

    bool result = true;

    enter_scope(analyzer, name);
    bool prev_in_function = analyzer->in_function;
    bool prev_in_loop = analyzer->in_loop;
    bool prev_in_switch = analyzer->in_switch;
    Symbol *prev_function = analyzer->current_function;
    analyzer->in_function = true;
    analyzer->in_loop = false;
    analyzer->in_switch = false;
    analyzer->current_function = func_symbol;

    if (parameters && parameters->type == NODE_LIST) {
        for (int i = 0; i < parameters->data.list.count; i++) {
            ASTNode *p = parameters->data.list.items[i];
            if (!p || p->type != NODE_PARAMETER) continue;
            Symbol *ps = create_symbol(p->data.parameter.name, SYMBOL_PARAMETER,
                                       string_to_data_type(p->data.parameter.data_type),
                                       analyzer->current_scope, p->line, p->column);
            ps->is_initialized = true;
            ps->is_array = p->data.parameter.dims > 0;
            ps->dims = p->data.parameter.dims;
            ps->decl = p;
            if (ps->data_type == TYPE_VOID || ps->data_type == TYPE_UNKNOWN) {
                sem_err(analyzer, p, "Tipo no válido para el parámetro '%s'", ps->id);
                result = false;
            }
            if (!add_symbol(analyzer, ps)) result = false;
        }
    }

    // El cuerpo comparte ámbito con los parámetros
    if (body && body->type == NODE_LIST) {
        predeclare_functions(analyzer, body);
        for (int i = 0; i < body->data.list.count; i++)
            result = analyze_semantic(analyzer, body->data.list.items[i]) && result;
    } else if (body) {
        result = analyze_semantic(analyzer, body) && result;
    }

    exit_scope(analyzer);
    analyzer->in_function = prev_in_function;
    analyzer->in_loop = prev_in_loop;
    analyzer->in_switch = prev_in_switch;
    analyzer->current_function = prev_function;

    return result;
}

/* ------------------------------------------------------------------------
 * Sentencias
 * --------------------------------------------------------------------- */

static bool check_condition(SemanticAnalyzer *an, ASTNode *cond, ASTNode *where, const char *what) {
    DataType t;
    if (!scalar_expr(an, cond, &t)) return false;
    if (t != TYPE_BOOLEAN) {
        sem_err(an, where, "La condición del %s debe ser boolean y es %s", what, type_str(t, 0));
        return false;
    }
    return true;
}

bool analyze_semantic(SemanticAnalyzer *analyzer, ASTNode *node) {
    if (!node) return true;
    DataType t;
    int d;
    bool ok = true;

    switch (node->type) {
        case NODE_PROGRAM: {
            ASTNode *body = node->data.program.body;
            if (!body || body->type != NODE_LIST)
                return analyze_semantic(analyzer, body);
            predeclare_functions(analyzer, body);
            for (int i = 0; i < body->data.list.count; i++)
                if (body->data.list.items[i]->type == NODE_FUNCTION_DECL)
                    ok = analyze_semantic(analyzer, body->data.list.items[i]) && ok;
            for (int i = 0; i < body->data.list.count; i++)
                if (body->data.list.items[i]->type != NODE_FUNCTION_DECL)
                    ok = analyze_semantic(analyzer, body->data.list.items[i]) && ok;
            return ok;
        }

        case NODE_MAIN_CLASS: {
            bool prev_fn = analyzer->in_function;
            Symbol *prev_cur = analyzer->current_function;
            enter_scope(analyzer, "main");
            analyzer->in_function = true;       // main se comporta como una función void
            analyzer->current_function = NULL;
            ok = analyze_semantic(analyzer, node->data.main_class.body);
            analyzer->in_function = prev_fn;
            analyzer->current_function = prev_cur;
            exit_scope(analyzer);
            return ok;
        }

        case NODE_LIST:
        case NODE_STATEMENT_LIST:
            enter_block_scope(analyzer);
            predeclare_functions(analyzer, node);
            for (int i = 0; i < node->data.list.count; i++)
                ok = analyze_semantic(analyzer, node->data.list.items[i]) && ok;
            exit_scope(analyzer);
            return ok;

        case NODE_FUNCTION_DECL:
            return analyze_function_declaration(analyzer, node);

        case NODE_VAR_DECL:
            return analyze_variable_declaration(analyzer, node);

        case NODE_ASSIGNMENT:
            return analyze_assignment(analyzer, node);

        case NODE_FUNCTION_CALL:
            return analyze_function_call(analyzer, node);

        case NODE_EXPRESSION_STMT:
            return expr(analyzer, node->data.program.body, &t, &d);

        case NODE_IF_STMT:
            ok = check_condition(analyzer, node->data.if_stmt.condition, node, "if");
            ok = analyze_semantic(analyzer, node->data.if_stmt.then_stmt) && ok;
            ok = analyze_semantic(analyzer, node->data.if_stmt.else_stmt) && ok;
            return ok;

        case NODE_WHILE_STMT: {
            bool prev = analyzer->in_loop;
            ok = check_condition(analyzer, node->data.while_stmt.condition, node, "while");
            analyzer->in_loop = true;
            ok = analyze_semantic(analyzer, node->data.while_stmt.body) && ok;
            analyzer->in_loop = prev;
            return ok;
        }

        case NODE_DO_WHILE_STMT: {
            bool prev = analyzer->in_loop;
            analyzer->in_loop = true;
            ok = analyze_semantic(analyzer, node->data.while_stmt.body);
            analyzer->in_loop = prev;
            ok = check_condition(analyzer, node->data.while_stmt.condition, node, "do-while") && ok;
            return ok;
        }

        case NODE_FOR_STMT: {
            bool prev = analyzer->in_loop;
            enter_block_scope(analyzer);  // ámbito propio para la variable del for
            ok = analyze_semantic(analyzer, node->data.for_stmt.init);
            if (node->data.for_stmt.condition)
                ok = check_condition(analyzer, node->data.for_stmt.condition, node, "for") && ok;
            analyzer->in_loop = true;
            ok = analyze_semantic(analyzer, node->data.for_stmt.update) && ok;
            ok = analyze_semantic(analyzer, node->data.for_stmt.body) && ok;
            analyzer->in_loop = prev;
            exit_scope(analyzer);
            return ok;
        }

        case NODE_FOREACH_STMT: {
            bool prev = analyzer->in_loop;
            DataType vt = string_to_data_type(node->data.foreach_stmt.data_type);
            int vd = node->data.foreach_stmt.dims;
            DataType it;
            int id;
            ok = expr(analyzer, node->data.foreach_stmt.iterable, &it, &id);
            if (ok) {
                if (id < 1) {
                    sem_err(analyzer, node, "El for-each requiere un arreglo y recibió %s", type_str(it, id));
                    ok = false;
                } else if (id != vd + 1 || !assignable(vt, vd, it, id - 1)) {
                    sem_err(analyzer, node, "La variable '%s' es %s pero los elementos del arreglo son %s",
                            node->data.foreach_stmt.name, type_str(vt, vd), type_str(it, id - 1));
                    ok = false;
                }
            }
            enter_block_scope(analyzer);
            Symbol *vs = create_symbol(node->data.foreach_stmt.name, SYMBOL_VARIABLE, vt,
                                       analyzer->current_scope, node->line, node->column);
            vs->is_initialized = true;
            vs->dims = vd;
            vs->is_array = vd > 0;
            vs->decl = node;
            if (!add_symbol(analyzer, vs)) ok = false;
            analyzer->in_loop = true;
            ok = analyze_semantic(analyzer, node->data.foreach_stmt.body) && ok;
            analyzer->in_loop = prev;
            exit_scope(analyzer);
            return ok;
        }

        case NODE_SWITCH_STMT: {
            DataType kt;
            ok = scalar_expr(analyzer, node->data.switch_stmt.expression, &kt);
            if (ok && kt != TYPE_INT && kt != TYPE_CHAR && kt != TYPE_STRING) {
                sem_err(analyzer, node, "El switch requiere int, char o String y recibió %s", type_str(kt, 0));
                ok = false;
            }
            bool prev = analyzer->in_switch;
            analyzer->in_switch = true;
            ASTNode *cases = node->data.switch_stmt.cases;
            if (cases && cases->type == NODE_LIST) {
                for (int i = 0; i < cases->data.list.count; i++) {
                    ASTNode *c = cases->data.list.items[i];
                    if (c->data.case_stmt.value) {
                        DataType ct;
                        if (!scalar_expr(analyzer, c->data.case_stmt.value, &ct)) ok = false;
                        else if (ok && !assignable(kt, 0, ct, 0) && !assignable(ct, 0, kt, 0)) {
                            sem_err(analyzer, c->data.case_stmt.value, "El case es %s pero el switch es %s",
                                    type_str(ct, 0), type_str(kt, 0));
                            ok = false;
                        }
                    }
                    ok = analyze_semantic(analyzer, c->data.case_stmt.statements) && ok;
                }
            }
            analyzer->in_switch = prev;
            return ok;
        }

        case NODE_RETURN_STMT: {
            Symbol *f = analyzer->current_function;
            ASTNode *value = node->data.return_stmt.value;
            if (!analyzer->in_function) {
                sem_err(analyzer, node, "return fuera de una función");
                return false;
            }
            if (!f) {                                             // main
                if (value) {
                    sem_err(analyzer, node, "main es void y no puede devolver un valor");
                    return false;
                }
                return true;
            }
            if (f->data_type == TYPE_VOID) {
                if (value) {
                    sem_err(analyzer, node, "La función '%s' es void y no puede devolver un valor", f->id);
                    return false;
                }
                return true;
            }
            if (!value) {
                sem_err(analyzer, node, "La función '%s' debe devolver un valor de tipo %s", f->id, type_str(f->data_type, 0));
                return false;
            }
            if (!expr(analyzer, value, &t, &d)) return false;
            if (!assignable(f->data_type, 0, t, d)) {
                sem_err(analyzer, node, "La función '%s' devuelve %s pero se retornó %s",
                        f->id, type_str(f->data_type, 0), type_str(t, d));
                return false;
            }
            return true;
        }

        case NODE_BREAK_STMT:
            if (!analyzer->in_loop && !analyzer->in_switch) {
                sem_err(analyzer, node, "break fuera de un ciclo o de un switch");
                return false;
            }
            return true;

        case NODE_CONTINUE_STMT:
            if (!analyzer->in_loop) {
                sem_err(analyzer, node, "continue fuera de un ciclo");
                return false;
            }
            return true;

        case NODE_BINARY_OP:
        case NODE_UNARY_OP:
        case NODE_METHOD_CALL:
        case NODE_MEMBER_ACCESS:
            return expr(analyzer, node, &t, &d);

        default:
            return true;
    }
}

/* ------------------------------------------------------------------------
 * Utilidades públicas
 * --------------------------------------------------------------------- */

void generate_semantic_errors_report(const char *filename) {
    if (global_analyzer) {
        printf("📄 Generando reporte de errores semánticos: %s\n", filename);
    }
}

const char* symbol_type_to_string(SymbolType type) {
    switch (type) {
        case SYMBOL_VARIABLE: return "Variable";
        case SYMBOL_FUNCTION: return "Función";
        case SYMBOL_PARAMETER: return "Parámetro";
        case SYMBOL_CONSTANT: return "Constante";
        default: return "Desconocido";
    }
}
