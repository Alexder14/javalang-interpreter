

#include "semantic.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Variables globales
static SemanticAnalyzer *global_analyzer = NULL;
static bool is_builtin_function(const char *name);
extern int block_counter;

// Crear analizador semántico
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
    block_counter = 0;  // numeración de bloques por análisis
    
    global_analyzer = analyzer;
    return analyzer;
}

// Destruir analizador semántico
void destroy_semantic_analyzer(SemanticAnalyzer *analyzer) {
    if (!analyzer) return;
    
    // Liberar tabla de símbolos
    Symbol *current = analyzer->symbol_table;
    while (current) {
        Symbol *next = current->next;
        free(current->id);
        free(current->scope);
        free(current);
        current = next;
    }
    
    // Liberar errores
    SemanticError *error = analyzer->errors;
    while (error) {
        SemanticError *next = error->next;
        free(error->message);
        free(error->context);
        free(error);
        error = next;
    }
    
    free(analyzer->current_scope);
    free(analyzer);
}

// Crear símbolo
Symbol* create_symbol(const char *id, SymbolType type, DataType data_type, 
                     const char *scope, int line, int col) {
    Symbol *symbol = malloc(sizeof(Symbol));
    if (!symbol) {
        fprintf(stderr, "Error: No se pudo crear símbolo\n");
        exit(1);
    }
    
    symbol->id = strdup(id);
    symbol->symbol_type = type;  // CORREGIDO: usar symbol_type
    symbol->data_type = data_type;
    symbol->scope = strdup(scope);
    symbol->line = line;
    symbol->column = col;
    symbol->is_initialized = false;
    symbol->is_array = false;
    symbol->array_size = 0;
    symbol->parameters = NULL;
    symbol->value = NULL;
    symbol->next = NULL;
    
    return symbol;
}

// Buscar símbolo en la tabla: ámbito actual, luego ámbitos padre ("a/b/c" -> "a/b" -> "a") y Global
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

// Agregar símbolo a la tabla
bool add_symbol(SemanticAnalyzer *analyzer, Symbol *symbol) {
    // Verificar que no exista en el ámbito actual
    Symbol *existing = lookup_symbol(analyzer, symbol->id);
    if (existing && strcmp(existing->scope, symbol->scope) == 0) {
        add_semantic_error(analyzer, "Variable ya declarada en este ámbito", 
                          symbol->id, symbol->line, symbol->column);
        return false;
    }
    
    // Agregar al inicio de la lista
    symbol->next = analyzer->symbol_table;
    analyzer->symbol_table = symbol;
    return true;
}

// Agregar error semántico
void add_semantic_error(SemanticAnalyzer *analyzer, const char *message, 
                       const char *context, int line, int col) {
    SemanticError *error = malloc(sizeof(SemanticError));
    if (!error) return;
    
    error->message = strdup(message);
    error->context = strdup(context ? context : "");
    error->line = line;
    error->column = col;
    error->next = analyzer->errors;
    
    analyzer->errors = error;
    analyzer->error_count++;
}

// Analizar declaración de función - CORREGIDO
bool analyze_function_declaration(SemanticAnalyzer *analyzer, ASTNode *node) {
    if (!node || node->type != NODE_FUNCTION_DECL) {
        return false;
    }
    
    // CORREGIDO: Usar el nombre correcto del campo en el AST
    char *return_type = node->data.func_decl.return_type;
    char *name = node->data.func_decl.name;
    ASTNode *parameters = node->data.func_decl.parameters;
    ASTNode *body = node->data.func_decl.body;
    
    // Convertir tipo de retorno
    DataType ret_type = string_to_data_type(return_type);
    
    // Crear símbolo de función
    Symbol *func_symbol = create_symbol(name, SYMBOL_FUNCTION, ret_type,
                                       analyzer->current_scope, node->line, node->column);
    func_symbol->parameters = parameters;
    
    if (!add_symbol(analyzer, func_symbol)) {
        return false;
    }
    
    bool result = true;
    
    // Entrar al ámbito de la función
    enter_scope(analyzer, name);
    bool prev_in_function = analyzer->in_function;
    analyzer->in_function = true;
    
    // Establecer función actual
    analyzer->current_function = func_symbol;
    
    // Analizar parámetros
    if (parameters && parameters->type == NODE_LIST) {
        for (int i = 0; i < parameters->data.list.count; i++) {
            ASTNode *p = parameters->data.list.items[i];
            if (!p || p->type != NODE_PARAMETER) continue;
            Symbol *ps = create_symbol(p->data.parameter.name, SYMBOL_VARIABLE,
                                       string_to_data_type(p->data.parameter.data_type),
                                       analyzer->current_scope, p->line, p->column);
            ps->is_initialized = true;
            ps->is_array = p->data.parameter.is_array;
            if (!add_symbol(analyzer, ps)) result = false;
        }
    }
    
    // Analizar cuerpo
    if (body) {
        result = analyze_semantic(analyzer, body) && result;
    }
    
    // Salir del ámbito
    exit_scope(analyzer);
    analyzer->in_function = prev_in_function;
    analyzer->current_function = NULL;
    
    return result;
}

