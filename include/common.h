#ifndef COMMON_H
#define COMMON_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

// Variables globales
extern int line_num;
extern int col_num;

// Tipos de errores
typedef enum {
    ERROR_LEXICAL,
    ERROR_SYNTACTIC,
    ERROR_SEMANTIC
} ErrorType;

// Estructura de error
typedef struct Error {
    ErrorType type;
    char *message;
    char *scope;
    int line;
    int column;
    struct Error *next;
} Error;

// Lista global de errores
extern Error *error_list;

// Funciones
void add_error(ErrorType type, char *message, char *scope, int line, int column);
void print_errors();
void clear_errors();

#endif
