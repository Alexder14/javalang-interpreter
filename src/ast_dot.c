#include "ast_dot.h"
#include <stdlib.h>
#include <string.h>

/* ========================================================================
 * Exportación del AST a Graphviz (DOT)
 *
 * Cada nodo del AST es un vértice con una etiqueta legible y un color según
 * su categoría; las aristas llevan el rol del hijo (condición, cuerpo, ...).
 * ===================================================================== */

#define MAX_KIDS 24

typedef struct { ASTNode *node; const char *label; } Kid;

static int g_counter = 0;

/* Escapa una cadena para usarla dentro de una etiqueta DOT entre comillas */
static void dot_escape(const char *src, char *dst, size_t cap) {
    size_t j = 0;
    for (size_t i = 0; src[i] && j + 3 < cap; i++) {
        unsigned char c = (unsigned char)src[i];
        if (c == '"' || c == '\\') { dst[j++] = '\\'; dst[j++] = (char)c; }
        else if (c == '\n') { dst[j++] = '\\'; dst[j++] = 'n'; }
        else if (c == '\t') { dst[j++] = '\\'; dst[j++] = 't'; }
        else dst[j++] = (char)c;
    }
    dst[j] = '\0';
}

static const char *dims_str(int dims) {
    static const char *s[] = { "", "[]", "[][]", "[][][]", "[][][][]" };
    return dims >= 0 && dims <= 4 ? s[dims] : "[]...";
}