// Analizar declaración de variable - CORREGIDO
bool analyze_variable_declaration(SemanticAnalyzer *analyzer, ASTNode *node) {
    if (!node || node->type != NODE_VAR_DECL) {
        return false;
    }
    
    // CORREGIDO: Usar acceso directo a los campos
    char *data_type_str = node->data.var_decl.data_type;
    char *name = node->data.var_decl.name;
    ASTNode *init_value = node->data.var_decl.init_value;
    bool is_array = node->data.var_decl.is_array;
    int array_size = node->data.var_decl.array_size;
    
    // Convertir tipo
    DataType data_type = string_to_data_type(data_type_str);
    
    // Crear símbolo de variable
    Symbol *var_symbol = create_symbol(name, SYMBOL_VARIABLE, data_type,
                                      analyzer->current_scope, node->line, node->column);
    var_symbol->is_array = is_array;
    var_symbol->array_size = array_size;
    var_symbol->is_initialized = (init_value != NULL);
    
    if (!add_symbol(analyzer, var_symbol)) {
        return false;
    }
    
    // Analizar inicializador si existe
    if (init_value && init_value->type == NODE_ARRAY_INIT) {
        ASTNode *vals = init_value->data.array_init.values;
        bool ok = true;
        if (init_value->data.array_init.type &&
            string_to_data_type(init_value->data.array_init.type) != data_type) {
            add_semantic_error(analyzer, "Tipo de arreglo incompatible", name,
                              node->line, node->column);
            ok = false;
        }
        if (init_value->data.array_init.size) {
            DataType st;
            if (analyze_expression(analyzer, init_value->data.array_init.size, &st) && st != TYPE_INT) {
                add_semantic_error(analyzer, "El tamaño del arreglo debe ser int", name,
                                  node->line, node->column);
                ok = false;
            }
        }
        if (vals && vals->type == NODE_LIST) {
            for (int i = 0; i < vals->data.list.count; i++) {
                DataType et;
                if (analyze_expression(analyzer, vals->data.list.items[i], &et) &&
                    !is_compatible_types(data_type, et)) {
                    add_semantic_error(analyzer, "Elemento de arreglo con tipo incompatible", name,
                                      node->line, node->column);
                    ok = false;
                }
            }
        }
        return ok;
    }
    
    if (init_value) {
        DataType init_type;
        if (analyze_expression(analyzer, init_value, &init_type)) {
            if (!is_compatible_types(data_type, init_type)) {
                add_semantic_error(analyzer, "Tipo de inicializador incompatible",
                                  name, node->line, node->column);
                return false;
            }
        }
    }
    
    return true;
}

