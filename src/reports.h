#include "reports.h"
#include "semantic.h"
#include "ast_visualizer.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Función para obtener timestamp actual
char* get_timestamp() {
    time_t now = time(NULL);
    char* timestamp = malloc(64);
    strftime(timestamp, 64, "%Y-%m-%d %H:%M:%S", localtime(&now));
    return timestamp;
}

// Función para escapar HTML
char* escape_html(const char* str) {
    if (!str) return strdup("");
    
    int len = strlen(str);
    char* escaped = malloc(len * 6 + 1); // Espacio extra para entidades HTML
    int j = 0;
    
    for (int i = 0; i < len; i++) {
        switch (str[i]) {
            case '<':
                strcpy(&escaped[j], "&lt;");
                j += 4;
                break;
            case '>':
                strcpy(&escaped[j], "&gt;");
                j += 4;
                break;
            case '&':
                strcpy(&escaped[j], "&amp;");
                j += 5;
                break;
            case '"':
                strcpy(&escaped[j], "&quot;");
                j += 6;
                break;
            case '\'':
                strcpy(&escaped[j], "&#39;");
                j += 5;
                break;
            default:
                escaped[j++] = str[i];
                break;
        }
    }
    escaped[j] = '\0';
    
    return escaped;
}

// Función para generar reporte en texto plano
void generate_text_report(const char* filename, ReportData* data) {
    char report_file[256];
    snprintf(report_file, sizeof(report_file), "%s_report.txt", filename);
    
    FILE* file = fopen(report_file, "w");
    if (!file) {
        fprintf(stderr, "Error: No se pudo crear el reporte %s\n", report_file);
        return;
    }
    
    char* timestamp = get_timestamp();
    
    // Cabecera del reporte
    fprintf(file, "╔════════════════════════════════════════════════════════════════════════╗\n");
    fprintf(file, "║                      REPORTE COMPILADOR JAVALANG                      ║\n");
    fprintf(file, "╚════════════════════════════════════════════════════════════════════════╝\n\n");
    
    fprintf(file, "📁 Archivo analizado: %s\n", data->source_file);
    fprintf(file, "🕒 Timestamp: %s\n", timestamp);
    fprintf(file, "🔧 Versión: JavaLang Compiler v1.0 - Fase 4\n\n");
    
    // Resumen ejecutivo
    fprintf(file, "═══════════════════════════════════════════════════════════════════════════\n");
    fprintf(file, "📊 RESUMEN EJECUTIVO\n");
    fprintf(file, "═══════════════════════════════════════════════════════════════════════════\n");
    fprintf(file, "✅ Análisis léxico: %s\n", data->lexical_success ? "EXITOSO" : "FALLÓ");
    fprintf(file, "✅ Análisis sintáctico: %s\n", data->syntactic_success ? "EXITOSO" : "FALLÓ");
    fprintf(file, "✅ Análisis semántico: %s\n", data->semantic_success ? "EXITOSO" : "FALLÓ");
    fprintf(file, "📈 Líneas procesadas: %d\n", data->lines_processed);
    fprintf(file, "🔢 Tokens reconocidos: %d\n", data->tokens_count);
    fprintf(file, "📊 Símbolos en tabla: %d\n", data->symbols_count);
    fprintf(file, "❌ Total de errores: %d\n", data->total_errors);
    fprintf(file, "🎯 Función main: %s\n\n", data->has_main ? "ENCONTRADA" : "NO ENCONTRADA");
    
    // Tabla de símbolos
    if (data->symbols_count > 0) {
        fprintf(file, "═══════════════════════════════════════════════════════════════════════════\n");
        fprintf(file, "📋 TABLA DE SÍMBOLOS\n");
        fprintf(file, "═══════════════════════════════════════════════════════════════════════════\n");
        fprintf(file, "%-20s %-15s %-12s %-15s %-6s %-8s\n", 
               "ID", "Tipo Símbolo", "Tipo Dato", "Ámbito", "Línea", "Columna");
        fprintf(file, "────────────────────────────────────────────────────────────────────────────────────────\n");
        
        Symbol *current = symbol_table;
        while (current) {
            fprintf(file, "%-20s %-15s %-12s %-15s %-6d %-8d\n",
                   current->id,
                   symbol_type_to_string(current->symbol_type),
                   data_type_to_string(current->data_type),
                   current->scope,
                   current->line,
                   current->column);
            current = current->next;
        }
        fprintf(file, "\n");
    }
    
    // Errores
    if (data->total_errors > 0) {
        fprintf(file, "═══════════════════════════════════════════════════════════════════════════\n");
        fprintf(file, "❌ ERRORES DETECTADOS\n");
        fprintf(file, "═══════════════════════════════════════════════════════════════════════════\n");
        fprintf(file, "%-3s %-15s %-40s %-15s %-6s %-8s\n", 
               "No.", "Tipo", "Descripción", "Ámbito", "Línea", "Columna");
        fprintf(file, "────────────────────────────────────────────────────────────────────────────────────────\n");
        
        const char* error_types[] = {"LÉXICO", "SINTÁCTICO", "SEMÁNTICO", "RUNTIME"};
        for (int i = 0; i < error_count; i++) {
            fprintf(file, "%-3d %-15s %-40s %-15s %-6d %-8d\n",
                   i + 1,
                   error_types[errors[i].type],
                   errors[i].message,
                   errors[i].scope,
                   errors[i].line,
                   errors[i].column);
        }
        fprintf(file, "\n");
    }
    
    // Pie del reporte
    fprintf(file, "═══════════════════════════════════════════════════════════════════════════\n");
    fprintf(file, "🏁 FIN DEL REPORTE\n");
    fprintf(file, "═══════════════════════════════════════════════════════════════════════════\n");
    fprintf(file, "Generado por JavaLang Compiler - Proyecto Educativo\n");
    fprintf(file, "Organización de Lenguajes y Compiladores 2\n");
    
    fclose(file);
    free(timestamp);
    
    printf("📄 Reporte de texto generado: %s\n", report_file);
}

