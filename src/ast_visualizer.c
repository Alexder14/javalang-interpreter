#include "ast_visualizer.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int node_counter = 0;

// Función para escapar caracteres especiales en strings
char* escape_string(const char* str) {
    if (!str) return strdup("");
    
    int len = strlen(str);
    char* escaped = malloc(len * 2 + 1); // Espacio extra para escapes
    int j = 0;
    
    for (int i = 0; i < len; i++) {
        switch (str[i]) {
            case '"':
                escaped[j++] = '\\';
                escaped[j++] = '"';
                break;
            case '\\':
                escaped[j++] = '\\';
                escaped[j++] = '\\';
                break;
            case '\n':
                escaped[j++] = '\\';
                escaped[j++] = 'n';
                break;
            case '\t':
                escaped[j++] = '\\';
                escaped[j++] = 't';
                break;
            default:
                escaped[j++] = str[i];
                break;
        }
    }
    escaped[j] = '\0';
    
    return escaped;
}

// Función para obtener color según tipo de nodo
const char* get_node_color(NodeType type) {
    switch (type) {
        case NODE_PROGRAM:
        case NODE_MAIN_CLASS:
            return "lightblue";
        case NODE_VAR_DECL:
        case NODE_FUNC_DECL:
            return "lightgreen";
        case NODE_IF_STMT:
        case NODE_WHILE_STMT:
        case NODE_FOR_STMT:
            return "lightyellow";
        case NODE_BINARY_OP:
        case NODE_UNARY_OP:
            return "lightcoral";
        case NODE_INT_LITERAL:
        case NODE_FLOAT_LITERAL:
        case NODE_STRING_LITERAL:
        case NODE_CHAR_LITERAL:
        case NODE_BOOLEAN_LITERAL:
            return "lightgray";
        case NODE_IDENTIFIER:
            return "wheat";
        case NODE_FUNCTION_CALL:
            return "plum";
        default:
            return "white";
    }
}

// Función para obtener forma según tipo de nodo
const char* get_node_shape(NodeType type) {
    switch (type) {
        case NODE_PROGRAM:
        case NODE_MAIN_CLASS:
            return "box";
        case NODE_IF_STMT:
        case NODE_WHILE_STMT:
        case NODE_FOR_STMT:
            return "diamond";
        case NODE_FUNCTION_CALL:
            return "ellipse";
        case NODE_INT_LITERAL:
        case NODE_FLOAT_LITERAL:
        case NODE_STRING_LITERAL:
        case NODE_CHAR_LITERAL:
        case NODE_BOOLEAN_LITERAL:
            return "box";
        default:
            return "ellipse";
    }
}

// Función para obtener nombre del tipo de nodo
const char* get_node_type_name(NodeType type) {
    switch (type) {
        case NODE_PROGRAM: return "PROGRAM";
        case NODE_MAIN_CLASS: return "MAIN_CLASS";
        case NODE_VAR_DECL: return "VAR_DECL";
        case NODE_FUNC_DECL: return "FUNC_DECL";
        case NODE_PARAMETER: return "PARAMETER";
        case NODE_ASSIGNMENT: return "ASSIGNMENT";
        case NODE_IF_STMT: return "IF_STMT";
        case NODE_WHILE_STMT: return "WHILE_STMT";
        case NODE_FOR_STMT: return "FOR_STMT";
        case NODE_BINARY_OP: return "BINARY_OP";
        case NODE_UNARY_OP: return "UNARY_OP";
        case NODE_FUNCTION_CALL: return "FUNC_CALL";
        case NODE_ARRAY_ACCESS: return "ARRAY_ACCESS";
        case NODE_INT_LITERAL: return "INT_LITERAL";
        case NODE_FLOAT_LITERAL: return "FLOAT_LITERAL";
        case NODE_STRING_LITERAL: return "STRING_LITERAL";
        case NODE_CHAR_LITERAL: return "CHAR_LITERAL";
        case NODE_BOOLEAN_LITERAL: return "BOOL_LITERAL";
        case NODE_NULL_LITERAL: return "NULL_LITERAL";
        case NODE_IDENTIFIER: return "IDENTIFIER";
        case NODE_LIST: return "LIST";
        case NODE_BLOCK: return "BLOCK";
        case NODE_RETURN_STMT: return "RETURN";
        case NODE_BREAK_STMT: return "BREAK";
        case NODE_CONTINUE_STMT: return "CONTINUE";
        default: return "UNKNOWN";
    }
}