// Analizar asignación - CORREGIDO
bool analyze_assignment(SemanticAnalyzer *analyzer, ASTNode *node) {
    if (!node || node->type != NODE_ASSIGNMENT) {
        return false;
    }
    
    // CORREGIDO: Usar acceso directo
    ASTNode *left = node->data.assignment.left;
    ASTNode *right = node->data.assignment.right;
    
    // Lado izquierdo con acceso a arreglo: a[i] = expr
    if (left->type == NODE_ARRAY_ACCESS) {
        DataType lt, rt;
        bool l_ok = analyze_expression(analyzer, left, &lt);
        bool r_ok = analyze_expression(analyzer, right, &rt);
        if (l_ok && r_ok && !is_compatible_types(lt, rt)) {
            add_semantic_error(analyzer, "Tipos incompatibles en asignación",
                              "arreglo", node->line, node->column);
            return false;
        }
        return l_ok && r_ok;
    }
    
    // Verificar que el lado izquierdo sea un identificador válido
    if (left->type == NODE_IDENTIFIER) {
        const char *var_name = left->data.identifier.name;
        Symbol *var_symbol = lookup_symbol(analyzer, var_name);
        
        if (!var_symbol) {
            add_semantic_error(analyzer, "Variable no declarada", var_name,
                              left->line, left->column);
            return false;
        }
        
        if (var_symbol->symbol_type != SYMBOL_VARIABLE) { // CORREGIDO: symbol_type
            add_semantic_error(analyzer, "No se puede asignar a este identificador",
                              var_name, left->line, left->column);
            return false;
        }
        
        // Con "=" la variable queda inicializada; con "+=" etc. ya debía estarlo
        const char *aop = node->data.assignment.operator;
        if (aop && strcmp(aop, "=") != 0 && !var_symbol->is_initialized) {
            add_semantic_error(analyzer, "Variable usada antes de ser inicializada",
                              var_name, left->line, left->column);
        }
        var_symbol->is_initialized = true;
        
        // Analizar expresión del lado derecho
        DataType right_type;
        if (analyze_expression(analyzer, right, &right_type)) {
            if (!is_compatible_types(var_symbol->data_type, right_type)) {
                add_semantic_error(analyzer, "Tipos incompatibles en asignación",
                                  var_name, node->line, node->column);
                return false;
            }
        }
    }
    
    return true;
}

