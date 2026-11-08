#include "interpreter.h"
#include "common.h"
#include <stdarg.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

/* ========================================================================
 * Valores
 * ===================================================================== */

typedef enum { V_VOID, V_INT, V_FLOAT, V_DOUBLE, V_BOOL, V_CHAR, V_STRING, V_ARRAY, V_NULL } VKind;

struct Array;
typedef struct Value {
    VKind k;
    union {
        int32_t i;
        double d;
        int b;
        char c;
        const char *s;
        struct Array *a;
    } u;
} Value;

typedef struct Array {
    VKind base;     /* tipo escalar de los elementos hoja */
    int dims;       /* dimensiones de ESTE arreglo: 1 = vector, 2 = matriz... */
    int len;
    Value *items;   /* escalares de tipo base si dims == 1; subarreglos (V_ARRAY) si dims > 1 */
} Array;

static Value mkvoid(void)             { Value v; memset(&v, 0, sizeof v); v.k = V_VOID; return v; }
static Value mknull(void)             { Value v; memset(&v, 0, sizeof v); v.k = V_NULL; return v; }
static Value mkint(int32_t i)         { Value v = mkvoid(); v.k = V_INT; v.u.i = i; return v; }
static Value mkbool(int b)            { Value v = mkvoid(); v.k = V_BOOL; v.u.b = b ? 1 : 0; return v; }
static Value mkchar(char c)           { Value v = mkvoid(); v.k = V_CHAR; v.u.c = c; return v; }
static Value mkstr(const char *s)     { Value v = mkvoid(); v.k = V_STRING; v.u.s = s; return v; }
static Value mkfloat(double d)        { Value v = mkvoid(); v.k = V_FLOAT; v.u.d = (double)(float)d; return v; }
static Value mkdouble(double d)       { Value v = mkvoid(); v.k = V_DOUBLE; v.u.d = d; return v; }
static Value mkarray(Array *a)        { Value v = mkvoid(); v.k = V_ARRAY; v.u.a = a; return v; }

/* ========================================================================
 * Memoria: todo lo que se reserva durante una ejecución se libera de golpe
 * ===================================================================== */

static void **g_allocs = NULL;
static size_t g_nallocs = 0, g_capallocs = 0;

static void *ialloc(size_t n) {
    void *p = calloc(1, n ? n : 1);
    if (!p) { fprintf(stderr, "Error: memoria insuficiente en el intérprete\n"); exit(1); }
    if (g_nallocs == g_capallocs) {
        g_capallocs = g_capallocs ? g_capallocs * 2 : 256;
        g_allocs = realloc(g_allocs, g_capallocs * sizeof(void *));
    }
    g_allocs[g_nallocs++] = p;
    return p;
}

static char *istrdup(const char *s) {
    size_t n = strlen(s);
    char *p = ialloc(n + 1);
    memcpy(p, s, n + 1);
    return p;
}

static void arena_free_all(void) {
    for (size_t i = 0; i < g_nallocs; i++) free(g_allocs[i]);
    free(g_allocs);
    g_allocs = NULL;
    g_nallocs = g_capallocs = 0;
}

/* ========================================================================
 * Estado del intérprete
 * ===================================================================== */

#define MAX_STEPS 3000000
#define MAX_CALL_DEPTH 1000
#define MAX_ARGS 32

typedef enum { SIG_NONE, SIG_BREAK, SIG_CONTINUE, SIG_RETURN } Signal;

typedef struct Var {
    const char *name;
    VKind type;          /* tipo declarado (o tipo base de los elementos si es arreglo) */
    int dims;            /* dimensiones (0 = escalar) */
    bool is_array;
    Value val;
    int rep;             /* índice en la tabla de símbolos del reporte */
    struct Var *next;
} Var;

typedef struct Scope {
    Var *vars;
    struct Scope *parent;   /* ámbito léxico (NULL en el cuerpo de una función) */
    struct Scope *caller;   /* ámbito activo antes de entrar (para desapilar) */
    int depth;
    const char *fname;
} Scope;

typedef struct { const char *name; ASTNode *node; } FuncEntry;

typedef struct {
    ASTNode *site;       /* nodo de la declaración (una fila por declaración) */
    char *id;
    const char *kind;    /* Variable, Parámetro, Constante, Función */
    int depth;
    char *func;
    char *type;
    char *value;
    int line, column;
} RepSymbol;

static FILE *g_out = NULL;
static bool g_err = false;
static long g_steps = 0;
static int g_calls = 0;
static Value g_retval;
static Scope *g_scope = NULL;
static FuncEntry *g_funcs = NULL;
static int g_nfuncs = 0;
static RepSymbol *g_rep = NULL;       /* malloc propio: sobrevive hasta interpreter_reset */
static int g_nrep = 0, g_caprep = 0;

static void rt_error(ASTNode *n, const char *fmt, ...) {
    if (g_err) return;
    char msg[512];
    va_list ap;
    va_start(ap, fmt);
    vsnprintf(msg, sizeof msg, fmt, ap);
    va_end(ap);
    add_error(ERROR_RUNTIME, msg, g_scope && g_scope->fname ? g_scope->fname : "Global",
              n ? n->line : 0, n ? n->column : 0);
    g_err = true;
}

/* ========================================================================
 * Utilidades de tipos y conversión a texto
 * ===================================================================== */

static VKind kind_from_name(const char *t) {
    if (!t) return V_VOID;
    if (!strcmp(t, "int")) return V_INT;
    if (!strcmp(t, "float")) return V_FLOAT;
    if (!strcmp(t, "double")) return V_DOUBLE;
    if (!strcmp(t, "boolean")) return V_BOOL;
    if (!strcmp(t, "char")) return V_CHAR;
    if (!strcmp(t, "String")) return V_STRING;
    return V_VOID;
}

static bool is_num(Value v) { return v.k == V_INT || v.k == V_FLOAT || v.k == V_DOUBLE || v.k == V_CHAR; }

static double as_double(Value v) {
    switch (v.k) {
        case V_INT: return (double)v.u.i;
        case V_CHAR: return (double)(unsigned char)v.u.c;
        case V_FLOAT: case V_DOUBLE: return v.u.d;
        default: return 0.0;
    }
}

static int64_t as_int64(Value v) {
    switch (v.k) {
        case V_INT: return v.u.i;
        case V_CHAR: return (unsigned char)v.u.c;
        case V_FLOAT: case V_DOUBLE: {
            double d = v.u.d;
            if (d != d) return 0;
            if (d >= 2147483647.0) return 2147483647;
            if (d <= -2147483648.0) return -2147483647LL - 1;
            return (int64_t)d;
        }
        default: return 0;
    }
}

