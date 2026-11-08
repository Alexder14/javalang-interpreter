#ifndef SEMANTIC_H
#define SEMANTIC_H

#include "ast.h"
#include "common.h"

// Tipos de símbolos
typedef enum {
    SYMBOL_VARIABLE,
    SYMBOL_FUNCTION,
    SYMBOL_PARAMETER,
    SYMBOL_CONSTANT
} SymbolType;

// Estructura para errores semánticos
typedef struct SemanticError {
    char *message;
    char *context;
    char *scope;                 // Ámbito donde ocurrió (función); "Global" si no hay
    int line;
    int column;
    struct SemanticError *next;
} SemanticError;

// Estructura de símbolo en la tabla de símbolos
typedef struct Symbol {
    char *id;                    // Nombre del símbolo
    SymbolType symbol_type;      // Cambiado de 'type' a 'symbol_type' para evitar confusión
    DataType data_type;          // Tipo de dato
    char *scope;                 // Ámbito del símbolo
    int line;                    // Línea de declaración
    int column;                  // Columna de declaración
    bool is_initialized;         // Si está inicializada (para variables)
    bool is_array;               // Si es un arreglo
    int array_size;              // Tamaño del arreglo
    int dims;                    // Dimensiones (0 = escalar, 1 = vector, 2 = matriz...)
    bool is_const;               // Declarada con final
    struct ASTNode *decl;        // Nodo del AST donde se declaró
    struct ASTNode *parameters;  // Parámetros (para funciones)
    struct ASTNode *value;       // Valor inicial
    struct Symbol *next;         // Siguiente en la tabla hash/lista
} Symbol;

// Analizador semántico
typedef struct SemanticAnalyzer {
    Symbol *symbol_table;        // Tabla de símbolos
    char *current_scope;         // Ámbito actual
    int scope_level;             // Nivel de anidamiento
    Symbol *current_function;    // Función actual
    SemanticError *errors;       // Lista de errores semánticos
    int error_count;             // Contador de errores
    bool in_loop;                // Si estamos dentro de un bucle
    bool in_function;            // Si estamos dentro de una función (o de main)
    bool in_switch;              // Si estamos dentro de un switch
} SemanticAnalyzer;

// Funciones principales
SemanticAnalyzer* create_semantic_analyzer();
void destroy_semantic_analyzer(SemanticAnalyzer *analyzer);
bool analyze_semantic(SemanticAnalyzer *analyzer, ASTNode *node);

// Funciones de tabla de símbolos
Symbol* create_symbol(const char *id, SymbolType type, DataType data_type, 
                     const char *scope, int line, int col);
Symbol* lookup_symbol(SemanticAnalyzer *analyzer, const char *id);
bool add_symbol(SemanticAnalyzer *analyzer, Symbol *symbol);
void print_symbol_table(SemanticAnalyzer *analyzer);

// Funciones de manejo de errores
void add_semantic_error(SemanticAnalyzer *analyzer, const char *message, 
                       const char *context, int line, int col);
void print_semantic_errors(SemanticAnalyzer *analyzer);
void generate_semantic_errors_report(const char *filename);

// Funciones de análisis específico
bool analyze_function_declaration(SemanticAnalyzer *analyzer, ASTNode *node);
bool analyze_variable_declaration(SemanticAnalyzer *analyzer, ASTNode *node);
bool analyze_assignment(SemanticAnalyzer *analyzer, ASTNode *node);
bool analyze_function_call(SemanticAnalyzer *analyzer, ASTNode *node);
bool analyze_if_statement(SemanticAnalyzer *analyzer, ASTNode *node);
bool analyze_while_statement(SemanticAnalyzer *analyzer, ASTNode *node);
bool analyze_for_statement(SemanticAnalyzer *analyzer, ASTNode *node);
bool analyze_return_statement(SemanticAnalyzer *analyzer, ASTNode *node);
bool analyze_expression(SemanticAnalyzer *analyzer, ASTNode *node, DataType *result_type);

// Funciones de validación de tipos
bool is_compatible_types(DataType type1, DataType type2);
DataType get_binary_operation_result_type(const char *operator, DataType left_type, DataType right_type);
bool is_arithmetic_operator(const char *op);
bool is_comparison_operator(const char *op);
bool is_logical_operator(const char *op);

// Funciones de manejo de ámbitos
void enter_scope(SemanticAnalyzer *analyzer, const char *scope_name);
void exit_scope(SemanticAnalyzer *analyzer);

// Funciones de utilidad
const char* symbol_type_to_string(SymbolType type);
const char* data_type_to_string(DataType type);  // Debe coincidir con common.h
DataType string_to_data_type(const char *str);

#endif