// Función recursiva para generar nodos de Graphviz
void generate_graphviz_node(FILE* file, ASTNode* node, int* node_id) {
    if (!node || !file) return;
    
    int current_id = (*node_id)++;
    
    // Generar etiqueta del nodo
    char label[512];
    char* escaped_label = NULL;
    
    switch (node->type) {
        case NODE_VAR_DECL:
            snprintf(label, sizeof(label), "%s\\n%s %s%s", 
                get_node_type_name(node->type),
                node->data.var_decl.data_type ? node->data.var_decl.data_type : "?",
                node->data.var_decl.name ? node->data.var_decl.name : "?",
                node->data.var_decl.is_array ? "[]" : "");
            break;
            
        case NODE_FUNC_DECL:
            snprintf(label, sizeof(label), "%s\\n%s %s()", 
                get_node_type_name(node->type),
                node->data.func_decl.return_type ? node->data.func_decl.return_type : "?",
                node->data.func_decl.name ? node->data.func_decl.name : "?");
            break;
            
        case NODE_BINARY_OP:
            snprintf(label, sizeof(label), "%s\\n%s", 
                get_node_type_name(node->type),
                node->data.binary_op.operator ? node->data.binary_op.operator : "?");
            break;
            
        case NODE_UNARY_OP:
            snprintf(label, sizeof(label), "%s\\n%s (%s)", 
                get_node_type_name(node->type),
                node->data.unary_op.operator ? node->data.unary_op.operator : "?",
                node->data.unary_op.is_prefix ? "prefix" : "postfix");
            break;
            
        case NODE_ASSIGNMENT:
            snprintf(label, sizeof(label), "%s\\n%s", 
                get_node_type_name(node->type),
                node->data.assignment.operator ? node->data.assignment.operator : "?");
            break;
            
        case NODE_FUNCTION_CALL:
            snprintf(label, sizeof(label), "%s\\n%s", 
                get_node_type_name(node->type),
                node->data.func_call.name ? node->data.func_call.name : "?");
            break;
            
        case NODE_INT_LITERAL:
            snprintf(label, sizeof(label), "%s\\n%d", 
                get_node_type_name(node->type),
                node->data.int_literal.value);
            break;
            
        case NODE_FLOAT_LITERAL:
            snprintf(label, sizeof(label), "%s\\n%.2f", 
                get_node_type_name(node->type),
                node->data.float_literal.value);
            break;
            
        case NODE_STRING_LITERAL:
            if (node->data.string_literal.value) {
                escaped_label = escape_string(node->data.string_literal.value);
                snprintf(label, sizeof(label), "%s\\n\\\"%s\\\"", 
                    get_node_type_name(node->type), escaped_label);
                free(escaped_label);
            } else {
                snprintf(label, sizeof(label), "%s\\n\\\"\\\"", get_node_type_name(node->type));
            }
            break;
            
        case NODE_CHAR_LITERAL:
            snprintf(label, sizeof(label), "%s\\n'%c'", 
                get_node_type_name(node->type),
                node->data.char_literal.value);
            break;
            
        case NODE_BOOLEAN_LITERAL:
            snprintf(label, sizeof(label), "%s\\n%s", 
                get_node_type_name(node->type),
                node->data.boolean_literal.value ? "true" : "false");
            break;
            
        case NODE_IDENTIFIER:
            snprintf(label, sizeof(label), "%s\\n%s", 
                get_node_type_name(node->type),
                node->data.identifier.name ? node->data.identifier.name : "?");
            break;
            
        case NODE_LIST:
            snprintf(label, sizeof(label), "%s\\n(%d items)", 
                get_node_type_name(node->type),
                node->data.list.count);
            break;
            
        case NODE_BLOCK:
            snprintf(label, sizeof(label), "%s\\n(%d stmts)", 
                get_node_type_name(node->type),
                node->data.block.count);
            break;
            
        default:
            snprintf(label, sizeof(label), "%s", get_node_type_name(node->type));
            break;
    }
    
    // Escribir definición del nodo
    fprintf(file, "    node%d [label=\"%s\", shape=%s, style=filled, fillcolor=%s];\n",
            current_id, label, get_node_shape(node->type), get_node_color(node->type));
    
    // Generar nodos hijos y conexiones
    switch (node->type) {
        case NODE_PROGRAM:
            if (node->data.program.body) {
                generate_graphviz_node(file, node->data.program.body, node_id);
                fprintf(file, "    node%d -> node%d [label=\"body\"];\n", current_id, *node_id - 1);
            }
            break;
            
        case NODE_MAIN_CLASS:
            if (node->data.main_class.body) {
                generate_graphviz_node(file, node->data.main_class.body, node_id);
                fprintf(file, "    node%d -> node%d [label=\"body\"];\n", current_id, *node_id - 1);
            }
            break;
            
        case NODE_VAR_DECL:
            if (node->data.var_decl.init_value) {
                generate_graphviz_node(file, node->data.var_decl.init_value, node_id);
                fprintf(file, "    node%d -> node%d [label=\"init\"];\n", current_id, *node_id - 1);
            }
            break;
            
        case NODE_FUNC_DECL:
            if (node->data.func_decl.parameters) {
                generate_graphviz_node(file, node->data.func_decl.parameters, node_id);
                fprintf(file, "    node%d -> node%d [label=\"params\"];\n", current_id, *node_id - 1);
            }
            if (node->data.func_decl.body) {
                generate_graphviz_node(file, node->data.func_decl.body, node_id);
                fprintf(file, "    node%d -> node%d [label=\"body\"];\n", current_id, *node_id - 1);
            }
            break;
            
        case NODE_BINARY_OP:
            if (node->data.binary_op.left) {
                generate_graphviz_node(file, node->data.binary_op.left, node_id);
                fprintf(file, "    node%d -> node%d [label=\"left\"];\n", current_id, *node_id - 1);
            }
            if (node->data.binary_op.right) {
                generate_graphviz_node(file, node->data.binary_op.right, node_id);
                fprintf(file, "    node%d -> node%d [label=\"right\"];\n", current_id, *node_id - 1);
            }
            break;
            
        case NODE_UNARY_OP:
            if (node->data.unary_op.operand) {
                generate_graphviz_node(file, node->data.unary_op.operand, node_id);
                fprintf(file, "    node%d -> node%d [label=\"operand\"];\n", current_id, *node_id - 1);
            }
            break;
            
        case NODE_ASSIGNMENT:
            if (node->data.assignment.left) {
                generate_graphviz_node(file, node->data.assignment.left, node_id);
                fprintf(file, "    node%d -> node%d [label=\"left\"];\n", current_id, *node_id - 1);
            }
            if (node->data.assignment.right) {
                generate_graphviz_node(file, node->data.assignment.right, node_id);
                fprintf(file, "    node%d -> node%d [label=\"right\"];\n", current_id, *node_id - 1);
            }
            break;
            
        case NODE_IF_STMT:
            if (node->data.if_stmt.condition) {
                generate_graphviz_node(file, node->data.if_stmt.condition, node_id);
                fprintf(file, "    node%d -> node%d [label=\"condition\"];\n", current_id, *node_id - 1);
            }
            if (node->data.if_stmt.then_stmt) {
                generate_graphviz_node(file, node->data.if_stmt.then_stmt, node_id);
                fprintf(file, "    node%d -> node%d [label=\"then\"];\n", current_id, *node_id - 1);
            }
            if (node->data.if_stmt.else_stmt) {
                generate_graphviz_node(file, node->data.if_stmt.else_stmt, node_id);
                fprintf(file, "    node%d -> node%d [label=\"else\"];\n", current_id, *node_id - 1);
            }
            break;
            
        case NODE_WHILE_STMT:
            if (node->data.while_stmt.condition) {
                generate_graphviz_node(file, node->data.while_stmt.condition, node_id);
                fprintf(file, "    node%d -> node%d [label=\"condition\"];\n", current_id, *node_id - 1);
            }
            if (node->data.while_stmt.body) {
                generate_graphviz_node(file, node->data.while_stmt.body, node_id);
                fprintf(file, "    node%d -> node%d [label=\"body\"];\n", current_id, *node_id - 1);
            }
            break;
            
        case NODE_FOR_STMT:
            if (node->data.for_stmt.init) {
                generate_graphviz_node(file, node->data.for_stmt.init, node_id);
                fprintf(file, "    node%d -> node%d [label=\"init\"];\n", current_id, *node_id - 1);
            }
            if (node->data.for_stmt.condition) {
                generate_graphviz_node(file, node->data.for_stmt.condition, node_id);
                fprintf(file, "    node%d -> node%d [label=\"condition\"];\n", current_id, *node_id - 1);
            }
            if (node->data.for_stmt.update) {
                generate_graphviz_node(file, node->data.for_stmt.update, node_id);
                fprintf(file, "    node%d -> node%d [label=\"update\"];\n", current_id, *node_id - 1);
            }
            if (node->data.for_stmt.body) {
                generate_graphviz_node(file, node->data.for_stmt.body, node_id);
                fprintf(file, "    node%d -> node%d [label=\"body\"];\n", current_id, *node_id - 1);
            }
            break;
            
        case NODE_FUNCTION_CALL:
            if (node->data.func_call.arguments) {
                generate_graphviz_node(file, node->data.func_call.arguments, node_id);
                fprintf(file, "    node%d -> node%d [label=\"args\"];\n", current_id, *node_id - 1);
            }
            break;
            
        case NODE_ARRAY_ACCESS:
            if (node->data.array_access.array) {
                generate_graphviz_node(file, node->data.array_access.array, node_id);
                fprintf(file, "    node%d -> node%d [label=\"array\"];\n", current_id, *node_id - 1);
            }
            if (node->data.array_access.index) {
                generate_graphviz_node(file, node->data.array_access.index, node_id);
                fprintf(file, "    node%d -> node%d [label=\"index\"];\n", current_id, *node_id - 1);
            }
            break;
            
        case NODE_LIST:
            for (int i = 0; i < node->data.list.count; i++) {
                if (node->data.list.items[i]) {
                    generate_graphviz_node(file, node->data.list.items[i], node_id);
                    fprintf(file, "    node%d -> node%d [label=\"[%d]\"];\n", current_id, *node_id - 1, i);
                }
            }
            break;
            
        case NODE_BLOCK:
            for (int i = 0; i < node->data.block.count; i++) {
                if (node->data.block.statements[i]) {
                    generate_graphviz_node(file, node->data.block.statements[i], node_id);
                    fprintf(file, "    node%d -> node%d [label=\"stmt%d\"];\n", current_id, *node_id - 1, i);
                }
            }
            break;
            
        case NODE_RETURN_STMT:
            if (node->data.return_stmt.value) {
                generate_graphviz_node(file, node->data.return_stmt.value, node_id);
                fprintf(file, "    node%d -> node%d [label=\"value\"];\n", current_id, *node_id - 1);
            }
            break;
            
        default:
            // Nodos sin hijos específicos
            break;
    }
}