static double d_abs(double x) { return x < 0 ? -x : x; }
static bool d_isnan(double x) { return x != x; }
static bool d_isinf(double x) { return !d_isnan(x) && d_abs(x) > 1.7976931348623157e308; }

static bool roundtrips(const char *buf, double d, bool is_float) {
    double back = strtod(buf, NULL);
    return is_float ? ((float)back == (float)d) : (back == d);
}

/* Formato de Java: 5.0, 3.14, 1.0E7 */
static const char *fmt_double(double d, bool is_float) {
    if (d_isnan(d)) return "NaN";
    if (d_isinf(d)) return d < 0 ? "-Infinity" : "Infinity";
    char buf[96];
    double a = d_abs(d);
    if (a == 0 || (a >= 1e-3 && a < 1e7)) {
        for (int p = 1; p <= 17; p++) {
            snprintf(buf, sizeof buf, "%.*f", p, d);
            if (roundtrips(buf, d, is_float)) break;
        }
    } else {
        char raw[96];
        for (int p = 0; p <= 17; p++) {
            snprintf(raw, sizeof raw, "%.*e", p, d);
            if (roundtrips(raw, d, is_float)) break;
        }
        char *e = strchr(raw, 'e');
        int ex = e ? atoi(e + 1) : 0;
        if (e) *e = '\0';
        snprintf(buf, sizeof buf, "%s%sE%d", raw, strchr(raw, '.') ? "" : ".0", ex);
    }
    return istrdup(buf);
}

static const char *value_to_string(Value v) {
    char buf[64];
    switch (v.k) {
        case V_INT: snprintf(buf, sizeof buf, "%d", v.u.i); return istrdup(buf);
        case V_FLOAT: return fmt_double(v.u.d, true);
        case V_DOUBLE: return fmt_double(v.u.d, false);
        case V_BOOL: return v.u.b ? "true" : "false";
        case V_CHAR: buf[0] = v.u.c; buf[1] = '\0'; return istrdup(buf);
        case V_STRING: return v.u.s ? v.u.s : "null";
        case V_NULL: return "null";
        case V_VOID: return "";
        case V_ARRAY: {
            Array *a = v.u.a;
            size_t cap = 3;
            const char **parts = ialloc((size_t)(a->len + 1) * sizeof(char *));
            for (int i = 0; i < a->len; i++) {
                parts[i] = value_to_string(a->items[i]);
                cap += strlen(parts[i]) + 2;
            }
            char *s = ialloc(cap + 1);
            strcat(s, "[");
            for (int i = 0; i < a->len; i++) {
                if (i) strcat(s, ", ");
                strcat(s, parts[i]);
            }
            strcat(s, "]");
            return s;
        }
    }
    return "";
}

static Value default_value(VKind t) {
    switch (t) {
        case V_INT: return mkint(0);
        case V_FLOAT: return mkfloat(0);
        case V_DOUBLE: return mkdouble(0);
        case V_BOOL: return mkbool(0);
        case V_CHAR: return mkchar('\0');
        case V_STRING: return mknull();
        default: return mknull();
    }
}

/* Convierte `v` al tipo `t` (ensanchamiento, y estrechamiento explícito en += etc.) */
static Value coerce_to(VKind t, Value v, ASTNode *n) {
    switch (t) {
        case V_INT:
            if (is_num(v)) return mkint((int32_t)as_int64(v));
            break;
        case V_FLOAT:
            if (is_num(v)) return mkfloat(as_double(v));
            break;
        case V_DOUBLE:
            if (is_num(v)) return mkdouble(as_double(v));
            break;
        case V_BOOL:
            if (v.k == V_BOOL) return v;
            break;
        case V_CHAR:
            if (v.k == V_CHAR) return v;
            if (is_num(v)) return mkchar((char)as_int64(v));
            break;
        case V_STRING:
            if (v.k == V_STRING || v.k == V_NULL) return v;
            break;
        default:
            return v;
    }
    rt_error(n, "Tipo incompatible en tiempo de ejecución");
    return mkvoid();
}

static bool values_equal(Value a, Value b) {
    if (is_num(a) && is_num(b)) {
        if ((a.k == V_INT || a.k == V_CHAR) && (b.k == V_INT || b.k == V_CHAR))
            return as_int64(a) == as_int64(b);
        return as_double(a) == as_double(b);
    }
    if (a.k == V_BOOL && b.k == V_BOOL) return a.u.b == b.u.b;
    if (a.k == V_STRING && b.k == V_STRING) return strcmp(a.u.s ? a.u.s : "", b.u.s ? b.u.s : "") == 0;
    if (a.k == V_NULL || b.k == V_NULL) return a.k == b.k;
    if (a.k == V_ARRAY && b.k == V_ARRAY) return a.u.a == b.u.a;
    return false;
}

/* ========================================================================
 * Tabla de símbolos (reporte) y ámbitos
 * ===================================================================== */

static const char *kind_name(VKind k) {
    switch (k) {
        case V_INT: return "int";
        case V_FLOAT: return "float";
        case V_DOUBLE: return "double";
        case V_BOOL: return "boolean";
        case V_CHAR: return "char";
        case V_STRING: return "String";
        default: return "void";
    }
}

static int rep_add_typed(ASTNode *site, const char *kind, const char *id, int depth, const char *func,
                         const char *type_name, int dims) {
    for (int i = 0; i < g_nrep; i++)
        if (g_rep[i].site == site) return i;    /* misma declaración (p. ej. en un bucle) */
    if (g_nrep == g_caprep) {
        g_caprep = g_caprep ? g_caprep * 2 : 32;
        g_rep = realloc(g_rep, (size_t)g_caprep * sizeof(RepSymbol));
    }
    RepSymbol *r = &g_rep[g_nrep];
    memset(r, 0, sizeof *r);
    r->site = site;
    r->id = strdup(id);
    r->kind = kind;
    r->depth = depth;
    r->func = strdup(func ? func : "Global");
    char t[64];
    snprintf(t, sizeof t, "%s", type_name);
    for (int d = 0; d < dims && strlen(t) < 58; d++) strcat(t, "[]");
    r->type = strdup(t);
    r->value = strdup("");
    r->line = site ? site->line : 0;
    r->column = site ? site->column : 0;
    return g_nrep++;
}

static int rep_add(ASTNode *site, const char *kind, const char *id, int depth, const char *func,
                   VKind type, int dims) {
    return rep_add_typed(site, kind, id, depth, func, kind_name(type), dims);
}

static void rep_set_value(int idx, Value v) {
    if (idx < 0 || idx >= g_nrep) return;
    free(g_rep[idx].value);
    g_rep[idx].value = strdup(value_to_string(v));
}

