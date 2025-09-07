#ifndef SEMANTIC_H
#define SEMANTIC_H

#include "ast.h"
#include "common.h"
#include <stdbool.h>

// Tipos de símbolos en la tabla
typedef enum {
    SYMBOL_VARIABLE,
    SYMBOL_FUNCTION,
    SYMBOL_PARAMETER,
    SYMBOL_CONSTANT
} SymbolType;

// Estructura de símbolo en la tabla
typedef struct Symbol {
    char *id;                      // Identificador del símbolo
    SymbolType symbol_type;        // Tipo de símbolo (variable, función, etc.)
    DataType data_type;            // Tipo de dato (int, float, etc.)
    char *scope;                   // Ámbito del símbolo
    int line;                      // Línea de declaración
    int column;                    // Columna de declaración
    bool is_array;                 // Si es un arreglo
    int array_size;                // Tamaño del arreglo (si aplica)
    bool is_initialized;           // Si ha sido inicializada
    bool is_constant;              // Si es constante (final)
    
    // Para funciones
    struct ASTNode *parameters;    // Lista de parámetros
    DataType return_type;          // Tipo de retorno (solo para funciones)
    
    struct Symbol *next;           // Siguiente símbolo (lista enlazada)
} Symbol;

// Estructura del analizador semántico
typedef struct SemanticAnalyzer {
    Symbol *symbol_table;          // Tabla de símbolos (lista enlazada)
    char *current_scope;           // Ámbito actual
    int scope_level;               // Nivel de anidamiento de ámbitos
    bool has_main_function;        // Si existe función main
    bool in_function;              // Si estamos dentro de una función
    DataType current_function_return_type; // Tipo de retorno de función actual
} SemanticAnalyzer;

// Funciones principales del analizador semántico
SemanticAnalyzer* create_semantic_analyzer();
void destroy_semantic_analyzer(SemanticAnalyzer *analyzer);

// Funciones de tabla de símbolos
Symbol* create_symbol(const char *id, SymbolType symbol_type, DataType data_type, 
                     const char *scope, int line, int column);
bool add_symbol(SemanticAnalyzer *analyzer, Symbol *symbol);
Symbol* lookup_symbol(SemanticAnalyzer *analyzer, const char *id);
Symbol* lookup_symbol_in_scope(SemanticAnalyzer *analyzer, const char *id, const char *scope);
void print_symbol_table(SemanticAnalyzer *analyzer);

// Funciones de análisis semántico del AST
bool analyze_semantic(SemanticAnalyzer *analyzer, ASTNode *node);
bool analyze_program(SemanticAnalyzer *analyzer, ASTNode *node);
bool analyze_main_class(SemanticAnalyzer *analyzer, ASTNode *node);
bool analyze_function_declaration(SemanticAnalyzer *analyzer, ASTNode *node);
bool analyze_variable_declaration(SemanticAnalyzer *analyzer, ASTNode *node);
bool analyze_assignment(SemanticAnalyzer *analyzer, ASTNode *node);
bool analyze_expression(SemanticAnalyzer *analyzer, ASTNode *node, DataType *result_type);
bool analyze_function_call(SemanticAnalyzer *analyzer, ASTNode *node, DataType *result_type);
bool analyze_statement_list(SemanticAnalyzer *analyzer, ASTNode *node);
bool analyze_if_statement(SemanticAnalyzer *analyzer, ASTNode *node);
bool analyze_while_statement(SemanticAnalyzer *analyzer, ASTNode *node);
bool analyze_for_statement(SemanticAnalyzer *analyzer, ASTNode *node);
bool analyze_return_statement(SemanticAnalyzer *analyzer, ASTNode *node);

// Funciones de validación de tipos
bool is_compatible_types(DataType type1, DataType type2);
DataType get_binary_operation_result_type(const char *operator, DataType left_type, DataType right_type);
DataType get_unary_operation_result_type(const char *operator, DataType operand_type);
bool is_valid_assignment(DataType target_type, DataType source_type);
bool is_numeric_type(DataType type);
bool is_boolean_type(DataType type);

// Funciones de gestión de ámbitos
void enter_scope(SemanticAnalyzer *analyzer, const char *scope_name);
void exit_scope(SemanticAnalyzer *analyzer);
char* get_current_scope(SemanticAnalyzer *analyzer);

// Funciones de reportes
void generate_symbol_table_report(SemanticAnalyzer *analyzer, const char *filename);
void generate_semantic_errors_report(const char *filename);

// Función auxiliar para obtener string del tipo de dato
const char* data_type_to_string(DataType type);
const char* symbol_type_to_string(SymbolType type);

#endif // SEMANTIC_H