// Analizar expresión
bool analyze_expression(SemanticAnalyzer *analyzer, ASTNode *node, DataType *result_type) {
    if (!node || !result_type) return false;
    
    switch (node->type) {
        case NODE_INT_LITERAL:
            *result_type = TYPE_INT;
            return true;
            
        case NODE_FLOAT_LITERAL:
            *result_type = TYPE_FLOAT;
            return true;
            
        case NODE_STRING_LITERAL:
            *result_type = TYPE_STRING;
            return true;
            
        case NODE_CHAR_LITERAL:
            *result_type = TYPE_CHAR;
            return true;
            
        case NODE_BOOLEAN_LITERAL:
            *result_type = TYPE_BOOLEAN;
            return true;
            
        case NODE_NULL_LITERAL:
            *result_type = TYPE_NULL;
            return true;
            
        case NODE_IDENTIFIER: {
            const char *name = node->data.identifier.name;
            Symbol *symbol = lookup_symbol(analyzer, name);
            
            if (!symbol) {
                add_semantic_error(analyzer, "Variable no declarada", name,
                                  node->line, node->column);
                *result_type = TYPE_UNKNOWN;
                return false;
            }
            
            if (!symbol->is_initialized && symbol->symbol_type == SYMBOL_VARIABLE) { // CORREGIDO
                add_semantic_error(analyzer, "Variable usada antes de ser inicializada",
                                  name, node->line, node->column);
            }
            
            *result_type = symbol->data_type;
            return true;
        }
        
        case NODE_BINARY_OP: {
            DataType left_type, right_type;
            bool left_ok = analyze_expression(analyzer, node->data.binary_op.left, &left_type);
            bool right_ok = analyze_expression(analyzer, node->data.binary_op.right, &right_type);
            
            if (!left_ok || !right_ok) {
                *result_type = TYPE_UNKNOWN;
                return false;
            }
            
            // CORREGIDO: orden correcto de parámetros
            *result_type = get_binary_operation_result_type(node->data.binary_op.operator,
                                                           left_type, right_type);
            
            if (*result_type == TYPE_UNKNOWN) {
                add_semantic_error(analyzer, "Operación no válida entre tipos",
                                  node->data.binary_op.operator, node->line, node->column);
                return false;
            }
            
            return true;
        }
        
        case NODE_UNARY_OP: {
            DataType ot;
            if (!analyze_expression(analyzer, node->data.unary_op.operand, &ot)) {
                *result_type = TYPE_UNKNOWN;
                return false;
            }
            const char *op = node->data.unary_op.operator;
            if (strcmp(op, "!") == 0) {
                if (ot != TYPE_BOOLEAN) {
                    add_semantic_error(analyzer, "Operador ! requiere booleano", op,
                                      node->line, node->column);
                    *result_type = TYPE_UNKNOWN;
                    return false;
                }
                *result_type = TYPE_BOOLEAN;
            } else {
                if (!is_numeric_type(ot)) {
                    add_semantic_error(analyzer, "Operador unario requiere tipo numérico", op,
                                      node->line, node->column);
                    *result_type = TYPE_UNKNOWN;
                    return false;
                }
                *result_type = ot;
            }
            return true;
        }
        
        case NODE_FUNCTION_CALL: {
            bool ok = analyze_function_call(analyzer, node);
            const char *fname = node->data.func_call.name;
            if (is_builtin_function(fname)) {
                if (strstr(fname, "parseInt") || strstr(fname, "indexOf")) *result_type = TYPE_INT;
                else if (strstr(fname, "parseFloat")) *result_type = TYPE_FLOAT;
                else if (strstr(fname, "parseDouble")) *result_type = TYPE_DOUBLE;
                else if (strstr(fname, "valueOf") || strstr(fname, "join")) *result_type = TYPE_STRING;
                else *result_type = TYPE_VOID;
            } else {
                Symbol *fs = lookup_symbol(analyzer, fname);
                *result_type = fs ? fs->data_type : TYPE_UNKNOWN;
            }
            return ok;
        }
        
        case NODE_ARRAY_ACCESS: {
            ASTNode *arr = node->data.array_access.array;
            DataType it;
            bool ok = analyze_expression(analyzer, node->data.array_access.index, &it);
            if (ok && it != TYPE_INT) {
                add_semantic_error(analyzer, "El índice de un arreglo debe ser int", "",
                                  node->line, node->column);
                ok = false;
            }
            Symbol *as = (arr && arr->type == NODE_IDENTIFIER)
                         ? lookup_symbol(analyzer, arr->data.identifier.name) : NULL;
            if (!as) {
                if (arr && arr->type == NODE_IDENTIFIER)
                    add_semantic_error(analyzer, "Arreglo no declarado", arr->data.identifier.name,
                                      node->line, node->column);
                *result_type = TYPE_UNKNOWN;
                return false;
            }
            *result_type = as->data_type;
            return ok;
        }
        
        case NODE_ARRAY_INIT:
            *result_type = node->data.array_init.type
                           ? string_to_data_type(node->data.array_init.type) : TYPE_UNKNOWN;
            return true;
        
        case NODE_ASSIGNMENT:
            *result_type = TYPE_UNKNOWN;
            return analyze_assignment(analyzer, node);
        
        default:
            *result_type = TYPE_UNKNOWN;
            return false;
    }
}

// Analizar llamada a función - CORREGIDO
bool analyze_function_call(SemanticAnalyzer *analyzer, ASTNode *node) {
    if (!node || node->type != NODE_FUNCTION_CALL) {
        return false;
    }
    
    // CORREGIDO: Usar acceso directo
    char *name = node->data.func_call.name;
    ASTNode *arguments = node->data.func_call.arguments;
    
    // Analizar argumentos
    bool args_ok = true;
    if (arguments && arguments->type == NODE_LIST) {
        for (int i = 0; i < arguments->data.list.count; i++) {
            DataType at;
            args_ok = analyze_expression(analyzer, arguments->data.list.items[i], &at) && args_ok;
        }
    } else if (arguments) {
        DataType at;
        args_ok = analyze_expression(analyzer, arguments, &at);
    }
    
    if (is_builtin_function(name)) return args_ok;
    
    // Buscar función en la tabla de símbolos
    Symbol *func_symbol = lookup_symbol(analyzer, name);
    
    if (!func_symbol) {
        add_semantic_error(analyzer, "Función no declarada", name,
                          node->line, node->column);
        return false;
    }
    
    if (func_symbol->symbol_type != SYMBOL_FUNCTION) { // CORREGIDO
        add_semantic_error(analyzer, "Identificador no es una función", name,
                          node->line, node->column);
        return false;
    }
    
    int expected = (func_symbol->parameters && func_symbol->parameters->type == NODE_LIST)
                   ? func_symbol->parameters->data.list.count : 0;
    int given = (arguments && arguments->type == NODE_LIST) ? arguments->data.list.count
                : (arguments ? 1 : 0);
    if (expected != given) {
        add_semantic_error(analyzer, "Número de argumentos incorrecto", name,
                          node->line, node->column);
        return false;
    }
    
    return args_ok;
}

