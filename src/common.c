
#include "common.h"

// Variables globales
int line_num = 1;
int col_num = 1;
Error *error_list = NULL;  // Cambio a puntero para lista enlazada
int error_count = 0;
bool has_errors = false;

// Inicializar sistema de errores
void initialize_error_system() {
    error_list = NULL;
    error_count = 0;
    has_errors = false;
}

// Limpiar sistema de errores
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
    error_count = 0;
    has_errors = false;
}

// Agregar error
void add_error(ErrorType type, const char* message, const char* scope, int line, int col) {
    if (error_count >= MAX_ERRORS) {
        fprintf(stderr, "⚠️  Límite de errores alcanzado (%d)\n", MAX_ERRORS);
        return;
    }
    
    Error *new_error = malloc(sizeof(Error));
    if (!new_error) {
        fprintf(stderr, "Error: No se pudo asignar memoria para error\n");
        return;
    }
    
    new_error->type = type;
    new_error->message = strdup(message);
    new_error->scope = strdup(scope ? scope : "Global");
    new_error->line = line;
    new_error->column = col;
    new_error->next = error_list;
    
    error_list = new_error;
    error_count++;
    has_errors = true;
}

// Obtener nombre del tipo de error
const char* get_error_type_name(ErrorType type) {
    switch (type) {
        case ERROR_LEXICAL: return "LÉXICO";
        case ERROR_SYNTACTIC: return "SINTÁCTICO";
        case ERROR_SEMANTIC: return "SEMÁNTICO";
        case ERROR_RUNTIME: return "EJECUCIÓN";
        default: return "DESCONOCIDO";
    }
}

// Imprimir errores
void print_errors() {
    if (!error_list) {
        printf("✅ No se encontraron errores\n");
        return;
    }
    
    printf("\n🚨 ERRORES ENCONTRADOS (%d):\n", error_count);
    printf("═══════════════════════════════════════════════════════════\n");
    
    Error *current = error_list;
    int error_num = 1;
    
    while (current) {
        printf("\n📍 Error #%d [%s]\n", error_num++, get_error_type_name(current->type));
        printf("   📍 Línea: %d, Columna: %d\n", current->line, current->column);
        printf("   📍 Ámbito: %s\n", current->scope);
        printf("   📍 Mensaje: %s\n", current->message);
        printf("   ────────────────────────────────────────────────────\n");
        
        current = current->next;
    }
    
    printf("\n📊 Total de errores: %d\n", error_count);
}

// Limpiar errores
void clear_errors() {
    cleanup_error_system();
    initialize_error_system();
}

// Verificar si hay errores
bool has_any_errors() {
    return has_errors;
}

// Generar reporte de errores
void generate_error_report(const char* filename) {
    if (!filename) {
        printf("⚠️  Nombre de archivo no válido para reporte\n");
        return;
    }
    
    FILE *file = fopen(filename, "w");
    if (!file) {
        printf("⚠️  No se pudo crear el archivo de reporte: %s\n", filename);
        return;
    }
    
    fprintf(file, "REPORTE DE ERRORES - JAVALANG COMPILER\n");
    fprintf(file, "=====================================\n\n");
    fprintf(file, "Total de errores encontrados: %d\n\n", error_count);
    
    if (error_list) {
        Error *current = error_list;
        int error_num = 1;
        
        while (current) {
            fprintf(file, "Error #%d: %s\n", error_num++, get_error_type_name(current->type));
            fprintf(file, "  Línea: %d, Columna: %d\n", current->line, current->column);
            fprintf(file, "  Ámbito: %s\n", current->scope);
            fprintf(file, "  Descripción: %s\n\n", current->message);
            
            current = current->next;
        }
    } else {
        fprintf(file, "No se encontraron errores.\n");
    }
    
    fclose(file);
    printf("📄 Reporte de errores generado: %s\n", filename);
}

// Convertir string a DataType
DataType string_to_data_type(const char* type_str) {
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

// Convertir DataType a string
const char* data_type_to_string(DataType type) {
    switch (type) {
        case TYPE_INT: return "int";
        case TYPE_FLOAT: return "float";
        case TYPE_DOUBLE: return "double";
        case TYPE_BOOLEAN: return "boolean";
        case TYPE_CHAR: return "char";
        case TYPE_STRING: return "String";
        case TYPE_VOID: return "void";
        case TYPE_ARRAY: return "array";
        case TYPE_NULL: return "null";
        case TYPE_UNKNOWN: return "unknown";
        default: return "unknown";
    }
}

// Verificar si es tipo numérico
bool is_numeric_type(DataType type) {
    return type == TYPE_INT || type == TYPE_FLOAT || type == TYPE_DOUBLE;
}

// Función para obtener el nombre del tipo de token (para debugging)
const char* get_token_name(int token) {
    switch (token) {
        case 1: return "PUBLIC";
        case 2: return "PRIVATE";
        case 3: return "PROTECTED";
        case 4: return "STATIC";
        case 5: return "FINAL";
        case 6: return "VOID";
        case 7: return "MAIN";
        case 8: return "INT";
        case 9: return "FLOAT";
        case 10: return "DOUBLE";
        case 11: return "BOOLEAN";
        case 12: return "CHAR";
        case 13: return "STRING_TYPE";
        case 14: return "IF";
        case 15: return "ELSE";
        default: return "UNKNOWN";
    }
}

// Imprimir resumen de compilación
void print_compilation_summary() {
    printf("\n");
    printf("╔══════════════════════════════════════════════════════════╗\n");
    printf("║                  RESUMEN DE COMPILACIÓN                 ║\n");
    printf("╚══════════════════════════════════════════════════════════╝\n");
    
    if (error_count == 0) {
        printf("✅ Compilación exitosa - Sin errores\n");
        printf("📊 Estado: EXITOSO\n");
    } else {
        printf("❌ Compilación fallida\n");
        printf("📊 Errores encontrados: %d\n", error_count);
        
        // Contar errores por tipo
        int lexical = 0, syntactic = 0, semantic = 0, runtime = 0;
        Error *current = error_list;
        
        while (current) {
            switch (current->type) {
                case ERROR_LEXICAL: lexical++; break;
                case ERROR_SYNTACTIC: syntactic++; break;
                case ERROR_SEMANTIC: semantic++; break;
                case ERROR_RUNTIME: runtime++; break;
            }
            current = current->next;
        }
        
        if (lexical > 0) printf("   🔤 Errores léxicos: %d\n", lexical);
        if (syntactic > 0) printf("   📝 Errores sintácticos: %d\n", syntactic);
        if (semantic > 0) printf("   🧠 Errores semánticos: %d\n", semantic);
        if (runtime > 0) printf("   ⚡ Errores de ejecución: %d\n", runtime);
    }
    
    printf("════════════════════════════════════════════════════════════\n");
}