/* Etiqueta (sin escapar) y estilo de un nodo */
static void describe(ASTNode *n, char *label, size_t cap, const char **shape, const char **color) {
    *shape = "ellipse";
    *color = "#FFF4C2";          /* expresiones */
    switch (n->type) {
        case NODE_PROGRAM:
            snprintf(label, cap, "Programa"); *shape = "box"; *color = "#C9D6FF"; break;
        case NODE_MAIN_CLASS:
            snprintf(label, cap, "main()"); *shape = "box"; *color = "#C9D6FF"; break;
        case NODE_FUNCTION_DECL:
            snprintf(label, cap, "Funcion %s\n-> %s", n->data.func_decl.name, n->data.func_decl.return_type);
            *shape = "box"; *color = "#C9D6FF"; break;
        case NODE_PARAMETER:
            snprintf(label, cap, "Parametro\n%s%s %s", n->data.parameter.data_type,
                     dims_str(n->data.parameter.dims), n->data.parameter.name);
            *shape = "box"; *color = "#D5F5D5"; break;
        case NODE_VAR_DECL:
            snprintf(label, cap, "%s\n%s%s %s", n->data.var_decl.is_const ? "Constante" : "Declaracion",
                     n->data.var_decl.data_type, dims_str(n->data.var_decl.is_array ? n->data.var_decl.array_size : 0),
                     n->data.var_decl.name);
            *shape = "box"; *color = "#D5F5D5"; break;
        case NODE_ASSIGNMENT:
            snprintf(label, cap, "Asignacion\n%s", n->data.assignment.operator ? n->data.assignment.operator : "=");
            *shape = "box"; *color = "#FFD9B3"; break;
        case NODE_BLOCK:
        case NODE_LIST:
        case NODE_STATEMENT_LIST:
            snprintf(label, cap, "Lista (%d)", n->type == NODE_BLOCK ? n->data.block.count : n->data.list.count);
            *shape = "box"; *color = "#E8E8E8"; break;
        case NODE_EXPRESSION_STMT:
            snprintf(label, cap, "Expresion"); *shape = "box"; *color = "#E8E8E8"; break;
        case NODE_IF_STMT:      snprintf(label, cap, "if"); *shape = "diamond"; *color = "#F7C6C6"; break;
        case NODE_WHILE_STMT:   snprintf(label, cap, "while"); *shape = "diamond"; *color = "#F7C6C6"; break;
        case NODE_DO_WHILE_STMT:snprintf(label, cap, "do-while"); *shape = "diamond"; *color = "#F7C6C6"; break;
        case NODE_FOR_STMT:     snprintf(label, cap, "for"); *shape = "diamond"; *color = "#F7C6C6"; break;
        case NODE_FOREACH_STMT:
            snprintf(label, cap, "for-each\n%s%s %s", n->data.foreach_stmt.data_type,
                     dims_str(n->data.foreach_stmt.dims), n->data.foreach_stmt.name);
            *shape = "diamond"; *color = "#F7C6C6"; break;
        case NODE_SWITCH_STMT:  snprintf(label, cap, "switch"); *shape = "diamond"; *color = "#F7C6C6"; break;
        case NODE_CASE_STMT:
            snprintf(label, cap, n->data.case_stmt.value ? "case" : "default"); *shape = "box"; *color = "#F7C6C6"; break;
        case NODE_BREAK_STMT:   snprintf(label, cap, "break"); *shape = "box"; *color = "#F7C6C6"; break;
        case NODE_CONTINUE_STMT:snprintf(label, cap, "continue"); *shape = "box"; *color = "#F7C6C6"; break;
        case NODE_RETURN_STMT:  snprintf(label, cap, "return"); *shape = "box"; *color = "#F7C6C6"; break;
        case NODE_BINARY_OP:
            snprintf(label, cap, "Binaria\n%s", n->data.binary_op.operator); break;
        case NODE_UNARY_OP:
            snprintf(label, cap, "Unaria\n%s%s", n->data.unary_op.operator,
                     (n->data.unary_op.operator[0] == '+' || n->data.unary_op.operator[0] == '-') &&
                     n->data.unary_op.operator[1] && !n->data.unary_op.is_prefix ? " (post)" : "");
            break;
        case NODE_FUNCTION_CALL:
            snprintf(label, cap, "Llamada\n%s", n->data.func_call.name); *color = "#FFE0F0"; break;
        case NODE_METHOD_CALL:
            snprintf(label, cap, "Metodo\n.%s()", n->data.method_call.name); *color = "#FFE0F0"; break;
        case NODE_MEMBER_ACCESS:
            snprintf(label, cap, "Miembro\n.%s", n->data.member_access.member); *color = "#FFE0F0"; break;
        case NODE_ARRAY_ACCESS:
            snprintf(label, cap, "Acceso a arreglo\n[ ]"); *color = "#FFE0F0"; break;
        case NODE_ARRAY_INIT:
            if (n->data.array_init.size) snprintf(label, cap, "Nuevo arreglo\nnew %s", n->data.array_init.type);
            else snprintf(label, cap, "Arreglo literal\n{ ... }");
            *color = "#FFE0F0"; break;
        case NODE_INT_LITERAL:
            snprintf(label, cap, "int\n%d", n->data.int_literal.value); *shape = "plaintext"; *color = "#D5F5D5"; break;
        case NODE_FLOAT_LITERAL:
            snprintf(label, cap, "float\n%g", (double)n->data.float_literal.value); *shape = "plaintext"; *color = "#D5F5D5"; break;
        case NODE_STRING_LITERAL:
            snprintf(label, cap, "String\n\"%s\"", n->data.string_literal.value); *shape = "plaintext"; *color = "#D5F5D5"; break;
        case NODE_CHAR_LITERAL:
            snprintf(label, cap, "char\n'%c'", n->data.char_literal.value); *shape = "plaintext"; *color = "#D5F5D5"; break;
        case NODE_BOOLEAN_LITERAL:
            snprintf(label, cap, "boolean\n%s", n->data.boolean_literal.value ? "true" : "false"); *shape = "plaintext"; *color = "#D5F5D5"; break;
        case NODE_NULL_LITERAL:
            snprintf(label, cap, "null"); *shape = "plaintext"; *color = "#D5F5D5"; break;
        case NODE_IDENTIFIER:
            snprintf(label, cap, "id\n%s", n->data.identifier.name); *shape = "plaintext"; *color = "#E6F0FF"; break;
        default:
            snprintf(label, cap, "Nodo %d", n->type); break;
    }
}

