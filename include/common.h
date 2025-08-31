#ifndef COMMON_H
#define COMMON_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>

// Constantes del proyecto
#define MAX_IDENTIFIER_LEN 256
#define MAX_STRING_LEN 1024
#define MAX_ERRORS 100
#define MAX_SYMBOLS 1000

// Tipos de datos del lenguaje JavaLang
typedef enum {
    TYPE_INT,
    TYPE_FLOAT,
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

// Estructura para manejo de errores
typedef struct {
    ErrorType type;
    char message[MAX_STRING_LEN];
    char scope[MAX_IDENTIFIER_LEN];
    int line;
    int column;
} Error;

// SOLO DECLARACIONES EXTERN (no definiciones)
extern int line_num;
extern int col_num;
extern Error errors[MAX_ERRORS];
extern int error_count;
extern bool has_errors;

// Funciones utilitarias
char* data_type_to_string(DataType type);
DataType string_to_data_type(const char* str);
void add_error(ErrorType type, const char* message, const char* scope, int line, int col);
void print_errors(void);
void clear_errors(void);

#endif // COMMON_H
