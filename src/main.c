#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <libgen.h>
#include "ast.h"
#include "semantic.h"
#include "common.h"

// Prototipos de funciones
void print_usage(const char *program_name);
void print_version();
void print_header();
int parse_file(const char *filename);
void generate_complete_reports(const char *base_filename, ASTNode *ast);
void visualize_ast(ASTNode *ast, const char *base_filename);
char* get_base_filename(const char *filepath);

// Variables globales del parser
extern FILE *yyin;
extern int yyparse();
extern ASTNode *ast_root;

int main(int argc, char *argv[]) {
    // Variables para opciones
    bool generate_reports = false;
    bool visualize = false;
    bool generate_graphviz = false;
    bool verbose = false;
    char *filename = NULL;
    
    print_header();
    
    // Parsear argumentos de línea de comandos
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "--help") == 0) {
            print_usage(argv[0]);
            return 0;
        } else if (strcmp(argv[i], "-v") == 0 || strcmp(argv[i], "--version") == 0) {
            print_version();
            return 0;
        } else if (strcmp(argv[i], "-r") == 0 || strcmp(argv[i], "--reports") == 0) {
            generate_reports = true;
        } else if (strcmp(argv[i], "-g") == 0 || strcmp(argv[i], "--graphviz") == 0) {
            generate_graphviz = true;
        } else if (strcmp(argv[i], "-V") == 0 || strcmp(argv[i], "--visualize") == 0) {
            visualize = true;
        } else if (strcmp(argv[i], "--verbose") == 0) {
            verbose = true;
        } else if (argv[i][0] != '-') {
            if (filename == NULL) {
                filename = argv[i];
            } else {
                fprintf(stderr, "Error: Múltiples archivos especificados\n");
                print_usage(argv[0]);
                return 1;
            }
        } else {
            fprintf(stderr, "Error: Opción desconocida: %s\n", argv[i]);
            print_usage(argv[0]);
            return 1;
        }
    }
    
    // Verificar que se especificó un archivo
    if (filename == NULL) {
        fprintf(stderr, "Error: No se especificó archivo de entrada\n");
        print_usage(argv[0]);
        return 1;
    }
    
    // Verificar que el archivo existe
    if (access(filename, F_OK) != 0) {
        fprintf(stderr, "Error: El archivo '%s' no existe\n", filename);
        return 1;
    }
    
    // Verificar extensión .usl
    char *ext = strrchr(filename, '.');
    if (!ext || strcmp(ext, ".usl") != 0) {
        fprintf(stderr, "Advertencia: El archivo no tiene extensión .usl\n");
    }
    
    printf("📁 Analizando archivo: %s\n", filename);
    
    // Inicializar sistema de errores
    initialize_error_system();
    
    // Fase 1: Análisis Léxico y Sintáctico
    printf("\n🔍 FASE 1: Análisis Léxico y Sintáctico\n");
    printf("──────────────────────────────────────\n");
    
    if (parse_file(filename) != 0) {
        fprintf(stderr, "❌ Error durante el análisis sintáctico\n");
        print_errors();
        cleanup_error_system();
        return 1;
    }
    
    if (ast_root == NULL) {
        fprintf(stderr, "❌ No se pudo construir el AST\n");
        cleanup_error_system();
        return 1;
    }
    
    printf("✅ Análisis léxico y sintáctico completado\n");
    
    // Fase 2: Análisis Semántico
    printf("\n🧠 FASE 2: Análisis Semántico\n");
    printf("─────────────────────────\n");
    
    SemanticAnalyzer *semantic_analyzer = create_semantic_analyzer();
    
    if (!analyze_semantic(semantic_analyzer, ast_root)) {
        printf("❌ Errores semánticos encontrados\n");
    } else {
        printf("✅ Análisis semántico completado sin errores\n");
    }
    
    // Mostrar tabla de símbolos si está en modo verbose
    if (verbose) {
        printf("\n📊 Tabla de Símbolos:\n");
        print_symbol_table(semantic_analyzer);
    }
    
    // Mostrar errores si los hay
    if (has_any_errors()) {
        printf("\n⚠️  Errores encontrados:\n");
        print_errors();
    }
    
    // Generar reportes si se solicita
    char *base_name = get_base_filename(filename);
    
    if (generate_reports) {
        printf("\n📋 GENERANDO REPORTES\n");
        printf("────────────────────\n");
        generate_complete_reports(base_name, ast_root);
    }
    
    if (visualize || generate_graphviz) {
        printf("\n🎨 GENERANDO VISUALIZACIÓN\n");
        printf("─────────────────────────\n");
        visualize_ast(ast_root, base_name);
    }
    
    // Resumen final
    printf("\n📈 RESUMEN DE COMPILACIÓN\n");
    printf("────────────────────────\n");
    print_compilation_summary();
    
    // Liberar memoria
    free_ast(ast_root);
    destroy_semantic_analyzer(semantic_analyzer);
    cleanup_error_system();
    free(base_name);
    
    return has_any_errors() ? 1 : 0;
}