static Scope *push_scope(Scope *lexical_parent, const char *fname) {
    Scope *s = ialloc(sizeof(Scope));
    s->parent = lexical_parent;
    s->caller = g_scope;
    s->depth = lexical_parent ? lexical_parent->depth + 1 : 0;
    s->fname = fname;
    g_scope = s;
    return s;
}

static void pop_scope(void) {
    Scope *s = g_scope;
    if (!s) return;
    for (Var *v = s->vars; v; v = v->next) rep_set_value(v->rep, v->val);
    g_scope = s->caller;
}

static Var *lookup_var(const char *name) {
    for (Scope *s = g_scope; s; s = s->parent)
        for (Var *v = s->vars; v; v = v->next)
            if (strcmp(v->name, name) == 0) return v;
    return NULL;
}

static Var *declare_var(ASTNode *site, const char *kind, const char *name, VKind type, int dims, Value val) {
    Var *v = ialloc(sizeof(Var));
    v->name = istrdup(name);
    v->type = type;
    v->dims = dims;
    v->is_array = dims > 0;
    v->val = val;
    v->rep = rep_add(site, kind, name, g_scope->depth, g_scope->fname, type, dims);
    v->next = g_scope->vars;
    g_scope->vars = v;
    rep_set_value(v->rep, val);
    return v;
}

static void register_function(ASTNode *fn, const char *scope_name) {
    for (int i = 0; i < g_nfuncs; i++)
        if (g_funcs[i].node == fn) return;
    {   /* fila de la tabla de símbolos: nombre, "Función", tipo de retorno, ámbito, posición y firma */
        int idx = rep_add_typed(fn, "Función", fn->data.func_decl.name, 0, scope_name,
                                fn->data.func_decl.return_type, 0);
        char sig[256] = "(";
        ASTNode *ps = fn->data.func_decl.parameters;
        int np = (ps && ps->type == NODE_LIST) ? ps->data.list.count : 0;
        for (int i = 0; i < np; i++) {
            ASTNode *p = ps->data.list.items[i];
            char one[96];
            snprintf(one, sizeof one, "%s%s%s %s", i ? ", " : "", p->data.parameter.data_type,
                     p->data.parameter.dims > 1 ? "[][]" : (p->data.parameter.dims ? "[]" : ""),
                     p->data.parameter.name);
            if (strlen(sig) + strlen(one) < sizeof sig - 2) strcat(sig, one);
        }
        strcat(sig, ")");
        free(g_rep[idx].value);
        g_rep[idx].value = strdup(sig);
    }
    g_funcs = realloc(g_funcs, (size_t)(g_nfuncs + 1) * sizeof(FuncEntry));
    g_funcs[g_nfuncs].name = fn->data.func_decl.name;
    g_funcs[g_nfuncs].node = fn;
    g_nfuncs++;
}

static ASTNode *find_function(const char *name) {
    for (int i = g_nfuncs - 1; i >= 0; i--)
        if (strcmp(g_funcs[i].name, name) == 0) return g_funcs[i].node;
    return NULL;
}

/* ========================================================================
 * Evaluación de expresiones
 * ===================================================================== */

static Value eval(ASTNode *n);
static Signal exec(ASTNode *n);

static Value arith(const char *op, Value a, Value b, ASTNode *n) {
    bool both_int = (a.k == V_INT || a.k == V_CHAR) && (b.k == V_INT || b.k == V_CHAR);
    if (both_int) {
        int64_t x = as_int64(a), y = as_int64(b), r = 0;
        switch (op[0]) {
            case '+': r = x + y; break;
            case '-': r = x - y; break;
            case '*': r = x * y; break;
            case '/':
                if (y == 0) { rt_error(n, "División entre cero"); return mkvoid(); }
                r = x / y; break;
            case '%':
                if (y == 0) { rt_error(n, "División entre cero (módulo)"); return mkvoid(); }
                r = x % y; break;
        }
        return mkint((int32_t)r);
    }
    double x = as_double(a), y = as_double(b), r = 0;
    switch (op[0]) {
        case '+': r = x + y; break;
        case '-': r = x - y; break;
        case '*': r = x * y; break;
        case '/': r = (y == 0) ? (x == 0 || d_isnan(x) ? (y / y) : (x < 0 ? -1.0 : 1.0) / 0.0) : x / y; break;
        case '%': r = (y == 0) ? (y / y) : x - (double)(long long)(x / y) * y; break;
    }
    if (a.k == V_DOUBLE || b.k == V_DOUBLE) return mkdouble(r);
    return mkfloat(r);
}

static Value binary_values(const char *op, Value l, Value r, ASTNode *n) {
    if (!strcmp(op, "+") && (l.k == V_STRING || r.k == V_STRING ||
                             ((l.k == V_NULL || r.k == V_NULL) && !(is_num(l) || is_num(r))))) {
        const char *a = value_to_string(l), *b = value_to_string(r);
        char *s = ialloc(strlen(a) + strlen(b) + 1);
        strcpy(s, a);
        strcat(s, b);
        return mkstr(s);
    }
    if (!strcmp(op, "+") || !strcmp(op, "-") || !strcmp(op, "*") || !strcmp(op, "/") || !strcmp(op, "%")) {
        if (!is_num(l) || !is_num(r)) { rt_error(n, "Operandos no numéricos para '%s'", op); return mkvoid(); }
        return arith(op, l, r, n);
    }
    if (!strcmp(op, "==")) return mkbool(values_equal(l, r));
    if (!strcmp(op, "!=")) return mkbool(!values_equal(l, r));
    if (!strcmp(op, "<") || !strcmp(op, "<=") || !strcmp(op, ">") || !strcmp(op, ">=")) {
        if (!is_num(l) || !is_num(r)) { rt_error(n, "Operandos no numéricos para '%s'", op); return mkvoid(); }
        bool both_int = (l.k == V_INT || l.k == V_CHAR) && (r.k == V_INT || r.k == V_CHAR);
        double x = both_int ? (double)as_int64(l) : as_double(l);
        double y = both_int ? (double)as_int64(r) : as_double(r);
        if (!strcmp(op, "<")) return mkbool(x < y);
        if (!strcmp(op, "<=")) return mkbool(x <= y);
        if (!strcmp(op, ">")) return mkbool(x > y);
        return mkbool(x >= y);
    }
    if (!strcmp(op, "&") || !strcmp(op, "|") || !strcmp(op, "^")) {
        if (l.k == V_BOOL && r.k == V_BOOL) {
            int a = l.u.b, b = r.u.b;
            return mkbool(op[0] == '&' ? (a & b) : op[0] == '|' ? (a | b) : (a ^ b));
        }
        if ((l.k == V_INT || l.k == V_CHAR) && (r.k == V_INT || r.k == V_CHAR)) {
            int32_t a = (int32_t)as_int64(l), b = (int32_t)as_int64(r);
            return mkint(op[0] == '&' ? (a & b) : op[0] == '|' ? (a | b) : (a ^ b));
        }
        rt_error(n, "Operandos inválidos para '%s'", op);
        return mkvoid();
    }
    if (!strcmp(op, "<<") || !strcmp(op, ">>")) {
        if ((l.k != V_INT && l.k != V_CHAR) || (r.k != V_INT && r.k != V_CHAR)) {
            rt_error(n, "Operandos inválidos para '%s'", op);
            return mkvoid();
        }
        int32_t a = (int32_t)as_int64(l);
        int sh = (int)(as_int64(r) & 31);
        return mkint(op[0] == '<' ? (int32_t)((uint32_t)a << sh) : (a >> sh));
    }
    rt_error(n, "Operador desconocido '%s'", op);
    return mkvoid();
}