static int kids_of(ASTNode *n, Kid *k) {
    int c = 0;
#define ADD(nd, lb) do { if ((nd) && c < MAX_KIDS) { k[c].node = (nd); k[c].label = (lb); c++; } } while (0)
    switch (n->type) {
        case NODE_PROGRAM:      ADD(n->data.program.body, ""); break;
        case NODE_MAIN_CLASS:   ADD(n->data.main_class.body, "cuerpo"); break;
        case NODE_FUNCTION_DECL:
            ADD(n->data.func_decl.parameters, "parametros");
            ADD(n->data.func_decl.body, "cuerpo");
            break;
        case NODE_VAR_DECL:     ADD(n->data.var_decl.init_value, "valor"); break;
        case NODE_ASSIGNMENT:
            ADD(n->data.assignment.left, "destino");
            ADD(n->data.assignment.right, "valor");
            break;
        case NODE_BINARY_OP:
            ADD(n->data.binary_op.left, "izq");
            ADD(n->data.binary_op.right, "der");
            break;
        case NODE_UNARY_OP:     ADD(n->data.unary_op.operand, ""); break;
        case NODE_FUNCTION_CALL:ADD(n->data.func_call.arguments, "args"); break;
        case NODE_METHOD_CALL:
            ADD(n->data.method_call.object, "objeto");
            ADD(n->data.method_call.arguments, "args");
            break;
        case NODE_MEMBER_ACCESS:ADD(n->data.member_access.object, "objeto"); break;
        case NODE_ARRAY_ACCESS:
            ADD(n->data.array_access.array, "arreglo");
            ADD(n->data.array_access.index, "indice");
            break;
        case NODE_ARRAY_INIT:
            ADD(n->data.array_init.size, "tamanos");
            ADD(n->data.array_init.values, "valores");
            break;
        case NODE_EXPRESSION_STMT: ADD(n->data.program.body, ""); break;
        case NODE_IF_STMT:
            ADD(n->data.if_stmt.condition, "condicion");
            ADD(n->data.if_stmt.then_stmt, "entonces");
            ADD(n->data.if_stmt.else_stmt, "sino");
            break;
        case NODE_WHILE_STMT:
        case NODE_DO_WHILE_STMT:
            ADD(n->data.while_stmt.condition, "condicion");
            ADD(n->data.while_stmt.body, "cuerpo");
            break;
        case NODE_FOR_STMT:
            ADD(n->data.for_stmt.init, "inicio");
            ADD(n->data.for_stmt.condition, "condicion");
            ADD(n->data.for_stmt.update, "paso");
            ADD(n->data.for_stmt.body, "cuerpo");
            break;
        case NODE_FOREACH_STMT:
            ADD(n->data.foreach_stmt.iterable, "arreglo");
            ADD(n->data.foreach_stmt.body, "cuerpo");
            break;
        case NODE_SWITCH_STMT:
            ADD(n->data.switch_stmt.expression, "valor");
            ADD(n->data.switch_stmt.cases, "casos");
            break;
        case NODE_CASE_STMT:
            ADD(n->data.case_stmt.value, "valor");
            ADD(n->data.case_stmt.statements, "sentencias");
            break;
        case NODE_RETURN_STMT:  ADD(n->data.return_stmt.value, ""); break;
        case NODE_BLOCK:
            for (int i = 0; i < n->data.block.count; i++) ADD(n->data.block.statements[i], "");
            break;
        case NODE_LIST:
        case NODE_STATEMENT_LIST:
            for (int i = 0; i < n->data.list.count; i++) ADD(n->data.list.items[i], "");
            break;
        default: break;
    }
#undef ADD
    return c;
}

/* Emite el nodo y su subárbol; devuelve el id del nodo */
static int emit(ASTNode *n, FILE *f) {
    int id = g_counter++;
    char raw[512], esc[1100];
    const char *shape, *color;
    describe(n, raw, sizeof raw, &shape, &color);
    dot_escape(raw, esc, sizeof esc);
    fprintf(f, "  n%d [label=\"%s\", shape=%s, fillcolor=\"%s\"];\n", id, esc, shape, color);

    Kid kids[MAX_KIDS];
    int nk = kids_of(n, kids);
    for (int i = 0; i < nk; i++) {
        int cid = emit(kids[i].node, f);
        if (kids[i].label[0]) fprintf(f, "  n%d -> n%d [label=\"%s\"];\n", id, cid, kids[i].label);
        else fprintf(f, "  n%d -> n%d;\n", id, cid);
    }
    return id;
}

void ast_write_dot(ASTNode *root, FILE *f) {
    g_counter = 0;
    fprintf(f, "digraph AST {\n");
    fprintf(f, "  graph [rankdir=TB, fontname=\"Helvetica\", labelloc=t, label=\"Arbol de Sintaxis Abstracta (AST) - JavaLang\", nodesep=0.3, ranksep=0.5];\n");
    fprintf(f, "  node [fontname=\"Helvetica\", fontsize=10, style=filled];\n");
    fprintf(f, "  edge [fontname=\"Helvetica\", fontsize=8, color=\"#555555\"];\n");
    if (root) emit(root, f);
    else fprintf(f, "  vacio [label=\"(sin AST)\", shape=plaintext];\n");
    fprintf(f, "}\n");
}
