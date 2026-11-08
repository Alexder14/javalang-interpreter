
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#include "ast.h"
#include "semantic.h"
#include "common.h"
#include "interpreter.h"
#include "ast_dot.h"
#include <sys/wait.h>

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
int render_dot(const char *dot_file, const char *png_file);
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
        // Pasar los errores semánticos (en orden de detección) al sistema de reportes
        int n = 0;
        SemanticError *list[1024];
        for (SemanticError *e = analyzer->errors; e && n < 1024; e = e->next) list[n++] = e;
        for (int i = n - 1; i >= 0; i--) {
            char msg[512];
            snprintf(msg, sizeof(msg), "%s%s%s", list[i]->message,
                     list[i]->context[0] ? ": " : "", list[i]->context);
            add_error(ERROR_SEMANTIC, msg, list[i]->scope, list[i]->line, list[i]->column);
        }
        print_errors();
    } else {
        printf("✅ Análisis semántico completado sin errores\n");
        
        // Fase 5: Ejecución del programa
        printf("\n▶️  Ejecutando código\n");
        printf("═══════════════════════════════════════════════════════════\n");
        fflush(stdout);
        int run_rc = interpret_program(ast_root, stdout);
        printf("═══════════════════════════════════════════════════════════\n");
        if (run_rc != 0) {
            printf("❌ Error en tiempo de ejecución\n");
            print_errors();
        } else {
            printf("✅ Ejecución finalizada\n");
        }
    }
    
    // Generar reportes
    printf("\n📊 Generando reportes...\n");
    generate_complete_reports(filename);
    
    // Mostrar resumen final
    print_compilation_summary();
    
    // Limpiar memoria
    interpreter_reset();
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
    
    // Reporte del AST: grafo Graphviz (.dot + .png) y árbol de texto (.txt)
    char dot_filename[512], png_filename[512], ast_filename[512];
    snprintf(dot_filename, sizeof(dot_filename), "%s_ast.dot", base);
    snprintf(png_filename, sizeof(png_filename), "%s_ast.png", base);
    snprintf(ast_filename, sizeof(ast_filename), "%s_ast.txt", base);
    
    FILE *ast_file = fopen(ast_filename, "w");
    if (ast_file) {
        fprintf(ast_file, "ÁRBOL DE SINTAXIS ABSTRACTA (AST)\n");
        fprintf(ast_file, "==================================\n\n");
        if (ast_root) print_ast_file(ast_root, ast_file);
        else fprintf(ast_file, "No se pudo generar el AST.\n");
        fclose(ast_file);
        printf("📄 Reporte AST (texto) generado: %s\n", ast_filename);
    }
    
    FILE *dot_file = fopen(dot_filename, "w");
    if (dot_file) {
        ast_write_dot(ast_root, dot_file);
        fclose(dot_file);
        printf("📄 Reporte AST (grafo) generado: %s\n", dot_filename);
        if (render_dot(dot_filename, png_filename) == 0)
            printf("🖼️  Imagen del AST generada: %s\n", png_filename);
        else
            printf("ℹ️  Para dibujar el grafo instale Graphviz (sudo apt install graphviz) y ejecute: dot -Tpng %s -o %s\n",
                   dot_filename, png_filename);
    }
    
    // Reporte de tabla de símbolos con valores (solo si el programa se ejecutó)
    if (interpreter_symbol_count() > 0) {
        char sym_filename[512];
        snprintf(sym_filename, sizeof(sym_filename), "%s_symbols.txt", base);
        FILE *sym_file = fopen(sym_filename, "w");
        if (sym_file) {
            interpreter_write_symbol_table(sym_file);
            fclose(sym_file);
            printf("📄 Reporte de tabla de símbolos generado: %s\n", sym_filename);
        }
    }
    
    free(base);
}

// Ejecuta `dot -Tpng entrada -o salida` sin pasar por el shell. Devuelve 0 si tuvo éxito.
int render_dot(const char *dot_file, const char *png_file) {
    pid_t pid = fork();
    if (pid < 0) return -1;
    if (pid == 0) {
        freopen("/dev/null", "w", stderr);
        execlp("dot", "dot", "-Tpng", dot_file, "-o", png_file, (char *)NULL);
        _exit(127);
    }
    int status = 0;
    if (waitpid(pid, &status, 0) < 0) return -1;
    return (WIFEXITED(status) && WEXITSTATUS(status) == 0) ? 0 : -1;
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