/* --- valores asignables: variable o elemento de arreglo --- */

typedef struct { Var *v; Array *a; int idx; } LVal;

static bool lval_resolve(ASTNode *n, LVal *lv) {
    memset(lv, 0, sizeof *lv);
    if (n->type == NODE_IDENTIFIER) {
        lv->v = lookup_var(n->data.identifier.name);
        if (!lv->v) { rt_error(n, "Variable '%s' no existe en tiempo de ejecución", n->data.identifier.name); return false; }
        return true;
    }
    if (n->type == NODE_ARRAY_ACCESS) {
        Value arr = eval(n->data.array_access.array);
        if (g_err) return false;
        Value idx = eval(n->data.array_access.index);
        if (g_err) return false;
        if (arr.k == V_NULL) { rt_error(n, "Acceso a un arreglo nulo"); return false; }
        if (arr.k != V_ARRAY) { rt_error(n, "El valor no es un arreglo"); return false; }
        if (idx.k != V_INT && idx.k != V_CHAR) { rt_error(n, "El índice debe ser entero"); return false; }
        int64_t i = as_int64(idx);
        if (i < 0 || i >= arr.u.a->len) {
            rt_error(n, "Índice %lld fuera de rango (longitud %d)", (long long)i, arr.u.a->len);
            return false;
        }
        lv->a = arr.u.a;
        lv->idx = (int)i;
        return true;
    }
    rt_error(n, "Expresión no asignable");
    return false;
}

static Value lval_get(LVal *lv) { return lv->v ? lv->v->val : lv->a->items[lv->idx]; }

static void lval_set(LVal *lv, Value v, ASTNode *n) {
    if (lv->v) {
        if (lv->v->is_array) {
            if (v.k != V_ARRAY && v.k != V_NULL) { rt_error(n, "Se esperaba un arreglo"); return; }
            lv->v->val = v;
        } else {
            Value c = coerce_to(lv->v->type, v, n);
            if (!g_err) lv->v->val = c;
        }
    } else if (lv->a->dims > 1) {
        if (v.k != V_ARRAY && v.k != V_NULL) { rt_error(n, "Se esperaba un arreglo"); return; }
        lv->a->items[lv->idx] = v;
    } else {
        Value c = coerce_to(lv->a->base, v, n);
        if (!g_err) lv->a->items[lv->idx] = c;
    }
}

static VKind lval_kind(LVal *lv) { return lv->v ? lv->v->type : (lv->a->dims > 1 ? V_ARRAY : lv->a->base); }
static bool lval_is_array(LVal *lv) { return lv->v ? lv->v->is_array : lv->a->dims > 1; }

static Value eval_assignment(ASTNode *n) {
    ASTNode *left = n->data.assignment.left;
    const char *op = n->data.assignment.operator;
    LVal lv;
    Value rhs = eval(n->data.assignment.right);
    if (g_err) return mkvoid();
    if (!lval_resolve(left, &lv)) return mkvoid();
    Value result = rhs;
    if (op && strcmp(op, "=") != 0) {
        char bop[4] = { 0 };
        size_t blen = strlen(op) - 1;                    /* "<<=" -> "<<", "+=" -> "+" */
        memcpy(bop, op, blen < 3 ? blen : 3);
        Value cur = lval_get(&lv);
        result = binary_values(bop, cur, rhs, n);
        if (g_err) return mkvoid();
        if (lval_kind(&lv) != V_STRING && !lval_is_array(&lv)) {
            result = coerce_to(lval_kind(&lv), result, n);   /* cast implícito de +=, -=, ... */
            if (g_err) return mkvoid();
        }
    }
    lval_set(&lv, result, n);
    return g_err ? mkvoid() : lval_get(&lv);
}

static Value eval_unary(ASTNode *n) {
    const char *op = n->data.unary_op.operator;
    ASTNode *operand = n->data.unary_op.operand;

    if (!strcmp(op, "++") || !strcmp(op, "--")) {
        LVal lv;
        if (!lval_resolve(operand, &lv)) return mkvoid();
        Value old = lval_get(&lv);
        if (!is_num(old)) { rt_error(n, "'%s' requiere un valor numérico", op); return mkvoid(); }
        Value neu = arith(op[0] == '+' ? "+" : "-", old, mkint(1), n);
        if (g_err) return mkvoid();
        lval_set(&lv, neu, n);
        if (g_err) return mkvoid();
        return n->data.unary_op.is_prefix ? lval_get(&lv) : old;
    }

    Value v = eval(operand);
    if (g_err) return mkvoid();
    if (op[0] == '(') {                                    /* cast: (tipo) expresión */
        char tn[24];
        size_t len = strcspn(op + 1, ")");
        snprintf(tn, sizeof tn, "%.*s", (int)(len < 23 ? len : 23), op + 1);
        VKind tk = kind_from_name(tn);
        if (tk == V_STRING || tk == V_BOOL) return v;      /* (String) null, (boolean) b */
        return coerce_to(tk, v, n);                        /* (int) 0.5f -> 0 */
    }
    if (!strcmp(op, "!")) {
        if (v.k != V_BOOL) { rt_error(n, "'!' requiere un booleano"); return mkvoid(); }
        return mkbool(!v.u.b);
    }
    if (!strcmp(op, "~")) {
        if (v.k != V_INT && v.k != V_CHAR) { rt_error(n, "'~' requiere un entero"); return mkvoid(); }
        return mkint(~(int32_t)as_int64(v));
    }
    if (!strcmp(op, "-") || !strcmp(op, "+")) {
        if (!is_num(v)) { rt_error(n, "Operador unario requiere un número"); return mkvoid(); }
        if (op[0] == '+') return (v.k == V_CHAR) ? mkint((int32_t)as_int64(v)) : v;
        if (v.k == V_INT || v.k == V_CHAR) return mkint((int32_t)(-as_int64(v)));
        return v.k == V_FLOAT ? mkfloat(-v.u.d) : mkdouble(-v.u.d);
    }
    rt_error(n, "Operador unario desconocido '%s'", op);
    return mkvoid();
}