// Verificar compatibilidad de tipos
bool is_compatible_types(DataType type1, DataType type2) {
    if (type1 == type2) return true;
    
    // Conversiones implícitas permitidas
    if (type1 == TYPE_FLOAT && type2 == TYPE_INT) return true;
    if (type1 == TYPE_DOUBLE && (type2 == TYPE_INT || type2 == TYPE_FLOAT)) return true;
    
    return false;
}

// Obtener tipo resultado de operación binaria - CORREGIDO
DataType get_binary_operation_result_type(const char *op, DataType left_type, DataType right_type) {
    // Concatenación: String + cualquier tipo
    if (strcmp(op, "+") == 0 && (left_type == TYPE_STRING || right_type == TYPE_STRING)) {
        return TYPE_STRING;
    }
    
    if (strcmp(op, "+") == 0 || strcmp(op, "-") == 0 || 
        strcmp(op, "*") == 0 || strcmp(op, "/") == 0 || strcmp(op, "%") == 0) {
        if (is_numeric_type(left_type) && is_numeric_type(right_type)) {
            if (left_type == TYPE_DOUBLE || right_type == TYPE_DOUBLE) return TYPE_DOUBLE;
            if (left_type == TYPE_FLOAT || right_type == TYPE_FLOAT) return TYPE_FLOAT;
            return TYPE_INT;
        }
    }
    
    if (strcmp(op, "==") == 0 || strcmp(op, "!=") == 0 ||
        strcmp(op, "<") == 0 || strcmp(op, "<=") == 0 ||
        strcmp(op, ">") == 0 || strcmp(op, ">=") == 0) {
        if (is_compatible_types(left_type, right_type)) {
            return TYPE_BOOLEAN;
        }
    }
    
    if (strcmp(op, "&&") == 0 || strcmp(op, "||") == 0) {
        if (left_type == TYPE_BOOLEAN && right_type == TYPE_BOOLEAN) {
            return TYPE_BOOLEAN;
        }
    }
    
    return TYPE_UNKNOWN;
}

// Entrar a nuevo ámbito (ruta jerárquica: "main/bloque1/bloque2")
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

// Salir del ámbito actual (vuelve al padre)
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

int block_counter = 0;

static void enter_block_scope(SemanticAnalyzer *analyzer) {
    char name[32];
    snprintf(name, sizeof(name), "bloque%d", ++block_counter);
    enter_scope(analyzer, name);
}

static bool is_builtin_function(const char *name) {
    static const char *builtins[] = {"println", "print", "System.out.println", "System.out.print", "Integer.parseInt",
                                     "Float.parseFloat", "Double.parseDouble", "String.valueOf",
                                     "Arrays.indexOf", "parseInt", "parseFloat",
                                     "parseDouble", "valueOf", "String.join", "indexOf", NULL};
    for (int i = 0; builtins[i]; i++)
        if (strcmp(builtins[i], name) == 0) return true;
    return false;
}

