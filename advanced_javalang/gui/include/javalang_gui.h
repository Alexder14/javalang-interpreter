#ifndef JAVALANG_GUI_H
#define JAVALANG_GUI_H

#include <gtk/gtk.h>
#include <gtksourceview/gtksource.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct {
    GtkWidget *window;
    GtkWidget *main_box;
    GtkWidget *menu_bar;
    GtkWidget *toolbar;
    GtkWidget *paned_main;
    GtkWidget *paned_bottom;
    
    // Editor
    GtkWidget *editor_frame;
    GtkWidget *source_view;
    GtkTextBuffer *source_buffer;
    
    // Consola
    GtkWidget *console_frame;
    GtkWidget *console_view;
    GtkTextBuffer *console_buffer;
    GtkTextMark *console_end_mark;
    
    // Reportes
    GtkWidget *notebook_reports;
    GtkWidget *ast_textview;
    GtkWidget *symbols_textview;
    GtkWidget *errors_textview;
    
    // Estado
    char *current_filename;
    gboolean file_modified;
    int compilation_status;
    
} JavaLangApp;

JavaLangApp* javalang_app_new(void);
void javalang_app_run(JavaLangApp *app);
void javalang_app_destroy(JavaLangApp *app);

void on_new_file(GtkWidget *widget, gpointer data);
void on_open_file(GtkWidget *widget, gpointer data);
void on_save_file(GtkWidget *widget, gpointer data);
void on_compile_code(GtkWidget *widget, gpointer data);
void on_about(GtkWidget *widget, gpointer data);
void on_quit(GtkWidget *widget, gpointer data);

void add_to_console(JavaLangApp *app, const char *text);
void clear_console(JavaLangApp *app);
void set_source_code(JavaLangApp *app, const char *code);
char* get_source_code(JavaLangApp *app);
void update_window_title(JavaLangApp *app);

#endif