static Value eval_binary(ASTNode *n) {
    const char *op = n->data.binary_op.operator;
    if (!strcmp(op, "&&") || !strcmp(op, "||")) {
        Value l = eval(n->data.binary_op.left);
        if (g_err) return mkvoid();
        if (l.k != V_BOOL) { rt_error(n, "'%s' requiere booleanos", op); return mkvoid(); }
        if (op[0] == '&' && !l.u.b) return mkbool(0);   /* cortocircuito */
        if (op[0] == '|' && l.u.b) return mkbool(1);
        Value r = eval(n->data.binary_op.right);
        if (g_err) return mkvoid();
        if (r.k != V_BOOL) { rt_error(n, "'%s' requiere booleanos", op); return mkvoid(); }
        return mkbool(r.u.b);
    }
    Value l = eval(n->data.binary_op.left);
    if (g_err) return mkvoid();
    Value r = eval(n->data.binary_op.right);
    if (g_err) return mkvoid();
    return binary_values(op, l, r, n);
}

/* Reserva un arreglo de `dims` dimensiones con longitudes lens[level..] y valores por defecto */
static Array *alloc_nd(VKind base, int dims, const int *lens, int level) {
    Array *a = ialloc(sizeof(Array));
    a->base = base;
    a->dims = dims;
    a->len = lens[level];
    a->items = ialloc((size_t)(a->len + 1) * sizeof(Value));
    for (int i = 0; i < a->len; i++)
        a->items[i] = (dims == 1) ? default_value(base) : mkarray(alloc_nd(base, dims - 1, lens, level + 1));
    return a;
}

/* Literal {…}: anidado una vez por dimensión */
static Value build_literal(ASTNode *lit, VKind base, int dims, ASTNode *site) {
    ASTNode *vals = lit->data.array_init.values;
    Array *arr = ialloc(sizeof(Array));
    arr->base = base;
    arr->dims = dims;
    arr->len = (vals && vals->type == NODE_LIST) ? vals->data.list.count : 0;
    arr->items = ialloc((size_t)(arr->len + 1) * sizeof(Value));
    for (int i = 0; i < arr->len; i++) {
        ASTNode *el = vals->data.list.items[i];
        Value v;
        if (dims > 1 && el->type == NODE_ARRAY_INIT && !el->data.array_init.size) {
            v = build_literal(el, base, dims - 1, site);
        } else {
            v = eval(el);
            if (g_err) return mkvoid();
            if (dims > 1) {
                if (v.k != V_ARRAY && v.k != V_NULL) { rt_error(site, "Se esperaba un arreglo en la posición %d", i); return mkvoid(); }
            } else {
                v = coerce_to(base, v, site);
            }
        }
        if (g_err) return mkvoid();
        arr->items[i] = v;
    }
    return mkarray(arr);
}

/* new tipo[a][b]… */
static Value build_new_array(ASTNode *init, VKind base, int dims, ASTNode *site) {
    ASTNode *sizes = init->data.array_init.size;
    int nd = (sizes && sizes->type == NODE_LIST) ? sizes->data.list.count : 0;
    if (nd != dims || nd < 1 || nd > 16) { rt_error(site, "Dimensiones inválidas en la creación del arreglo"); return mkvoid(); }
    int lens[16];
    double total = 1;
    for (int i = 0; i < nd; i++) {
        Value sv = eval(sizes->data.list.items[i]);
        if (g_err) return mkvoid();
        if (sv.k != V_INT && sv.k != V_CHAR) { rt_error(site, "El tamaño del arreglo debe ser entero"); return mkvoid(); }
        int64_t len = as_int64(sv);
        if (len < 0) { rt_error(site, "Tamaño de arreglo negativo (%lld)", (long long)len); return mkvoid(); }
        lens[i] = (int)len;
        total *= (double)len;
    }
    if (total > 10000000.0) { rt_error(site, "Arreglo demasiado grande"); return mkvoid(); }
    return mkarray(alloc_nd(base, dims, lens, 0));
}

static Value make_array(ASTNode *init, VKind base, int dims, ASTNode *site) {
    if (init->data.array_init.size) return build_new_array(init, base, dims, site);
    return build_literal(init, base, dims, site);
}

static Value new_array_with(Array *src, Value extra, ASTNode *site) {
    Array *a = ialloc(sizeof(Array));
    a->base = src->base;
    a->dims = src->dims;
    a->len = src->len + 1;
    a->items = ialloc((size_t)(a->len + 1) * sizeof(Value));
    for (int i = 0; i < src->len; i++) a->items[i] = src->items[i];
    if (src->dims > 1) {
        if (extra.k != V_ARRAY && extra.k != V_NULL) { rt_error(site, "Se esperaba un arreglo para agregar"); return mkvoid(); }
        a->items[src->len] = extra;
    } else {
        Value c = coerce_to(src->base, extra, site);
        if (g_err) return mkvoid();
        a->items[src->len] = c;
    }
    return mkarray(a);
}

static int collect_args(ASTNode *args, Value *out, ASTNode *call) {
    if (!args) return 0;
    if (args->type == NODE_LIST) {
        int n = args->data.list.count;
        if (n > MAX_ARGS) { rt_error(call, "Demasiados argumentos (máx. %d)", MAX_ARGS); return -1; }
        for (int i = 0; i < n; i++) {
            out[i] = eval(args->data.list.items[i]);
            if (g_err) return -1;
        }
        return n;
    }
    out[0] = eval(args);
    return g_err ? -1 : 1;
}

static void print_args(Value *argv, int argc) {
    for (int i = 0; i < argc; i++) {
        if (i) fputc(' ', g_out);
        fputs(value_to_string(argv[i]), g_out);
    }
}

static bool parse_number(const char *s, bool integer, double *out) {
    if (!s) return false;
    while (*s == ' ' || *s == '\t' || *s == '\n') s++;
    if (!*s) return false;
    char *end;
    if (integer) {
        long long v = strtoll(s, &end, 10);
        if (v > 2147483647LL || v < -2147483648LL) return false;
        *out = (double)v;
    } else {
        *out = strtod(s, &end);
    }
    while (*end == ' ' || *end == '\t' || *end == '\n') end++;
    return *end == '\0';
}

