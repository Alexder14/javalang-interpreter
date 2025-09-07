#ifndef AST_VISUALIZER_H
#define AST_VISUALIZER_H

#include "ast.h"
#include <stdbool.h>

// Funciones principales para visualización
bool generate_ast_graphviz(ASTNode* root, const char* output_file);
bool generate_ast_png(const char* dot_file, const char* png_file);
void visualize_ast(ASTNode* root, const char* base_name);

// Funciones auxiliares
char* escape_string(const char* str);
const char* get_node_color(NodeType type);
const char* get_node_shape(NodeType type);
const char* get_node_type_name(NodeType type);

// Función recursiva interna
void generate_graphviz_node(FILE* file, ASTNode* node, int* node_id);

#endif