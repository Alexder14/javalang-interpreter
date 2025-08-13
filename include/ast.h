#ifndef AST_H
#define AST_H

#include "common.h"

// Tipos de nodos del AST
typedef enum {
    // Programa principal
    NODE_PROGRAM,
    NODE_MAIN_CLASS,
    
    // Declaraciones
    NODE_VAR_DECL,
    NODE_CONST_DECL,
    NODE_FUNCTION_DECL,
    NODE_PARAMETER,
    
    // Sentencias
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
    
    // Expresiones
    NODE_ASSIGNMENT,
    NODE_BINARY_OP,
    NODE_UNARY_OP,
    NODE_FUNCTION_CALL,
    NODE_ARRAY_ACCESS,
    NODE_ARRAY_INIT,
    
    // Literales
    NODE_INT_LITERAL,
    NODE_FLOAT_LITERAL,
    NODE_STRING_LITERAL,
    NODE_CHAR_LITERAL,
    NODE_BOOLEAN_LITERAL,
    NODE_NULL_LITERAL,
    
    // Identificadores y tipos
    NODE_IDENTIFIER,
    NODE_TYPE,
    
    // Lista de nodos
    NODE_STATEMENT_LIST,
    NODE_EXPRESSION_LIST,
    NODE_PARAMETER_LIST
} NodeType;

// Estructura principal del nodo AST
typedef struct ASTNode {
    NodeType type;
    int line;
    int column;
    
    union {
        // Programa principal
        struct {
            struct ASTNode *body;
        } program;
        
        // Clase main
        struct {
            struct ASTNode *body;
        } main_class;
        
        // Declaración de variable
        struct {
            char *data_type;
            char *name;
            struct ASTNode *init_value;
            bool is_array;
            int array_size;
        } var_decl;
        
        // Declaración de función
        struct {
            char *return_type;
            char *name;
            struct ASTNode *parameters;
            struct ASTNode *body;
        } func_decl;
        
        // Parámetro de función
        struct {
            char *data_type;
            char *name;
            bool is_array;
        } parameter;
        
        // Bloque de sentencias
        struct {
            struct ASTNode **statements;
            int count;
            int capacity;
        } block;
        
        // Sentencia if
        struct {
            struct ASTNode *condition;
            struct ASTNode *then_stmt;
            struct ASTNode *else_stmt;
        } if_stmt;
        
        // Sentencia while
        struct {
            struct ASTNode *condition;
            struct ASTNode *body;
        } while_stmt;
        
        // Sentencia for
        struct {
            struct ASTNode *init;
            struct ASTNode *condition;
            struct ASTNode *update;
            struct ASTNode *body;
        } for_stmt;
        
        // Sentencia switch
        struct {
            struct ASTNode *expression;
            struct ASTNode *cases;
        } switch_stmt;
        
        // Caso de switch
        struct {
            struct ASTNode *value;  // NULL para default
            struct ASTNode *statements;
        } case_stmt;
        
        // Sentencia return
        struct {
            struct ASTNode *value;  // NULL para return sin valor
        } return_stmt;
        
        // Asignación
        struct {
            struct ASTNode *left;
            char *operator;
            struct ASTNode *right;
        } assignment;
        
        // Operación binaria
        struct {
            char *operator;
            struct ASTNode *left;
            struct ASTNode *right;
        } binary_op;
        
        // Operación unaria
        struct {
            char *operator;
            struct ASTNode *operand;
            bool is_prefix;
        } unary_op;
        
        // Llamada a función
        struct {
            char *name;
            struct ASTNode *arguments;
        } func_call;
        
        // Acceso a arreglo
        struct {
            struct ASTNode *array;
            struct ASTNode *index;
        } array_access;
        
        // Inicialización de arreglo
        struct {
            char *type;
            struct ASTNode *size;
            struct ASTNode *values;  // Lista de valores iniciales
        } array_init;
        
        // Literales
        struct {
            int value;
        } int_literal;
        
        struct {
            float value;
        } float_literal;
        
        struct {
            char *value;
        } string_literal;
        
        struct {
            char value;
        } char_literal;
        
        struct {
            bool value;
        } boolean_literal;
        
        // Identificador
        struct {
            char *name;
        } identifier;
        
        // Tipo
        struct {
            char *name;
            bool is_array;
            int array_dimensions;
        } type;
        
        // Lista genérica
        struct {
            struct ASTNode **items;
            int count;
            int capacity;
        } list;
    } data;
    
    struct ASTNode *next;  // Para listas enlazadas
} ASTNode;

// Funciones para crear nodos del AST
ASTNode* create_node(NodeType type, int line, int col);
ASTNode* create_program_node(ASTNode *body);
ASTNode* create_main_class_node(ASTNode *body);
ASTNode* create_var_decl_node(const char *type, const char *name, ASTNode *init, bool is_array, int array_size);
ASTNode* create_function_decl_node(const char *return_type, const char *name, ASTNode *params, ASTNode *body);
ASTNode* create_parameter_node(const char *type, const char *name, bool is_array);
ASTNode* create_block_node();
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
ASTNode* create_null_literal_node();
ASTNode* create_identifier_node(const char *name);
ASTNode* create_list_node();

// Funciones para manipular listas
void add_to_list(ASTNode *list, ASTNode *item);
ASTNode* get_from_list(ASTNode *list, int index);
int get_list_size(ASTNode *list);

// Funciones para manipular el AST
void print_ast(ASTNode *node, int depth);
void free_ast(ASTNode *node);
ASTNode* clone_ast(ASTNode *node);

// Variables globales del parser
extern ASTNode *ast_root;
extern bool has_syntax_errors;

#endif