// Función principal de análisis semántico
bool analyze_semantic(SemanticAnalyzer *analyzer, ASTNode *node) {
    if (!node) return true;
    DataType t;
    bool ok = true;
    
    switch (node->type) {
        case NODE_PROGRAM: {
            ASTNode *body = node->data.program.body;
            if (!body || body->type != NODE_LIST)
                return analyze_semantic(analyzer, body);
            // Primero las funciones (para que main pueda llamarlas aunque se declaren después)
            for (int i = 0; i < body->data.list.count; i++)
                if (body->data.list.items[i]->type == NODE_FUNCTION_DECL)
                    ok = analyze_semantic(analyzer, body->data.list.items[i]) && ok;
            for (int i = 0; i < body->data.list.count; i++)
                if (body->data.list.items[i]->type != NODE_FUNCTION_DECL)
                    ok = analyze_semantic(analyzer, body->data.list.items[i]) && ok;
            return ok;
        }
            
        case NODE_MAIN_CLASS:
            enter_scope(analyzer, "main");
            ok = analyze_semantic(analyzer, node->data.main_class.body);
            exit_scope(analyzer);
            return ok;
            
        case NODE_LIST:
        case NODE_STATEMENT_LIST:
            enter_block_scope(analyzer);
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
            return analyze_expression(analyzer, node->data.program.body, &t);
            
        case NODE_IF_STMT:
            ok = analyze_expression(analyzer, node->data.if_stmt.condition, &t);
            if (ok && t != TYPE_BOOLEAN) {
                add_semantic_error(analyzer, "La condición del if debe ser booleana", "if",
                                  node->line, node->column);
                ok = false;
            }
            ok = analyze_semantic(analyzer, node->data.if_stmt.then_stmt) && ok;
            ok = analyze_semantic(analyzer, node->data.if_stmt.else_stmt) && ok;
            return ok;
            
        case NODE_WHILE_STMT: {
            bool prev = analyzer->in_loop;
            ok = analyze_expression(analyzer, node->data.while_stmt.condition, &t);
            if (ok && t != TYPE_BOOLEAN) {
                add_semantic_error(analyzer, "La condición del while debe ser booleana", "while",
                                  node->line, node->column);
                ok = false;
            }
            analyzer->in_loop = true;
            ok = analyze_semantic(analyzer, node->data.while_stmt.body) && ok;
            analyzer->in_loop = prev;
            return ok;
        }
            
        case NODE_FOR_STMT: {
            bool prev = analyzer->in_loop;
            enter_block_scope(analyzer);  // ámbito propio para la variable del for
            ok = analyze_semantic(analyzer, node->data.for_stmt.init);
            if (node->data.for_stmt.condition) {
                bool c = analyze_expression(analyzer, node->data.for_stmt.condition, &t);
                if (c && t != TYPE_BOOLEAN) {
                    add_semantic_error(analyzer, "La condición del for debe ser booleana", "for",
                                      node->line, node->column);
                    c = false;
                }
                ok = c && ok;
            }
            analyzer->in_loop = true;
            ok = analyze_semantic(analyzer, node->data.for_stmt.update) && ok;
            ok = analyze_semantic(analyzer, node->data.for_stmt.body) && ok;
            analyzer->in_loop = prev;
            exit_scope(analyzer);
            return ok;
        }
            
        case NODE_RETURN_STMT:
            if (!analyzer->in_function) {
                add_semantic_error(analyzer, "return fuera de una función", "return",
                                  node->line, node->column);
                return false;
            }
            if (node->data.return_stmt.value)
                return analyze_expression(analyzer, node->data.return_stmt.value, &t);
            return true;
            
        case NODE_BREAK_STMT:
        case NODE_CONTINUE_STMT:
            if (!analyzer->in_loop) {
                add_semantic_error(analyzer, "break/continue fuera de un bucle", "",
                                  node->line, node->column);
                return false;
            }
            return true;
            
        case NODE_BINARY_OP:
        case NODE_UNARY_OP:
            return analyze_expression(analyzer, node, &t);
            
        default:
            return true;
    }
}

// Generar reporte de errores semánticos
void generate_semantic_errors_report(const char *filename) {
    if (global_analyzer) {
        printf("📄 Generando reporte de errores semánticos: %s\n", filename);
        // Aquí se puede implementar la generación del reporte a archivo
    }
}

// Funciones de utilidad adicionales
const char* symbol_type_to_string(SymbolType type) {
    switch (type) {
        case SYMBOL_VARIABLE: return "Variable";
        case SYMBOL_FUNCTION: return "Función";
        case SYMBOL_PARAMETER: return "Parámetro";
        case SYMBOL_CONSTANT: return "Constante";
        default: return "Desconocido";
    }
}