static Value call_function(ASTNode *call) {
    const char *name = call->data.func_call.name;
    Value argv[MAX_ARGS];
    int argc = collect_args(call->data.func_call.arguments, argv, call);
    if (argc < 0) return mkvoid();

    if (!strcmp(name, "System.out.println") || !strcmp(name, "println")) { print_args(argv, argc); fputc('\n', g_out); return mkvoid(); }
    if (!strcmp(name, "System.out.print") || !strcmp(name, "print")) { print_args(argv, argc); return mkvoid(); }
    if (!strcmp(name, "String.valueOf") && argc == 1) return mkstr(value_to_string(argv[0]));
    if (!strcmp(name, "String.join")) {
        if (argc < 2 || argv[0].k != V_STRING) { rt_error(call, "String.join requiere un delimitador String"); return mkvoid(); }
        const char *delim = argv[0].u.s ? argv[0].u.s : "";
        int count = argc - 1;
        Value *items = argv + 1;
        if (argc == 2 && argv[1].k == V_ARRAY) { count = argv[1].u.a->len; items = argv[1].u.a->items; }
        else if (argc == 2 && argv[1].k == V_NULL) { rt_error(call, "String.join sobre un arreglo nulo"); return mkvoid(); }
        size_t cap = 1;
        const char **parts = ialloc((size_t)(count + 1) * sizeof(char *));
        for (int i = 0; i < count; i++) { parts[i] = value_to_string(items[i]); cap += strlen(parts[i]) + strlen(delim); }
        char *out = ialloc(cap + 1);
        for (int i = 0; i < count; i++) { if (i) strcat(out, delim); strcat(out, parts[i]); }
        return mkstr(out);
    }
    if (!strcmp(name, "Arrays.indexOf")) {
        if (argc != 2 || argv[0].k == V_NULL) { rt_error(call, "Arrays.indexOf sobre un arreglo nulo"); return mkvoid(); }
        if (argv[0].k != V_ARRAY) { rt_error(call, "Arrays.indexOf requiere un arreglo"); return mkvoid(); }
        Array *arr = argv[0].u.a;
        for (int i = 0; i < arr->len; i++)
            if (values_equal(arr->items[i], argv[1])) return mkint(i);
        return mkint(-1);
    }
    if (!strcmp(name, "Integer.parseInt") || !strcmp(name, "Float.parseFloat") ||
        !strcmp(name, "Double.parseDouble")) {
        double d;
        bool is_int = (name[0] == 'I');
        if (argc != 1 || argv[0].k != V_STRING || !parse_number(argv[0].u.s, is_int, &d)) {
            rt_error(call, "%s: cadena con formato inválido '%s'", name,
                     argc == 1 ? value_to_string(argv[0]) : "");
            return mkvoid();
        }
        if (is_int) return mkint((int32_t)d);
        return name[0] == 'F' ? mkfloat(d) : mkdouble(d);
    }

    ASTNode *fn = find_function(name);
    if (!fn) { rt_error(call, "Función '%s' no definida", name); return mkvoid(); }

    ASTNode *params = fn->data.func_decl.parameters;
    int nparams = (params && params->type == NODE_LIST) ? params->data.list.count : 0;
    if (nparams != argc) {
        rt_error(call, "La función '%s' espera %d argumentos y recibió %d", name, nparams, argc);
        return mkvoid();
    }
    if (g_calls >= MAX_CALL_DEPTH) {
        rt_error(call, "Desbordamiento de pila (recursión demasiado profunda en '%s')", name);
        return mkvoid();
    }

    g_calls++;
    push_scope(NULL, fn->data.func_decl.name);
    for (int i = 0; i < nparams && !g_err; i++) {
        ASTNode *p = params->data.list.items[i];
        VKind pk = kind_from_name(p->data.parameter.data_type);
        Value av = argv[i];
        if (p->data.parameter.dims > 0) {
            if (av.k != V_ARRAY && av.k != V_NULL) rt_error(call, "Se esperaba un arreglo en el argumento %d", i + 1);
        } else {
            av = coerce_to(pk, av, call);
        }
        if (!g_err) declare_var(p, "Parámetro", p->data.parameter.name, pk, p->data.parameter.dims, av);
    }

    Value rv = mkvoid();
    if (!g_err) {
        g_retval = mkvoid();
        ASTNode *body = fn->data.func_decl.body;
        /* el cuerpo se ejecuta en el mismo ámbito que los parámetros */
        if (body && body->type == NODE_LIST) {
            for (int i = 0; i < body->data.list.count; i++)
                if (body->data.list.items[i]->type == NODE_FUNCTION_DECL) register_function(body->data.list.items[i], g_scope->fname);
            for (int i = 0; i < body->data.list.count && !g_err; i++) {
                Signal s = exec(body->data.list.items[i]);
                if (s == SIG_RETURN) { rv = g_retval; break; }
                if (s != SIG_NONE) break;
            }
        }
        VKind rk = kind_from_name(fn->data.func_decl.return_type);
        if (!g_err && rk != V_VOID) {
            if (rv.k == V_VOID) rt_error(call, "La función '%s' terminó sin devolver un valor", name);
            else rv = coerce_to(rk, rv, call);
        }
        if (!g_err && rk == V_VOID) rv = mkvoid();
    }
    pop_scope();
    g_calls--;
    return rv;
}