// Función principal para generar archivo Graphviz
bool generate_ast_graphviz(ASTNode* root, const char* output_file) {
    if (!root || !output_file) return false;
    
    FILE* file = fopen(output_file, "w");
    if (!file) {
        fprintf(stderr, "Error: No se pudo crear el archivo %s\n", output_file);
        return false;
    }
    
    // Escribir cabecera del archivo DOT
    fprintf(file, "digraph AST {\n");
    fprintf(file, "    rankdir=TB;\n");
    fprintf(file, "    node [fontname=\"Arial\", fontsize=10];\n");
    fprintf(file, "    edge [fontname=\"Arial\", fontsize=8];\n");
    fprintf(file, "    \n");
    fprintf(file, "    // Configuración del grafo\n");
    fprintf(file, "    graph [bgcolor=white, pad=0.5];\n");
    fprintf(file, "    \n");
    fprintf(file, "    // Nodos del AST\n");
    
    // Generar todos los nodos
    int node_id = 0;
    generate_graphviz_node(file, root, &node_id);
    
    // Escribir cierre del archivo DOT
    fprintf(file, "}\n");
    
    fclose(file);
    return true;
}

// Función para generar imagen PNG desde archivo DOT
bool generate_ast_png(const char* dot_file, const char* png_file) {
    if (!dot_file || !png_file) return false;
    
    char command[512];
    snprintf(command, sizeof(command), "dot -Tpng %s -o %s", dot_file, png_file);
    
    int result = system(command);
    if (result != 0) {
        fprintf(stderr, "Warning: No se pudo generar PNG. ¿Está Graphviz instalado?\n");
        fprintf(stderr, "         Instale con: sudo apt install graphviz\n");
        return false;
    }
    
    return true;
}

// Función completa para generar visualización del AST
void visualize_ast(ASTNode* root, const char* base_name) {
    if (!root || !base_name) return;
    
    printf("🎨 Generando visualización del AST...\n");
    
    char dot_file[256];
    char png_file[256];
    
    snprintf(dot_file, sizeof(dot_file), "%s.dot", base_name);
    snprintf(png_file, sizeof(png_file), "%s.png", base_name);
    
    // Generar archivo DOT
    if (generate_ast_graphviz(root, dot_file)) {
        printf("✅ Archivo DOT generado: %s\n", dot_file);
        
        // Intentar generar PNG
        if (generate_ast_png(dot_file, png_file)) {
            printf("✅ Imagen PNG generada: %s\n", png_file);
        } else {
            printf("⚠️  Archivo DOT creado, pero no se pudo generar PNG\n");
            printf("   Instale Graphviz: sudo apt install graphviz\n");
            printf("   Luego ejecute: dot -Tpng %s -o %s\n", dot_file, png_file);
        }
    } else {
        printf("❌ Error al generar archivo DOT\n");
    }
}