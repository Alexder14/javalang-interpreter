#ifndef AST_H
#define AST_H

#include "common.h"
#include <stdbool.h>

// Tipos de nodos del AST
typedef enum {
    NODE_PROGRAM,
    NODE_MAIN_CLASS,
    NODE_VAR_DECL,
    NODE_CONST_DECL,
    NODE_FUNCTION_DECL,
    NODE_PARAMETER,
    NODE_BLOCK,
    NODE_EXPRESSION_STMT,
    NODE_IF_STMT,
    NODE_WHILE_STMT,
    NODE_FOR_STMT,
    NODE_DO_WHILE_STMT,
    NODE_SWITCH_STMT,
    NODE_CASE_STMT,
    NODE_BREAK_STMT,
    NODE_CONTINUE_STMT,
    NODE_RETURN_STMT,
    NODE_ASSIGNMENT,
    NODE_BINARY_OP,
    NODE_UNARY_OP,
    NODE_FUNCTION_CALL,
    NODE_ARRAY_ACCESS,
    NODE_ARRAY_INIT,
    NODE_INT_LITERAL,
    NODE_FLOAT_LITERAL,
    NODE_STRING_LITERAL,
    NODE_CHAR_LITERAL,
    NODE_BOOLEAN_LITERAL,
    NODE_NULL_LITERAL,
    NODE_IDENTIFIER,
    NODE_TYPE,
    NODE_STATEMENT_LIST,
    NODE_EXPRESSION_LIST,
    NODE_PARAMETER_LIST
} NodeType;

// Forward declaration
struct ASTNode;

typedef struct ASTNode {
    NodeType type;
    int line;
    int column;
    
    union {
        struct { struct ASTNode *body; } program;
        struct { struct ASTNode *body; } main_class;
        struct {
            char *data_type;
            char *name;
            struct ASTNode *init_value;
            bool is_array;
            int array_size;
        } var_decl;
        struct {
            char *return_type;
            char *name;
            struct ASTNode *parameters;
            struct ASTNode *body;
        } func_decl;
        struct {
            char *data_type;
            char *name;
            bool is_array;
        } parameter;
        struct {
            struct ASTNode **statements;
            int count;
            int capacity;
        } block;
        struct {
            struct ASTNode *condition;
            struct ASTNode *then_stmt;
            struct ASTNode *else_stmt;
        } if_stmt;
        struct {
            struct ASTNode *condition;
            struct ASTNode *body;
        } while_stmt;
        struct {
            struct ASTNode *init;
            struct ASTNode *condition;
            struct ASTNode *update;
            struct ASTNode *body;
        } for_stmt;
        struct {
            struct ASTNode *expression;
            struct ASTNode *cases;
        } switch_stmt;
        struct {
            struct ASTNode *value;
            struct ASTNode *statements;
        } case_stmt;
        struct {
            struct ASTNode *value;
        } return_stmt;
        struct {
            struct ASTNode *left;
            char *operator;
            struct ASTNode *right;
        } assignment;
        struct {
            char *operator;
            struct ASTNode *left;
            struct ASTNode *right;
        } binary_op;
        struct {
            char *operator;
            struct ASTNode *operand;
            bool is_prefix;
        } unary_op;
        struct {
            char *name;
            struct ASTNode *arguments;
        } func_call;
        struct {
            struct ASTNode *array;
            struct ASTNode *index;
        } array_access;
        struct {
            char *type;
            struct ASTNode *size;
            struct ASTNode *values;
        } array_init;
        struct { int value; } int_literal;
        struct { float value; } float_literal;
        struct { char *value; } string_literal;
        struct { char value; } char_literal;
        struct { bool value; } boolean_literal;
        struct { char *name; } identifier;
        struct {
            char *name;
            bool is_array;
            int array_dimensions;
        } type;
        struct {
            struct ASTNode **items;
            int count;
            int capacity;
        } list;
    } data;
    
    struct ASTNode *next;
} ASTNode;

// SOLO DECLARACIONES EXTERN (no definiciones)
extern ASTNode *ast_root;
extern bool has_syntax_errors;

// Prototipos de funciones
ASTNode* create_node(NodeType type, int line, int col);
ASTNode* create_program_node(ASTNode *body);
ASTNode* create_main_class_node(ASTNode *body);
ASTNode* create_var_decl_node(const char *type, const char *name, ASTNode *init, bool is_array, int array_size);
ASTNode* create_function_decl_node(const char *return_type, const char *name, ASTNode *params, ASTNode *body);
ASTNode* create_parameter_node(const char *type, const char *name, bool is_array);
ASTNode* create_block_node(void);
ASTNode* create_if_node(ASTNode *condition, ASTNode *then_stmt, ASTNode *else_stmt);
ASTNode* create_while_node(ASTNode *condition, ASTNode *body);
ASTNode* create_for_node(ASTNode *init, ASTNode *condition, ASTNode *update, ASTNode *body);
ASTNode* create_assignment_node(ASTNode *left, const char *op, ASTNode *right);
ASTNode* create_binary_op_node(const char *op, ASTNode *left, ASTNode *right);
ASTNode* create_unary_op_node(const char *op, ASTNode *operand, bool is_prefix);
ASTNode* create_function_call_node(const char *name, ASTNode *args);
ASTNode* create_array_access_node(ASTNode *array, ASTNode *index);
ASTNode* create_int_literal_node(int value);
ASTNode* create_float_literal_node(float value);
ASTNode* create_string_literal_node(const char *value);
ASTNode* create_char_literal_node(char value);
ASTNode* create_boolean_literal_node(bool value);
ASTNode* create_null_literal_node(void);
ASTNode* create_identifier_node(const char *name);
ASTNode* create_list_node(void);

void add_to_list(ASTNode *list, ASTNode *item);
ASTNode* get_from_list(ASTNode *list, int index);
int get_list_size(ASTNode *list);
void print_ast(ASTNode *node, int depth);
void free_ast(ASTNode *node);

#endif // AST_H
