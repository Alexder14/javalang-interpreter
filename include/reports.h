#ifndef REPORTS_H
#define REPORTS_H

#include "ast.h"
#include "common.h"
#include <stdbool.h>

// Estructura para datos del reporte
typedef struct {
    const char* source_file;
    bool lexical_success;
    bool syntactic_success;
    bool semantic_success;
    int lines_processed;
    int tokens_count;
    int symbols_count;
    int total_errors;
    bool has_main;
} ReportData;

// Funciones principales de reportes
void generate_complete_reports(const char* filename, ASTNode* ast_root);
void generate_text_report(const char* filename, ReportData* data);
void generate_html_report(const char* filename, ReportData* data);
void generate_json_report(const char* filename, ReportData* data);

// Funciones auxiliares
char* get_timestamp();
char* escape_html(const char* str);

// Variables externas necesarias
extern int token_count;

#endif