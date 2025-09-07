
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#include "ast.h"
#include "semantic.h"
#include "common.h"

// Declaraciones externas
extern FILE *yyin;
extern int yyparse();
extern ASTNode *ast_root;

// Funciones auxiliares
void print_help();
void print_banner();
void process_file(const char *filename);
void generate_reports(const char *filename);
void generate_complete_reports(const char *filename);
void visualize_ast(const char *filename);
char* get_base_filename(const char *filepath);

int main(int argc, char *argv[]) {
    print_banner();
    
    // Verificar argumentos
    if (argc != 2) {
        print_help();
        return 1;
    }
    
    const char *filename = argv[1];
    
    // Verificar que el archivo existe
    if (access(filename, F_OK) != 0) {
        printf("❌ Error: Archivo '%s' no encontrado\n", filename);
        return 1;
    }
    
    // Verificar extensión .usl
    if (strlen(filename) < 4 || strcmp(filename + strlen(filename) - 4, ".usl") != 0) {
        printf("⚠️  Advertencia: El archivo no tiene extensión .usl\n");
    }
    
    printf("🔍 Analizando archivo: %s\n", filename);
    printf("═══════════════════════════════════════════════════════════\n");
    
    // Inicializar sistema de errores
    initialize_error_system();
    
    // Procesar archivo
    process_file(filename);
    
    // Limpiar sistema de errores al finalizar
    if (has_any_errors()) {
        cleanup_error_system();
        return 1;
    }
    
    cleanup_error_system();
    return 0;
}

void print_banner() {
    printf("\n");
    printf("╔════════════════════════════════════════════════════════════════════════╗\n");
    printf("║                      COMPILADOR JAVALANG                              ║\n");
    printf("║                   Interpretador Educativo v1.0                        ║\n");
    printf("║                Universidad San Carlos de Guatemala                     ║\n");
    printf("╚════════════════════════════════════════════════════════════════════════╝\n\n");
}

void print_help() {
    printf("📖 USO: %s <archivo.usl>\n\n", "javalang_interpreter");
    printf("📝 DESCRIPCIÓN:\n");
    printf("   Compilador e intérprete para el lenguaje JavaLang\n\n");
    printf("📄 PARÁMETROS:\n");
    printf("   archivo.usl    Archivo fuente de JavaLang a compilar\n\n");
    printf("📊 SALIDAS:\n");
    printf("   - Reporte de análisis léxico\n");
    printf("   - Reporte de análisis sintáctico (AST)\n");
    printf("   - Reporte de análisis semántico\n");
    printf("   - Tabla de símbolos\n");
    printf("   - Reporte de errores (si los hay)\n\n");
    printf("📁 EJEMPLOS:\n");
    printf("   ./javalang_interpreter examples/test1.usl\n");
    printf("   ./javalang_interpreter mi_programa.usl\n\n");
}