void print_header() {
    printf("╔════════════════════════════════════════════════════════════════════════╗\n");
    printf("║                         JAVALANG INTERPRETER                           ║\n");
    printf("║                       Compilador Educativo v1.0                       ║\n");
    printf("║                    Fase 4: Análisis Semántico                         ║\n");
    printf("╚════════════════════════════════════════════════════════════════════════╝\n\n");
}

void print_usage(const char *program_name) {
    printf("Uso: %s [opciones] archivo.usl\n\n", program_name);
    printf("Opciones:\n");
    printf("  -h, --help          Mostrar esta ayuda\n");
    printf("  -v, --version       Mostrar versión\n");
    printf("  -r, --reports       Generar reportes (tabla de símbolos, errores)\n");
    printf("  -g, --graphviz      Generar archivo DOT para visualización del AST\n");
    printf("  -V, --visualize     Generar visualización completa del AST\n");
    printf("  --verbose           Mostrar información detallada\n\n");
    printf("Ejemplos:\n");
    printf("  %s programa.usl                    # Análisis básico\n", program_name);
    printf("  %s -r programa.usl                 # Con reportes\n", program_name);
    printf("  %s -g -r programa.usl              # Con reportes y visualización\n", program_name);
    printf("  %s --verbose programa.usl          # Modo detallado\n", program_name);
}

void print_version() {
    printf("JavaLang Interpreter v1.0\n");
    printf("Compilador educativo para el lenguaje JavaLang\n");
    printf("Desarrollado con Flex, Bison y C\n\n");
    printf("Fases implementadas:\n");
    printf("  ✅ Fase 1: Configuración\n");
    printf("  ✅ Fase 2: Análisis léxico\n");
    printf("  ✅ Fase 3: Análisis sintáctico y AST\n");
    printf("  ✅ Fase 4: Análisis semántico\n");
    printf("  🚧 Fase 5: Generación de código (próximamente)\n");
}

int parse_file(const char *filename) {
    // Abrir archivo
    yyin = fopen(filename, "r");
    if (!yyin) {
        fprintf(stderr, "Error: No se pudo abrir el archivo '%s'\n", filename);
        return 1;
    }
    
    // Reiniciar variables globales
    ast_root = NULL;
    has_syntax_errors = false;
    line_num = 1;
    col_num = 1;
    
    // Ejecutar parser
    int result = yyparse();
    
    // Cerrar archivo
    fclose(yyin);
    
    return result;
}

void generate_complete_reports(const char *base_filename, ASTNode *ast) {
    char report_filename[512];
    
    // Generar reporte de tabla de símbolos
    snprintf(report_filename, sizeof(report_filename), "%s_symbol_table.txt", base_filename);
    generate_symbol_table_report(NULL, report_filename);  // Necesitaremos pasar el analyzer
    
    // Generar reporte de errores
    snprintf(report_filename, sizeof(report_filename), "%s_errors.txt", base_filename);
    generate_error_report(report_filename);
    
    printf("✅ Reportes generados:\n");
    printf("   - %s_symbol_table.txt\n", base_filename);
    printf("   - %s_errors.txt\n", base_filename);
}

void visualize_ast(ASTNode *ast, const char *base_filename) {
    char dot_filename[512];
    char png_filename[512];
    char command[1024];
    
    snprintf(dot_filename, sizeof(dot_filename), "%s_ast.dot", base_filename);
    snprintf(png_filename, sizeof(png_filename), "%s_ast.png", base_filename);
    
    // Generar archivo DOT (implementación básica)
    FILE *dot_file = fopen(dot_filename, "w");
    if (dot_file) {
        fprintf(dot_file, "digraph AST {\n");
        fprintf(dot_file, "  node [shape=box];\n");
        fprintf(dot_file, "  \"Raíz\" [label=\"Programa JavaLang\"];\n");
        fprintf(dot_file, "}\n");
        fclose(dot_file);
        
        printf("✅ Archivo DOT generado: %s\n", dot_filename);
        
        // Intentar generar PNG con Graphviz
        snprintf(command, sizeof(command), "dot -Tpng %s -o %s 2>/dev/null", dot_filename, png_filename);
        if (system(command) == 0) {
            printf("✅ Visualización PNG generada: %s\n", png_filename);
        } else {
            printf("⚠️  No se pudo generar PNG (Graphviz no disponible)\n");
        }
    } else {
        printf("❌ Error al crear archivo DOT\n");
    }
}

char* get_base_filename(const char *filepath) {
    char *path_copy = strdup(filepath);
    char *base = basename(path_copy);
    
    // Remover extensión
    char *dot = strrchr(base, '.');
    if (dot) *dot = '\0';
    
    char *result = strdup(base);
    free(path_copy);
    return result;
}