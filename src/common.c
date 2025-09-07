#include "common.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Variables globales para errores
bool has_lexical_errors = false;
bool has_syntax_errors = false;
bool has_semantic_errors = false;
bool has_runtime_errors = false;
Error *error_list = NULL;

// ==========================================
// FUNCIONES DE MANEJO DE ERRORES
// ==========================================

void initialize_error_system() {
    has_lexical_errors = false;
    has_syntax_errors = false;
    has_semantic_errors = false;
    has_runtime_errors = false;
    error_list = NULL;
}

void cleanup_error_system() {
    Error *current = error_list;
    while (current) {
        Error *next = current->next;
        free(current->message);
        free(current->scope);
        free(current);
        current = next;
    }
    error_list = NULL;
}

void add_error(ErrorType type, const char *message, const char *scope, int line, int column) {
    Error *new_error = malloc(sizeof(Error));
    if (!new_error) {
        fprintf(stderr, "Error: No se pudo asignar memoria para error\n");
        return;
    }
    
    new_error->type = type;
    new_error->message = strdup(message);
    new_error->scope = strdup(scope ? scope : "Global");
    new_error->line = line;
    new_error->column = column;
    new_error->next = error_list;
    error_list = new_error;
    
    // Actualizar flags de errores
    switch (type) {
        case ERROR_LEXICAL:
            has_lexical_errors = true;
            break;
        case ERROR_SYNTACTIC:
            has_syntax_errors = true;
            break;
        case ERROR_SEMANTIC:
            has_semantic_errors = true;
            break;
        case ERROR_RUNTIME:
            has_runtime_errors = true;
            break;
    }
}

void print_errors() {
    if (!error_list) {
        printf("✅ No se encontraron errores\n");
        return;
    }
    
    printf("\n=== ERRORES ENCONTRADOS ===\n");
    printf("%-4s %-12s %-40s %-15s %-6s %-6s\n", 
           "No.", "Tipo", "Descripción", "Ámbito", "Línea", "Columna");
    printf("──────────────────────────────────────────────────────────────────────────────\n");
    
    Error *current = error_list;
    int count = 1;
    while (current) {
        const char *type_str;
        switch (current->type) {
            case ERROR_LEXICAL: type_str = "LÉXICO"; break;
            case ERROR_SYNTACTIC: type_str = "SINTÁCTICO"; break;
            case ERROR_SEMANTIC: type_str = "SEMÁNTICO"; break;
            case ERROR_RUNTIME: type_str = "EJECUCIÓN"; break;
            default: type_str = "DESCONOCIDO"; break;
        }
        
        printf("%-4d %-12s %-40s %-15s %-6d %-6d\n",
               count++, type_str, current->message, current->scope,
               current->line, current->column);
        current = current->next;
    }
    printf("\n");
}

void generate_error_report(const char *filename) {
    FILE *file = fopen(filename, "w");
    if (!file) {
        fprintf(stderr, "Error: No se pudo crear archivo de reporte de errores\n");
        return;
    }
    
    fprintf(file, "=== REPORTE DE ERRORES ===\n");
    fprintf(file, "Generado: %s\n\n", __DATE__);
    
    if (!error_list) {
        fprintf(file, "✅ No se encontraron errores\n");
    } else {
        fprintf(file, "%-4s %-12s %-40s %-15s %-6s %-6s\n", 
                "No.", "Tipo", "Descripción", "Ámbito", "Línea", "Columna");
        fprintf(file, "──────────────────────────────────────────────────────────────────────────────\n");
        
        Error *current = error_list;
        int count = 1;
        while (current) {
            const char *type_str;
            switch (current->type) {
                case ERROR_LEXICAL: type_str = "LÉXICO"; break;
                case ERROR_SYNTACTIC: type_str = "SINTÁCTICO"; break;
                case ERROR_SEMANTIC: type_str = "SEMÁNTICO"; break;
                case ERROR_RUNTIME: type_str = "EJECUCIÓN"; break;
                default: type_str = "DESCONOCIDO"; break;
            }
            
            fprintf(file, "%-4d %-12s %-40s %-15s %-6d %-6d\n",
                    count++, type_str, current->message, current->scope,
                    current->line, current->column);
            current = current->next;
        }
    }
    
    fclose(file);
    printf("Reporte de errores generado: %s\n", filename);
}

