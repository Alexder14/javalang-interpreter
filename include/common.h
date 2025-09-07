#ifndef COMMON_H
#define COMMON_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// Constantes del proyecto
#define MAX_IDENTIFIER_LEN 256
#define MAX_STRING_LEN 1024
#define MAX_ERRORS 100
#define MAX_SYMBOLS 1000

// Tipos de datos del lenguaje JavaLang
typedef enum {
    TYPE_INT,
    TYPE_FLOAT,
    TYPE_DOUBLE,    // Agregado TYPE_DOUBLE que faltaba
    TYPE_BOOLEAN,
    TYPE_STRING,
    TYPE_CHAR,
    TYPE_VOID,
    TYPE_ARRAY,
    TYPE_NULL,
    TYPE_UNKNOWN
} DataType;

// Tipos de errores
typedef enum {
    ERROR_LEXICAL,
    ERROR_SYNTACTIC,
    ERROR_SEMANTIC,
    ERROR_RUNTIME
} ErrorType;

// Estructura para manejo de errores - CORREGIDA
typedef struct Error {
    ErrorType type;
    char *message;      // Cambiado de array a puntero
    char *scope;        // Cambiado de array a puntero
    int line;
    int column;
    struct Error *next; // Agregado para lista enlazada
} Error;

// Variables globales
extern int line_num;
extern int col_num;
extern Error *error_list;  // Cambiado a puntero
extern int error_count;
extern bool has_errors;

// Funciones utilitarias - CORREGIDAS las declaraciones
const char* data_type_to_string(DataType type);  // Consistente con semantic.h
DataType string_to_data_type(const char* str);
void add_error(ErrorType type, const char* message, const char* scope, int line, int col);
void print_errors();
void clear_errors();
bool has_any_errors();
void initialize_error_system();
void cleanup_error_system();
void generate_error_report(const char* filename);
void print_compilation_summary();
bool is_numeric_type(DataType type);

#endif