static Value eval(ASTNode *n) {
    if (g_err || !n) return mkvoid();
    switch (n->type) {
        case NODE_INT_LITERAL:     return mkint(n->data.int_literal.value);
        case NODE_FLOAT_LITERAL:   return mkfloat(n->data.float_literal.value);
        case NODE_STRING_LITERAL:  return mkstr(n->data.string_literal.value);
        case NODE_CHAR_LITERAL:    return mkchar(n->data.char_literal.value);
        case NODE_BOOLEAN_LITERAL: return mkbool(n->data.boolean_literal.value);
        case NODE_NULL_LITERAL:    return mknull();
        case NODE_IDENTIFIER: {
            Var *v = lookup_var(n->data.identifier.name);
            if (!v) { rt_error(n, "Variable '%s' no existe en tiempo de ejecución", n->data.identifier.name); return mkvoid(); }
            return v->val;
        }
        case NODE_ARRAY_ACCESS: {
            LVal lv;
            if (!lval_resolve(n, &lv)) return mkvoid();
            return lval_get(&lv);
        }
        case NODE_MEMBER_ACCESS: {
            Value obj = eval(n->data.member_access.object);
            if (g_err) return mkvoid();
            if (!strcmp(n->data.member_access.member, "length")) {
                if (obj.k == V_NULL) { rt_error(n, "No se puede leer length de un arreglo nulo"); return mkvoid(); }
                if (obj.k == V_ARRAY) return mkint(obj.u.a->len);
            }
            rt_error(n, "El miembro '%s' no existe", n->data.member_access.member);
            return mkvoid();
        }
        case NODE_METHOD_CALL: {
            const char *mname = n->data.method_call.name;
            Value obj = eval(n->data.method_call.object);
            if (g_err) return mkvoid();
            Value argv[MAX_ARGS];
            int argc = collect_args(n->data.method_call.arguments, argv, n);
            if (argc < 0) return mkvoid();
            if (!strcmp(mname, "add") && argc == 1) {
                if (obj.k == V_NULL) { rt_error(n, "No se puede usar add sobre un arreglo nulo"); return mkvoid(); }
                if (obj.k == V_ARRAY) return new_array_with(obj.u.a, argv[0], n);
            }
            if (!strcmp(mname, "equals") && argc == 1) {
                if (obj.k == V_NULL) { rt_error(n, "No se puede llamar a equals sobre un valor nulo"); return mkvoid(); }
                if (obj.k == V_STRING) return mkbool(values_equal(obj, argv[0]));
            }
            rt_error(n, "El método '%s' no existe", mname);
            return mkvoid();
        }
        case NODE_ASSIGNMENT:    return eval_assignment(n);
        case NODE_UNARY_OP:      return eval_unary(n);
        case NODE_BINARY_OP:     return eval_binary(n);
        case NODE_FUNCTION_CALL: return call_function(n);
        default:
            rt_error(n, "Expresión no soportada en ejecución (nodo %d)", n->type);
            return mkvoid();
    }
}

/* ========================================================================
 * Ejecución de sentencias
 * ===================================================================== */

static bool eval_condition(ASTNode *cond, ASTNode *where, const char *what) {
    Value c = eval(cond);
    if (g_err) return false;
    if (c.k != V_BOOL) { rt_error(where, "La condición del %s debe ser booleana", what); return false; }
    return c.u.b != 0;
}

/* Ejecuta las sentencias de una lista en el ámbito actual */
static Signal exec_list_here(ASTNode *list) {
    if (!list || list->type != NODE_LIST) return exec(list);
    for (int i = 0; i < list->data.list.count; i++)
        if (list->data.list.items[i] && list->data.list.items[i]->type == NODE_FUNCTION_DECL)
            register_function(list->data.list.items[i], g_scope && g_scope->fname ? g_scope->fname : "Global");
    for (int i = 0; i < list->data.list.count && !g_err; i++) {
        Signal s = exec(list->data.list.items[i]);
        if (s != SIG_NONE) return s;
    }
    return SIG_NONE;
}

static Signal exec_block(ASTNode *list) {
    if (!list) return SIG_NONE;
    if (list->type != NODE_LIST) return exec(list);
    push_scope(g_scope, g_scope ? g_scope->fname : "Global");
    Signal s = exec_list_here(list);
    pop_scope();
    return s;
}

static Signal exec_for(ASTNode *n) {
    push_scope(g_scope, g_scope->fname);
    Signal result = SIG_NONE;
    if (n->data.for_stmt.init) exec(n->data.for_stmt.init);
    while (!g_err) {
        if (n->data.for_stmt.condition && !eval_condition(n->data.for_stmt.condition, n, "for")) break;
        if (g_err) break;
        Signal s = exec(n->data.for_stmt.body);
        if (s == SIG_BREAK) break;
        if (s == SIG_RETURN) { result = s; break; }
        if (n->data.for_stmt.update) eval(n->data.for_stmt.update);
    }
    pop_scope();
    return result;
}

static Signal exec_switch(ASTNode *n) {
    Value key = eval(n->data.switch_stmt.expression);
    if (g_err) return SIG_NONE;
    ASTNode *cases = n->data.switch_stmt.cases;
    if (!cases || cases->type != NODE_LIST) return SIG_NONE;
    int start = -1, def = -1;
    for (int i = 0; i < cases->data.list.count && start < 0; i++) {
        ASTNode *c = cases->data.list.items[i];
        if (!c->data.case_stmt.value) { def = i; continue; }
        Value cv = eval(c->data.case_stmt.value);
        if (g_err) return SIG_NONE;
        if (values_equal(key, cv)) start = i;
    }
    if (start < 0) start = def;
    if (start < 0) return SIG_NONE;
    for (int i = start; i < cases->data.list.count && !g_err; i++) {
        Signal s = exec(cases->data.list.items[i]->data.case_stmt.statements);
        if (s == SIG_BREAK) return SIG_NONE;
        if (s != SIG_NONE) return s;
    }
    return SIG_NONE;
}