void process_file(const char *filename) {
    // Abrir archivo
    yyin = fopen(filename, "r");
    if (!yyin) {
        printf("❌ Error: No se pudo abrir el archivo '%s'\n", filename);
        add_error(ERROR_LEXICAL, "No se pudo abrir el archivo", "Global", 0, 0);
        return;
    }
    
    printf("📖 Fase 1: Análisis Léxico\n");
    printf("📖 Fase 2: Análisis Sintáctico\n");
    printf("📖 Fase 3: Construcción del AST\n");
    
    // Realizar análisis sintáctico (que incluye el léxico)
    int parse_result = yyparse();
    fclose(yyin);
    
    if (parse_result != 0) {
        printf("❌ Error en análisis sintáctico\n");
        add_error(ERROR_SYNTACTIC, "Error en análisis sintáctico", "Global", line_num, col_num);
        print_errors();
        return;
    }
    
    if (!ast_root) {
        printf("❌ Error: No se pudo construir el AST\n");
        add_error(ERROR_SYNTACTIC, "No se pudo construir el AST", "Global", line_num, col_num);
        print_errors();
        return;
    }
    
    printf("✅ AST construido exitosamente\n");
    
    // Fase 4: Análisis semántico
    printf("📖 Fase 4: Análisis Semántico\n");
    
    SemanticAnalyzer *analyzer = create_semantic_analyzer();
    if (!analyzer) {
        printf("❌ Error: No se pudo crear el analizador semántico\n");
        add_error(ERROR_SEMANTIC, "No se pudo crear analizador semántico", "Global", 0, 0);
        print_errors();
        return;
    }
    
    bool semantic_ok = analyze_semantic(analyzer, ast_root);
    
    if (!semantic_ok || analyzer->error_count > 0) {
        printf("❌ Errores encontrados en análisis semántico (%d errores)\n", analyzer->error_count);
        // Los errores del analizador semántico se manejan internamente
    } else {
        printf("✅ Análisis semántico completado sin errores\n");
    }
    
    // Generar reportes
    printf("\n📊 Generando reportes...\n");
    generate_complete_reports(filename);
    
    // Visualizar AST si es posible
    visualize_ast(filename);
    
    // Mostrar resumen final
    print_compilation_summary();
    
    // Limpiar memoria
    if (ast_root) {
        free_ast(ast_root);
    }
    
    // No liberar analyzer aquí, se hace en cleanup_error_system
}

void generate_complete_reports(const char *filename) {
    char *base = get_base_filename(filename);
    if (!base) return;
    
    // Generar reporte de errores
    char report_filename[512];
    snprintf(report_filename, sizeof(report_filename), "%s_errors.txt", base);
    generate_error_report(report_filename);
    
    // Generar reporte del AST
    char ast_filename[512];
    snprintf(ast_filename, sizeof(ast_filename), "%s_ast.txt", base);
    
    FILE *ast_file = fopen(ast_filename, "w");
    if (ast_file) {
        fprintf(ast_file, "ÁRBOL DE SINTAXIS ABSTRACTA (AST)\n");
        fprintf(ast_file, "==================================\n\n");
        
        if (ast_root) {
            // Aquí se podría implementar una función para imprimir el AST a archivo
            fprintf(ast_file, "AST generado exitosamente.\n");
            fprintf(ast_file, "Tipo de nodo raíz: %d\n", ast_root->type);
        } else {
            fprintf(ast_file, "No se pudo generar el AST.\n");
        }
        
        fclose(ast_file);
        printf("📄 Reporte AST generado: %s\n", ast_filename);
    }
    
    free(base);
}

void visualize_ast(const char *filename) {
    char *base = get_base_filename(filename);
    if (!base) return;
    
    // Intentar generar visualización con Graphviz
    char dot_filename[512];
    char png_filename[512];
    snprintf(dot_filename, sizeof(dot_filename), "%s_ast.dot", base);
    snprintf(png_filename, sizeof(png_filename), "%s_ast.png", base);
    
    // Verificar si Graphviz está disponible
    if (system("which dot > /dev/null 2>&1") == 0) {
        // Generar archivo DOT (esto requeriría implementar export_ast_to_dot)
        printf("🎨 Visualización AST disponible con Graphviz\n");
        
        char command[1024];
        snprintf(command, sizeof(command), "dot -Tpng %s -o %s 2>/dev/null", dot_filename, png_filename);
        
        if (system(command) == 0) {
            printf("🖼️  Imagen AST generada: %s\n", png_filename);
        }
    }
    
    free(base);
}

char* get_base_filename(const char *filepath) {
    if (!filepath) return NULL;
    
    char *path_copy = strdup(filepath);
    if (!path_copy) return NULL;
    
    // Obtener solo el nombre del archivo sin la ruta
    char *base = strrchr(path_copy, '/');
    base = base ? base + 1 : path_copy;
    
    // Crear copia del nombre base
    char *result = strdup(base);
    
    // Remover extensión si existe
    char *dot = strrchr(result, '.');
    if (dot) *dot = '\0';
    
    free(path_copy);
    return result;
}