// Función para generar reporte en HTML
void generate_html_report(const char* filename, ReportData* data) {
    char report_file[256];
    snprintf(report_file, sizeof(report_file), "%s_report.html", filename);
    
    FILE* file = fopen(report_file, "w");
    if (!file) {
        fprintf(stderr, "Error: No se pudo crear el reporte %s\n", report_file);
        return;
    }
    
    char* timestamp = get_timestamp();
    char* escaped_filename = escape_html(data->source_file);
    
    // Escribir HTML
    fprintf(file, "<!DOCTYPE html>\n");
    fprintf(file, "<html lang=\"es\">\n");
    fprintf(file, "<head>\n");
    fprintf(file, "    <meta charset=\"UTF-8\">\n");
    fprintf(file, "    <meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">\n");
    fprintf(file, "    <title>Reporte JavaLang - %s</title>\n", escaped_filename);
    fprintf(file, "    <style>\n");
    fprintf(file, "        body { font-family: 'Segoe UI', Tahoma, Geneva, Verdana, sans-serif; margin: 20px; background-color: #f5f5f5; }\n");
    fprintf(file, "        .container { max-width: 1200px; margin: 0 auto; background: white; padding: 20px; border-radius: 8px; box-shadow: 0 2px 10px rgba(0,0,0,0.1); }\n");
    fprintf(file, "        .header { text-align: center; border-bottom: 3px solid #007acc; padding-bottom: 20px; margin-bottom: 30px; }\n");
    fprintf(file, "        .header h1 { color: #007acc; margin: 0; font-size: 2.5em; }\n");
    fprintf(file, "        .header p { color: #666; margin: 10px 0; }\n");
    fprintf(file, "        .summary { display: grid; grid-template-columns: repeat(auto-fit, minmax(250px, 1fr)); gap: 20px; margin-bottom: 30px; }\n");
    fprintf(file, "        .summary-card { background: linear-gradient(135deg, #667eea 0%%, #764ba2 100%%); color: white; padding: 20px; border-radius: 8px; text-align: center; }\n");
    fprintf(file, "        .summary-card h3 { margin: 0 0 10px 0; font-size: 1.2em; }\n");
    fprintf(file, "        .summary-card p { margin: 0; font-size: 1.8em; font-weight: bold; }\n");
    fprintf(file, "        .success { background: linear-gradient(135deg, #4facfe 0%%, #00f2fe 100%%) !important; }\n");
    fprintf(file, "        .error { background: linear-gradient(135deg, #ff6b6b 0%%, #ee5a24 100%%) !important; }\n");
    fprintf(file, "        .warning { background: linear-gradient(135deg, #feca57 0%%, #ff9ff3 100%%) !important; }\n");
    fprintf(file, "        .section { margin-bottom: 40px; }\n");
    fprintf(file, "        .section h2 { color: #333; border-bottom: 2px solid #eee; padding-bottom: 10px; }\n");
    fprintf(file, "        table { width: 100%%; border-collapse: collapse; margin-top: 20px; }\n");
    fprintf(file, "        th, td { padding: 12px; text-align: left; border-bottom: 1px solid #ddd; }\n");
    fprintf(file, "        th { background-color: #f8f9fa; font-weight: 600; color: #333; }\n");
    fprintf(file, "        tr:hover { background-color: #f5f5f5; }\n");
    fprintf(file, "        .status-ok { color: #28a745; font-weight: bold; }\n");
    fprintf(file, "        .status-error { color: #dc3545; font-weight: bold; }\n");
    fprintf(file, "        .footer { text-align: center; margin-top: 40px; padding-top: 20px; border-top: 1px solid #eee; color: #666; }\n");
    fprintf(file, "        .badge { display: inline-block; padding: 4px 8px; border-radius: 4px; font-size: 0.8em; font-weight: bold; }\n");
    fprintf(file, "        .badge-success { background-color: #d4edda; color: #155724; }\n");
    fprintf(file, "        .badge-error { background-color: #f8d7da; color: #721c24; }\n");
    fprintf(file, "        .badge-warning { background-color: #fff3cd; color: #856404; }\n");
    fprintf(file, "    </style>\n");
    fprintf(file, "</head>\n");
    fprintf(file, "<body>\n");
    fprintf(file, "    <div class=\"container\">\n");
    
    // Cabecera
    fprintf(file, "        <div class=\"header\">\n");
    fprintf(file, "            <h1>🚀 Reporte JavaLang Compiler</h1>\n");
    fprintf(file, "            <p><strong>Archivo:</strong> %s</p>\n", escaped_filename);
    fprintf(file, "            <p><strong>Generado:</strong> %s</p>\n", timestamp);
    fprintf(file, "            <p><strong>Versión:</strong> JavaLang Compiler v1.0 - Fase 4</p>\n");
    fprintf(file, "        </div>\n");
    
    // Resumen ejecutivo
    fprintf(file, "        <div class=\"section\">\n");
    fprintf(file, "            <h2>📊 Resumen Ejecutivo</h2>\n");
    fprintf(file, "            <div class=\"summary\">\n");
    
    // Cards de resumen
    fprintf(file, "                <div class=\"summary-card %s\">\n", 
           data->lexical_success ? "success" : "error");
    fprintf(file, "                    <h3>Análisis Léxico</h3>\n");
    fprintf(file, "                    <p>%s</p>\n", data->lexical_success ? "✅ EXITOSO" : "❌ FALLÓ");
    fprintf(file, "                </div>\n");
    
    fprintf(file, "                <div class=\"summary-card %s\">\n", 
           data->syntactic_success ? "success" : "error");
    fprintf(file, "                    <h3>Análisis Sintáctico</h3>\n");
    fprintf(file, "                    <p>%s</p>\n", data->syntactic_success ? "✅ EXITOSO" : "❌ FALLÓ");
    fprintf(file, "                </div>\n");
    
    fprintf(file, "                <div class=\"summary-card %s\">\n", 
           data->semantic_success ? "success" : "error");
    fprintf(file, "                    <h3>Análisis Semántico</h3>\n");
    fprintf(file, "                    <p>%s</p>\n", data->semantic_success ? "✅ EXITOSO" : "❌ FALLÓ");
    fprintf(file, "                </div>\n");
    
    fprintf(file, "                <div class=\"summary-card\">\n");
    fprintf(file, "                    <h3>Líneas Procesadas</h3>\n");
    fprintf(file, "                    <p>%d</p>\n", data->lines_processed);
    fprintf(file, "                </div>\n");
    
    fprintf(file, "                <div class=\"summary-card\">\n");
    fprintf(file, "                    <h3>Tokens Reconocidos</h3>\n");
    fprintf(file, "                    <p>%d</p>\n", data->tokens_count);
    fprintf(file, "                </div>\n");
    
    fprintf(file, "                <div class=\"summary-card %s\">\n", 
           data->total_errors == 0 ? "success" : "error");
    fprintf(file, "                    <h3>Total Errores</h3>\n");
    fprintf(file, "                    <p>%d</p>\n", data->total_errors);
    fprintf(file, "                </div>\n");
    
    fprintf(file, "            </div>\n");
    fprintf(file, "        </div>\n");
    
    // Tabla de símbolos
    if (data->symbols_count > 0) {
        fprintf(file, "        <div class=\"section\">\n");
        fprintf(file, "            <h2>📋 Tabla de Símbolos</h2>\n");
        fprintf(file, "            <table>\n");
        fprintf(file, "                <thead>\n");
        fprintf(file, "                    <tr>\n");
        fprintf(file, "                        <th>ID</th>\n");
        fprintf(file, "                        <th>Tipo Símbolo</th>\n");
        fprintf(file, "                        <th>Tipo Dato</th>\n");
        fprintf(file, "                        <th>Ámbito</th>\n");
        fprintf(file, "                        <th>Línea</th>\n");
        fprintf(file, "                        <th>Columna</th>\n");
        fprintf(file, "                    </tr>\n");
        fprintf(file, "                </thead>\n");
        fprintf(file, "                <tbody>\n");
        
        Symbol *current = symbol_table;
        while (current) {
            char* escaped_id = escape_html(current->id);
            char* escaped_scope = escape_html(current->scope);
            
            fprintf(file, "                    <tr>\n");
            fprintf(file, "                        <td><strong>%s</strong></td>\n", escaped_id);
            fprintf(file, "                        <td><span class=\"badge badge-success\">%s</span></td>\n", 
                   symbol_type_to_string(current->symbol_type));
            fprintf(file, "                        <td>%s</td>\n", data_type_to_string(current->data_type));
            fprintf(file, "                        <td>%s</td>\n", escaped_scope);
            fprintf(file, "                        <td>%d</td>\n", current->line);
            fprintf(file, "                        <td>%d</td>\n", current->column);
            fprintf(file, "                    </tr>\n");
            
            free(escaped_id);
            free(escaped_scope);
            current = current->next;
        }
        
        fprintf(file, "                </tbody>\n");
        fprintf(file, "            </table>\n");
        fprintf(file, "        </div>\n");
    }
    
    // Errores
    if (data->total_errors > 0) {
        fprintf(file, "        <div class=\"section\">\n");
        fprintf(file, "            <h2>❌ Errores Detectados</h2>\n");
        fprintf(file, "            <table>\n");
        fprintf(file, "                <thead>\n");
        fprintf(file, "                    <tr>\n");
        fprintf(file, "                        <th>No.</th>\n");
        fprintf(file, "                        <th>Tipo</th>\n");
        fprintf(file, "                        <th>Descripción</th>\n");
        fprintf(file, "                        <th>Ámbito</th>\n");
        fprintf(file, "                        <th>Línea</th>\n");
        fprintf(file, "                        <th>Columna</th>\n");
        fprintf(file, "                    </tr>\n");
        fprintf(file, "                </thead>\n");
        fprintf(file, "                <tbody>\n");
        
        const char* error_types[] = {"LÉXICO", "SINTÁCTICO", "SEMÁNTICO", "RUNTIME"};
        const char* error_badges[] = {"badge-warning", "badge-error", "badge-error", "badge-error"};
        
        for (int i = 0; i < error_count; i++) {
            char* escaped_message = escape_html(errors[i].message);
            char* escaped_scope = escape_html(errors[i].scope);
            
            fprintf(file, "                    <tr>\n");
            fprintf(file, "                        <td>%d</td>\n", i + 1);
            fprintf(file, "                        <td><span class=\"badge %s\">%s</span></td>\n", 
                   error_badges[errors[i].type], error_types[errors[i].type]);
            fprintf(file, "                        <td>%s</td>\n", escaped_message);
            fprintf(file, "                        <td>%s</td>\n", escaped_scope);
            fprintf(file, "                        <td>%d</td>\n", errors[i].line);
            fprintf(file, "                        <td>%d</td>\n", errors[i].column);
            fprintf(file, "                    </tr>\n");
            
            free(escaped_message);
            free(escaped_scope);
        }
        
        fprintf(file, "                </tbody>\n");
        fprintf(file, "            </table>\n");
        fprintf(file, "        </div>\n");
    }
    
    // Pie
    fprintf(file, "        <div class=\"footer\">\n");
    fprintf(file, "            <p>Generado por <strong>JavaLang Compiler</strong> - Proyecto Educativo</p>\n");
    fprintf(file, "            <p>Organización de Lenguajes y Compiladores 2</p>\n");
    fprintf(file, "        </div>\n");
    fprintf(file, "    </div>\n");
    fprintf(file, "</body>\n");
    fprintf(file, "</html>\n");
    
    fclose(file);
    free(timestamp);
    free(escaped_filename);
    
    printf("🌐 Reporte HTML generado: %s\n", report_file);
}

// Función para generar reporte en JSON
void generate_json_report(const char* filename, ReportData* data) {
    char report_file[256];
    snprintf(report_file, sizeof(report_file), "%s_report.json", filename);
    
    FILE* file = fopen(report_file, "w");
    if (!file) {
        fprintf(stderr, "Error: No se pudo crear el reporte %s\n", report_file);
        return;
    }
    
    char* timestamp = get_timestamp();
    
    fprintf(file, "{\n");
    fprintf(file, "  \"javalang_report\": {\n");
    fprintf(file, "    \"metadata\": {\n");
    fprintf(file, "      \"source_file\": \"%s\",\n", data->source_file);
    fprintf(file, "      \"timestamp\": \"%s\",\n", timestamp);
    fprintf(file, "      \"compiler_version\": \"JavaLang Compiler v1.0 - Fase 4\"\n");
    fprintf(file, "    },\n");
    fprintf(file, "    \"analysis_results\": {\n");
    fprintf(file, "      \"lexical_analysis\": %s,\n", data->lexical_success ? "true" : "false");
    fprintf(file, "      \"syntactic_analysis\": %s,\n", data->syntactic_success ? "true" : "false");
    fprintf(file, "      \"semantic_analysis\": %s,\n", data->semantic_success ? "true" : "false");
    fprintf(file, "      \"has_main_function\": %s\n", data->has_main ? "true" : "false");
    fprintf(file, "    },\n");
    fprintf(file, "    \"statistics\": {\n");
    fprintf(file, "      \"lines_processed\": %d,\n", data->lines_processed);
    fprintf(file, "      \"tokens_count\": %d,\n", data->tokens_count);
    fprintf(file, "      \"symbols_count\": %d,\n", data->symbols_count);
    fprintf(file, "      \"total_errors\": %d\n", data->total_errors);
    fprintf(file, "    },\n");
    
    // Tabla de símbolos
    fprintf(file, "    \"symbol_table\": [\n");
    Symbol *current = symbol_table;
    bool first_symbol = true;
    while (current) {
        if (!first_symbol) fprintf(file, ",\n");
        fprintf(file, "      {\n");
        fprintf(file, "        \"id\": \"%s\",\n", current->id);
        fprintf(file, "        \"symbol_type\": \"%s\",\n", symbol_type_to_string(current->symbol_type));
        fprintf(file, "        \"data_type\": \"%s\",\n", data_type_to_string(current->data_type));
        fprintf(file, "        \"scope\": \"%s\",\n", current->scope);
        fprintf(file, "        \"line\": %d,\n", current->line);
        fprintf(file, "        \"column\": %d\n", current->column);
        fprintf(file, "      }");
        first_symbol = false;
        current = current->next;
    }
    fprintf(file, "\n    ],\n");
    
    // Errores
    fprintf(file, "    \"errors\": [\n");
    const char* error_types[] = {"lexical", "syntactic", "semantic", "runtime"};
    for (int i = 0; i < error_count; i++) {
        if (i > 0) fprintf(file, ",\n");
        fprintf(file, "      {\n");
        fprintf(file, "        \"id\": %d,\n", i + 1);
        fprintf(file, "        \"type\": \"%s\",\n", error_types[errors[i].type]);
        fprintf(file, "        \"description\": \"%s\",\n", errors[i].message);
        fprintf(file, "        \"scope\": \"%s\",\n", errors[i].scope);
        fprintf(file, "        \"line\": %d,\n", errors[i].line);
        fprintf(file, "        \"column\": %d\n", errors[i].column);
        fprintf(file, "      }");
    }
    fprintf(file, "\n    ]\n");
    
    fprintf(file, "  }\n");
    fprintf(file, "}\n");
    
    fclose(file);
    free(timestamp);
    
    printf("📋 Reporte JSON generado: %s\n", report_file);
}

// Función principal para generar reportes completos
void generate_complete_reports(const char* filename, ASTNode* ast_root) {
    printf("\n📊 Generando reportes completos...\n");
    printf("═══════════════════════════════════════════════════════════════════════════\n");
    
    // Preparar datos del reporte
    ReportData data = {0};
    data.source_file = filename;
    data.lexical_success = true; // Asumimos que llegamos hasta aquí
    data.syntactic_success = (ast_root != NULL);
    data.semantic_success = (semantic_error_count == 0);
    data.lines_processed = line_num;
    data.tokens_count = token_count;
    data.has_main = has_main_function;
    data.total_errors = error_count;
    
    // Contar símbolos
    Symbol *current = symbol_table;
    while (current) {
        data.symbols_count++;
        current = current->next;
    }
    
    // Extraer nombre base del archivo
    char base_name[256];
    const char* last_slash = strrchr(filename, '/');
    const char* base_start = last_slash ? last_slash + 1 : filename;
    strncpy(base_name, base_start, sizeof(base_name) - 1);
    base_name[sizeof(base_name) - 1] = '\0';
    
    // Remover extensión
    char* dot = strrchr(base_name, '.');
    if (dot) *dot = '\0';
    
    // Generar reportes en diferentes formatos
    generate_text_report(base_name, &data);
    generate_html_report(base_name, &data);
    generate_json_report(base_name, &data);
    
    // Generar visualización del AST si está disponible
    if (ast_root) {
        visualize_ast(ast_root, base_name);
    }
    
    printf("═══════════════════════════════════════════════════════════════════════════\n");
    printf("✅ Reportes generados exitosamente\n");
    printf("📁 Archivos creados:\n");
    printf("   • %s_report.txt (Texto plano)\n", base_name);
    printf("   • %s_report.html (HTML interactivo)\n", base_name);
    printf("   • %s_report.json (Datos estructurados)\n", base_name);
    if (ast_root) {
        printf("   • %s.dot (Graphviz AST)\n", base_name);
        printf("   • %s.png (Imagen AST - si Graphviz está instalado)\n", base_name);
    }
    printf("\n");
}