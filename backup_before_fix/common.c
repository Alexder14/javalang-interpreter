#include "common.h"

// DEFINICIONES de variables globales (solo aquí)
int line_num = 1;
int col_num = 1;
Error errors[MAX_ERRORS];
int error_count = 0;
bool has_errors = false;

char* data_type_to_string(DataType type) {
    switch (type) {
        case TYPE_INT: return "int";
        case TYPE_FLOAT: return "float";
        case TYPE_BOOLEAN: return "boolean";
        case TYPE_STRING: return "String";
        case TYPE_CHAR: return "char";
        case TYPE_VOID: return "void";
        case TYPE_ARRAY: return "array";
        case TYPE_NULL: return "null";
        default: return "unknown";
    }
}

DataType string_to_data_type(const char* str) {
    if (strcmp(str, "int") == 0) return TYPE_INT;
    if (strcmp(str, "float") == 0) return TYPE_FLOAT;
    if (strcmp(str, "boolean") == 0) return TYPE_BOOLEAN;
    if (strcmp(str, "String") == 0) return TYPE_STRING;
    if (strcmp(str, "char") == 0) return TYPE_CHAR;
    if (strcmp(str, "void") == 0) return TYPE_VOID;
    return TYPE_UNKNOWN;
}

void add_error(ErrorType type, const char* message, const char* scope, int line, int col) {
    if (error_count < MAX_ERRORS) {
        errors[error_count].type = type;
        strncpy(errors[error_count].message, message, MAX_STRING_LEN - 1);
        errors[error_count].message[MAX_STRING_LEN - 1] = '\0';
        strncpy(errors[error_count].scope, scope, MAX_IDENTIFIER_LEN - 1);
        errors[error_count].scope[MAX_IDENTIFIER_LEN - 1] = '\0';
        errors[error_count].line = line;
        errors[error_count].column = col;
        error_count++;
        has_errors = true;
    }
}

void print_errors(void) {
    printf("\n=== REPORTE DE ERRORES ===\n");
    printf("No. | Descripción | Ámbito | Línea | Columna\n");
    printf("----|-------------|--------|-------|--------\n");
    
    for (int i = 0; i < error_count; i++) {
        printf("%3d | %s | %s | %5d | %7d\n",
               i + 1,
               errors[i].message,
               errors[i].scope,
               errors[i].line,
               errors[i].column);
    }
    printf("\nTotal de errores: %d\n", error_count);
}

void clear_errors(void) {
    error_count = 0;
    has_errors = false;
}