static Signal exec(ASTNode *n) {
    if (g_err || !n) return SIG_NONE;
    if (++g_steps > MAX_STEPS) {
        rt_error(n, "Límite de ejecución excedido (%d pasos): ¿bucle infinito?", MAX_STEPS);
        return SIG_NONE;
    }
    switch (n->type) {
        case NODE_LIST:
            return exec_block(n);

        case NODE_FUNCTION_DECL:
            register_function(n, g_scope && g_scope->fname ? g_scope->fname : "Global");
            return SIG_NONE;

        case NODE_VAR_DECL: {
            VKind t = kind_from_name(n->data.var_decl.data_type);
            bool is_arr = n->data.var_decl.is_array;
            int dims = is_arr ? n->data.var_decl.array_size : 0;
            ASTNode *init = n->data.var_decl.init_value;
            Value val;
            if (!init) {
                val = is_arr ? mknull() : default_value(t);
            } else if (init->type == NODE_ARRAY_INIT) {
                val = make_array(init, t, dims, n);
            } else {
                val = eval(init);
                if (!g_err) {
                    if (is_arr) {
                        if (val.k != V_ARRAY && val.k != V_NULL) rt_error(n, "Se esperaba un arreglo");
                    } else {
                        val = coerce_to(t, val, n);
                    }
                }
            }
            if (!g_err) declare_var(n, n->data.var_decl.is_const ? "Constante" : "Variable",
                                    n->data.var_decl.name, t, dims, val);
            return SIG_NONE;
        }

        case NODE_FOREACH_STMT: {
            Value it = eval(n->data.foreach_stmt.iterable);
            if (g_err) return SIG_NONE;
            if (it.k == V_NULL) { rt_error(n, "No se puede recorrer un arreglo nulo"); return SIG_NONE; }
            if (it.k != V_ARRAY) { rt_error(n, "El for-each requiere un arreglo"); return SIG_NONE; }
            Array *arr = it.u.a;
            int count = arr->len;                         /* longitud fija durante el recorrido */
            VKind vt = kind_from_name(n->data.foreach_stmt.data_type);
            int vdims = n->data.foreach_stmt.dims;
            for (int i = 0; i < count && !g_err; i++) {
                Value el = arr->items[i];
                if (vdims == 0) el = coerce_to(vt, el, n);
                if (g_err) break;
                push_scope(g_scope, g_scope->fname);
                declare_var(n, "Variable", n->data.foreach_stmt.name, vt, vdims, el);
                Signal s = exec(n->data.foreach_stmt.body);
                pop_scope();
                if (s == SIG_BREAK) break;
                if (s == SIG_RETURN) return s;
            }
            return SIG_NONE;
        }

        case NODE_ASSIGNMENT:
            eval_assignment(n);
            return SIG_NONE;

        case NODE_EXPRESSION_STMT:
            eval(n->data.program.body);
            return SIG_NONE;

        case NODE_IF_STMT: {
            bool c = eval_condition(n->data.if_stmt.condition, n, "if");
            if (g_err) return SIG_NONE;
            if (c) return exec(n->data.if_stmt.then_stmt);
            if (n->data.if_stmt.else_stmt) return exec(n->data.if_stmt.else_stmt);
            return SIG_NONE;
        }

        case NODE_WHILE_STMT:
            while (!g_err && eval_condition(n->data.while_stmt.condition, n, "while")) {
                Signal s = exec(n->data.while_stmt.body);
                if (s == SIG_BREAK) break;
                if (s == SIG_RETURN) return s;
            }
            return SIG_NONE;

        case NODE_DO_WHILE_STMT:
            do {
                Signal s = exec(n->data.while_stmt.body);
                if (s == SIG_BREAK) break;
                if (s == SIG_RETURN) return s;
            } while (!g_err && eval_condition(n->data.while_stmt.condition, n, "do-while"));
            return SIG_NONE;

        case NODE_FOR_STMT:
            return exec_for(n);

        case NODE_SWITCH_STMT:
            return exec_switch(n);

        case NODE_BREAK_STMT:
            return SIG_BREAK;

        case NODE_CONTINUE_STMT:
            return SIG_CONTINUE;

        case NODE_RETURN_STMT:
            g_retval = n->data.return_stmt.value ? eval(n->data.return_stmt.value) : mkvoid();
            return g_err ? SIG_NONE : SIG_RETURN;

        case NODE_BINARY_OP:
        case NODE_UNARY_OP:
        case NODE_FUNCTION_CALL:
            eval(n);
            return SIG_NONE;

        default:
            rt_error(n, "Sentencia no soportada en ejecución (nodo %d)", n->type);
            return SIG_NONE;
    }
}

/* ========================================================================
 * API pública
 * ===================================================================== */

void interpreter_reset(void) {
    for (int i = 0; i < g_nrep; i++) {
        free(g_rep[i].id);
        free(g_rep[i].func);
        free(g_rep[i].type);
        free(g_rep[i].value);
    }
    free(g_rep);
    g_rep = NULL;
    g_nrep = g_caprep = 0;
    free(g_funcs);
    g_funcs = NULL;
    g_nfuncs = 0;
    arena_free_all();
    g_scope = NULL;
    g_err = false;
    g_steps = 0;
    g_calls = 0;
}

int interpret_program(ASTNode *root, FILE *out) {
    interpreter_reset();
    g_out = out ? out : stdout;
    g_retval = mkvoid();

    ASTNode *main_node = NULL;
    ASTNode *body = (root && root->type == NODE_PROGRAM) ? root->data.program.body : NULL;
    if (body && body->type == NODE_LIST) {
        for (int i = 0; i < body->data.list.count; i++) {
            ASTNode *item = body->data.list.items[i];
            if (item->type == NODE_FUNCTION_DECL) register_function(item, "Global");
            else if (item->type == NODE_MAIN_CLASS && !main_node) main_node = item;
        }
    }
    if (!main_node) {
        rt_error(root, "No se encontró el método main");
        return 1;
    }

    push_scope(NULL, "main");
    exec_list_here(main_node->data.main_class.body);
    while (g_scope) pop_scope();    /* también desapila si hubo un error a mitad */
    fflush(g_out);
    return g_err ? 1 : 0;
}

int interpreter_symbol_count(void) { return g_nrep; }

// Escapa saltos de línea y tabulaciones para que el valor quepa en una sola fila
static void escape_cell(char *dst, size_t cap, const char *src) {
    size_t j = 0;
    for (size_t i = 0; src[i] && j + 3 < cap; i++) {
        if (src[i] == '\n') { dst[j++] = '\\'; dst[j++] = 'n'; }
        else if (src[i] == '\t') { dst[j++] = '\\'; dst[j++] = 't'; }
        else dst[j++] = src[i];
    }
    dst[j] = '\0';
}

void interpreter_write_symbol_table(FILE *f) {
    const char *line = "+------------------+--------------+--------------+--------------------+-------+---------+--------------------------+";
    fprintf(f, "============================================================================================================================\n");
    fprintf(f, "                                              REPORTE: TABLA DE SIMBOLOS\n");
    fprintf(f, "============================================================================================================================\n");
    fprintf(f, "%s\n", line);
    fprintf(f, "| "); fprint_cell(f, "ID", 16);
    fprintf(f, " | "); fprint_cell(f, "Tipo simbolo", 12);
    fprintf(f, " | "); fprint_cell(f, "Tipo dato", 12);
    fprintf(f, " | "); fprint_cell(f, "Ambito", 18);
    fprintf(f, " | Linea | Columna | "); fprint_cell(f, "Valor", 24);
    fprintf(f, " |\n%s\n", line);
    for (int i = 0; i < g_nrep; i++) {
        char scope[128], val[1024];
        if (!strcmp(g_rep[i].func, "Global") || g_rep[i].depth == 0)
            snprintf(scope, sizeof scope, "%s", g_rep[i].func);
        else
            snprintf(scope, sizeof scope, "%s [nivel %d]", g_rep[i].func, g_rep[i].depth);
        escape_cell(val, sizeof val, g_rep[i].value);
        fprintf(f, "| "); fprint_cell(f, g_rep[i].id, 16);
        fprintf(f, " | "); fprint_cell(f, g_rep[i].kind, 12);
        fprintf(f, " | "); fprint_cell(f, g_rep[i].type, 12);
        fprintf(f, " | "); fprint_cell(f, scope, 18);
        fprintf(f, " | %-5d | %-7d | ", g_rep[i].line, g_rep[i].column);
        fprint_cell(f, val, 24);
        fprintf(f, " |\n");
    }
    fprintf(f, "%s\n\nTotal de simbolos: %d\n", line, g_nrep);
}