bool has_any_errors() {
    return has_lexical_errors || has_syntax_errors || has_semantic_errors || has_runtime_errors;
}

// ==========================================
// FUNCIONES AUXILIARES PARA TIPOS DE DATOS
// ==========================================

DataType string_to_data_type(const char *type_str) {
    if (!type_str) return TYPE_UNKNOWN;
    
    if (strcmp(type_str, "int") == 0) return TYPE_INT;
    if (strcmp(type_str, "float") == 0) return TYPE_FLOAT;
    if (strcmp(type_str, "double") == 0) return TYPE_DOUBLE;
    if (strcmp(type_str, "boolean") == 0) return TYPE_BOOLEAN;
    if (strcmp(type_str, "char") == 0) return TYPE_CHAR;
    if (strcmp(type_str, "String") == 0) return TYPE_STRING;
    if (strcmp(type_str, "void") == 0) return TYPE_VOID;
    
    return TYPE_UNKNOWN;
}

const char* data_type_to_string(DataType type) {
    switch (type) {
        case TYPE_INT: return "int";
        case TYPE_FLOAT: return "float";
        case TYPE_DOUBLE: return "double";
        case TYPE_BOOLEAN: return "boolean";
        case TYPE_CHAR: return "char";
        case TYPE_STRING: return "String";
        case TYPE_VOID: return "void";
        case TYPE_UNKNOWN: return "unknown";
        default: return "invalid";
    }
}

bool is_numeric_type(DataType type) {
    return type == TYPE_INT || type == TYPE_FLOAT || type == TYPE_DOUBLE;
}

bool is_valid_type(DataType type) {
    return type != TYPE_UNKNOWN;
}

// ==========================================
// FUNCIONES DE UTILIDAD
// ==========================================

char* create_temp_filename(const char *prefix, const char *extension) {
    static char filename[256];
    time_t now = time(NULL);
    snprintf(filename, sizeof(filename), "%s_%ld.%s", prefix, now, extension);
    return filename;
}

void print_compilation_summary() {
    printf("\n=== RESUMEN DE COMPILACIÓN ===\n");
    
    if (has_lexical_errors) {
        printf("❌ Errores léxicos encontrados\n");
    } else {
        printf("✅ Análisis léxico: Sin errores\n");
    }
    
    if (has_syntax_errors) {
        printf("❌ Errores sintácticos encontrados\n");
    } else {
        printf("✅ Análisis sintáctico: Sin errores\n");
    }
    
    if (has_semantic_errors) {
        printf("❌ Errores semánticos encontrados\n");
    } else {
        printf("✅ Análisis semántico: Sin errores\n");
    }
    
    if (has_runtime_errors) {
        printf("❌ Errores de ejecución encontrados\n");
    }
    
    printf("\n📈 Estadísticas:\n");
    
    // Contar errores por tipo
    int lexical_count = 0, syntax_count = 0, semantic_count = 0, runtime_count = 0;
    Error *current = error_list;
    while (current) {
        switch (current->type) {
            case ERROR_LEXICAL: lexical_count++; break;
            case ERROR_SYNTACTIC: syntax_count++; break;
            case ERROR_SEMANTIC: semantic_count++; break;
            case ERROR_RUNTIME: runtime_count++; break;
        }
        current = current->next;
    }
    
    printf("   - Errores léxicos: %d\n", lexical_count);
    printf("   - Errores sintácticos: %d\n", syntax_count);
    printf("   - Errores semánticos: %d\n", semantic_count);
    if (runtime_count > 0) {
        printf("   - Errores de ejecución: %d\n", runtime_count);
    }
    
    if (!has_any_errors()) {
        printf("\n🎉 ¡Compilación exitosa! El programa está listo.\n");
    } else {
        printf("\n⚠️  Compilación completada con errores.\n");
    }
}