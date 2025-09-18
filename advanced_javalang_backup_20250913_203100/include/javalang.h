#ifndef JAVALANG_H
#define JAVALANG_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// Variables globales
extern int line_num;
extern int col_num;
extern int total_lines;
extern int total_tokens;

// Tipos de nodos AST completos
typedef enum {
    NODE_PROGRAM, NODE_CLASS, NODE_MAIN_METHOD, NODE_METHOD,
    NODE_VAR_DECL, NODE_ASSIGNMENT, NODE_IF, NODE_ELSE, NODE_WHILE,
    NODE_FOR, NODE_SWITCH, NODE_CASE, NODE_DEFAULT, NODE_BREAK,
    NODE_CONTINUE, NODE_RETURN, NODE_BLOCK, NODE_EXPRESSION,
    NODE_BINARY_OP, NODE_UNARY_OP, NODE_FUNCTION_CALL,
    NODE_ARRAY_ACCESS, NODE_ARRAY_DECL, NODE_IDENTIFIER,
    NODE_INT_LITERAL, NODE_FLOAT_LITERAL, NODE_STRING_LITERAL,
    NODE_BOOLEAN_LITERAL, NODE_NULL_LITERAL
} NodeType;

// AST Node
typedef struct ASTNode {
    NodeType type;
    char *value;
    int int_val;
    double float_val;
    bool bool_val;
    struct ASTNode *left;
    struct ASTNode *right;
    struct ASTNode *next;
    struct ASTNode **children;
    int child_count;
    int line, col;
} ASTNode;

extern ASTNode *ast_root;

// Análisis semántico avanzado
typedef enum {
    TYPE_INT, TYPE_FLOAT, TYPE_DOUBLE, TYPE_STRING, 
    TYPE_BOOLEAN, TYPE_VOID, TYPE_ARRAY, TYPE_UNKNOWN
} DataType;

typedef struct Symbol {
    char *name;
    DataType type;
    bool is_array;
    bool is_initialized;
    int scope_level;
    int line_declared;
    struct Symbol *next;
} Symbol;

typedef struct Scope {
    int level;
    Symbol *symbols;
    struct Scope *parent;
} Scope;

extern Scope *current_scope;
extern int total_symbols;
extern int semantic_errors;

// Funciones AST
ASTNode* create_node(NodeType type, const char *value, int line, int col);
void add_child(ASTNode *parent, ASTNode *child);
void print_ast(ASTNode *node, int depth);
int count_ast_nodes(ASTNode *node);

// Análisis semántico
void enter_scope();
void exit_scope();
void add_symbol(const char *name, DataType type, bool is_array);
Symbol* find_symbol(const char *name);
void check_variable_usage(const char *name, int line);
void validate_assignment(const char *var, DataType expr_type);
void print_symbol_table();
void print_semantic_analysis();

// Funciones built-in simuladas
void process_println(ASTNode *args);
void process_parseInt(ASTNode *args);
void process_parseFloat(ASTNode *args);
void process_valueOf(ASTNode *args);
void process_join(ASTNode *args);
void process_indexOf(ASTNode *args);

#endif
