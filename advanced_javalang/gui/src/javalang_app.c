#include "../include/javalang_gui.h"

static void create_menu(JavaLangApp *app);
static void create_toolbar(JavaLangApp *app);
static void create_main_area(JavaLangApp *app);
static void create_editor(JavaLangApp *app);
static void create_console(JavaLangApp *app);
static void create_reports_area(JavaLangApp *app);

JavaLangApp* javalang_app_new(void) {
    JavaLangApp *app = g_malloc0(sizeof(JavaLangApp));
    if (!app) return NULL;
    
    app->current_filename = NULL;
    app->file_modified = FALSE;
    app->compilation_status = 0;
    
    return app;
}

void javalang_app_run(JavaLangApp *app) {
    // Ventana principal
    app->window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(app->window), "JavaLang Advanced - GUI");
    gtk_window_set_default_size(GTK_WINDOW(app->window), 1200, 800);
    gtk_window_set_position(GTK_WINDOW(app->window), GTK_WIN_POS_CENTER);
    
    g_signal_connect(app->window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
    
    // Contenedor principal
    app->main_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_container_add(GTK_CONTAINER(app->window), app->main_box);
    
    create_menu(app);
    create_toolbar(app);
    create_main_area(app);
    
    gtk_widget_show_all(app->window);
    
    // Mensaje de bienvenida
    add_to_console(app, "JavaLang Advanced Interpreter - GUI Edition");
    add_to_console(app, "Universidad San Carlos de Guatemala");
    add_to_console(app, "Fase 5: Interfaz Gráfica Completada");
    add_to_console(app, "Listo para usar...");
    
    update_window_title(app);
}

static void create_menu(JavaLangApp *app) {
    app->menu_bar = gtk_menu_bar_new();
    
    // Menú Archivo
    GtkWidget *file_menu = gtk_menu_new();
    GtkWidget *file_item = gtk_menu_item_new_with_label("Archivo");
    gtk_menu_item_set_submenu(GTK_MENU_ITEM(file_item), file_menu);
    
    GtkWidget *new_item = gtk_menu_item_new_with_label("Nuevo");
    GtkWidget *open_item = gtk_menu_item_new_with_label("Abrir");
    GtkWidget *save_item = gtk_menu_item_new_with_label("Guardar");
    GtkWidget *quit_item = gtk_menu_item_new_with_label("Salir");
    
    gtk_menu_shell_append(GTK_MENU_SHELL(file_menu), new_item);
    gtk_menu_shell_append(GTK_MENU_SHELL(file_menu), open_item);
    gtk_menu_shell_append(GTK_MENU_SHELL(file_menu), save_item);
    gtk_menu_shell_append(GTK_MENU_SHELL(file_menu), gtk_separator_menu_item_new());
    gtk_menu_shell_append(GTK_MENU_SHELL(file_menu), quit_item);
    
    g_signal_connect(new_item, "activate", G_CALLBACK(on_new_file), app);
    g_signal_connect(open_item, "activate", G_CALLBACK(on_open_file), app);
    g_signal_connect(save_item, "activate", G_CALLBACK(on_save_file), app);
    g_signal_connect(quit_item, "activate", G_CALLBACK(on_quit), app);
    
    // Menú Compilar
    GtkWidget *compile_menu = gtk_menu_new();
    GtkWidget *compile_item = gtk_menu_item_new_with_label("Compilar");
    gtk_menu_item_set_submenu(GTK_MENU_ITEM(compile_item), compile_menu);
    
    GtkWidget *analyze_item = gtk_menu_item_new_with_label("Analizar código");
    gtk_menu_shell_append(GTK_MENU_SHELL(compile_menu), analyze_item);
    g_signal_connect(analyze_item, "activate", G_CALLBACK(on_compile_code), app);
    
    // Menú Ayuda
    GtkWidget *help_menu = gtk_menu_new();
    GtkWidget *help_item = gtk_menu_item_new_with_label("Ayuda");
    gtk_menu_item_set_submenu(GTK_MENU_ITEM(help_item), help_menu);
    
    GtkWidget *about_item = gtk_menu_item_new_with_label("Acerca de");
    gtk_menu_shell_append(GTK_MENU_SHELL(help_menu), about_item);
    g_signal_connect(about_item, "activate", G_CALLBACK(on_about), app);
    
    gtk_menu_shell_append(GTK_MENU_SHELL(app->menu_bar), file_item);
    gtk_menu_shell_append(GTK_MENU_SHELL(app->menu_bar), compile_item);
    gtk_menu_shell_append(GTK_MENU_SHELL(app->menu_bar), help_item);
    
    gtk_box_pack_start(GTK_BOX(app->main_box), app->menu_bar, FALSE, FALSE, 0);
}

static void create_toolbar(JavaLangApp *app) {
    app->toolbar = gtk_toolbar_new();
    
    GtkToolItem *new_btn = gtk_tool_button_new(NULL, "Nuevo");
    GtkToolItem *open_btn = gtk_tool_button_new(NULL, "Abrir");
    GtkToolItem *save_btn = gtk_tool_button_new(NULL, "Guardar");
    GtkToolItem *sep1 = gtk_separator_tool_item_new();
    GtkToolItem *compile_btn = gtk_tool_button_new(NULL, "Analizar");
    
    g_signal_connect(new_btn, "clicked", G_CALLBACK(on_new_file), app);
    g_signal_connect(open_btn, "clicked", G_CALLBACK(on_open_file), app);
    g_signal_connect(save_btn, "clicked", G_CALLBACK(on_save_file), app);
    g_signal_connect(compile_btn, "clicked", G_CALLBACK(on_compile_code), app);
    
    gtk_toolbar_insert(GTK_TOOLBAR(app->toolbar), new_btn, -1);
    gtk_toolbar_insert(GTK_TOOLBAR(app->toolbar), open_btn, -1);
    gtk_toolbar_insert(GTK_TOOLBAR(app->toolbar), save_btn, -1);
    gtk_toolbar_insert(GTK_TOOLBAR(app->toolbar), sep1, -1);
    gtk_toolbar_insert(GTK_TOOLBAR(app->toolbar), compile_btn, -1);
    
    gtk_box_pack_start(GTK_BOX(app->main_box), app->toolbar, FALSE, FALSE, 0);
}

static void create_main_area(JavaLangApp *app) {
    // Panel principal horizontal
    app->paned_main = gtk_paned_new(GTK_ORIENTATION_HORIZONTAL);
    
    create_editor(app);
    gtk_paned_pack1(GTK_PANED(app->paned_main), app->editor_frame, TRUE, TRUE);
    
    create_reports_area(app);
    gtk_paned_pack2(GTK_PANED(app->paned_main), app->notebook_reports, FALSE, TRUE);
    
    // Panel vertical
    app->paned_bottom = gtk_paned_new(GTK_ORIENTATION_VERTICAL);
    gtk_paned_pack1(GTK_PANED(app->paned_bottom), app->paned_main, TRUE, TRUE);
    
    create_console(app);
    gtk_paned_pack2(GTK_PANED(app->paned_bottom), app->console_frame, FALSE, TRUE);
    
    gtk_box_pack_start(GTK_BOX(app->main_box), app->paned_bottom, TRUE, TRUE, 0);
    
    // Configurar tamaños
    gtk_paned_set_position(GTK_PANED(app->paned_main), 800);
    gtk_paned_set_position(GTK_PANED(app->paned_bottom), 500);
}

static void create_editor(JavaLangApp *app) {
    app->editor_frame = gtk_frame_new("Editor de Código");
    
    GtkWidget *scrolled = gtk_scrolled_window_new(NULL, NULL);
    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scrolled),
                                   GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
    
    app->source_view = gtk_source_view_new();
    app->source_buffer = GTK_TEXT_BUFFER(gtk_text_view_get_buffer(GTK_TEXT_VIEW(app->source_view)));
    
    gtk_source_view_set_show_line_numbers(GTK_SOURCE_VIEW(app->source_view), TRUE);
    gtk_source_view_set_highlight_current_line(GTK_SOURCE_VIEW(app->source_view), TRUE);
    gtk_text_view_set_wrap_mode(GTK_TEXT_VIEW(app->source_view), GTK_WRAP_WORD);
    
    const char *initial_code = 
        "public class Test {\n"
        "    public static void main() {\n"
        "        int x = 5;\n"
        "        System.out.println(\"Hola JavaLang Advanced!\");\n"
        "    }\n"
        "}";
    
    gtk_text_buffer_set_text(app->source_buffer, initial_code, -1);
    
    gtk_container_add(GTK_CONTAINER(scrolled), app->source_view);
    gtk_container_add(GTK_CONTAINER(app->editor_frame), scrolled);
}

static void create_console(JavaLangApp *app) {
    app->console_frame = gtk_frame_new("Consola de Salida");
    
    GtkWidget *console_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 2);
    
    GtkWidget *console_buttons = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
    GtkWidget *clear_btn = gtk_button_new_with_label("Limpiar");
    GtkWidget *analyze_btn = gtk_button_new_with_label("Analizar");
    
    g_signal_connect_swapped(clear_btn, "clicked", G_CALLBACK(clear_console), app);
    g_signal_connect(analyze_btn, "clicked", G_CALLBACK(on_compile_code), app);
    
    gtk_box_pack_start(GTK_BOX(console_buttons), clear_btn, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(console_buttons), analyze_btn, FALSE, FALSE, 0);
    
    GtkWidget *scrolled = gtk_scrolled_window_new(NULL, NULL);
    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scrolled),
                                   GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
    
    app->console_view = gtk_text_view_new();
    app->console_buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(app->console_view));
    
    gtk_text_view_set_editable(GTK_TEXT_VIEW(app->console_view), FALSE);
    gtk_text_view_set_wrap_mode(GTK_TEXT_VIEW(app->console_view), GTK_WRAP_WORD);
    
    // Fuente monoespaciada
    PangoFontDescription *font_desc = pango_font_description_from_string("Courier New 10");
    gtk_widget_override_font(app->console_view, font_desc);
    pango_font_description_free(font_desc);
    
    // Colores
    GdkRGBA bg_color, fg_color;
    gdk_rgba_parse(&bg_color, "#1e1e1e");
    gdk_rgba_parse(&fg_color, "#00ff00");
    gtk_widget_override_background_color(app->console_view, GTK_STATE_FLAG_NORMAL, &bg_color);
    gtk_widget_override_color(app->console_view, GTK_STATE_FLAG_NORMAL, &fg_color);
    
    GtkTextIter end_iter;
    gtk_text_buffer_get_end_iter(app->console_buffer, &end_iter);
    app->console_end_mark = gtk_text_buffer_create_mark(app->console_buffer, "end", &end_iter, FALSE);
    
    gtk_container_add(GTK_CONTAINER(scrolled), app->console_view);
    
    gtk_box_pack_start(GTK_BOX(console_box), console_buttons, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(console_box), scrolled, TRUE, TRUE, 0);
    
    gtk_container_add(GTK_CONTAINER(app->console_frame), console_box);
}

static void create_reports_area(JavaLangApp *app) {
    app->notebook_reports = gtk_notebook_new();
    
    // AST
    GtkWidget *ast_scrolled = gtk_scrolled_window_new(NULL, NULL);
    app->ast_textview = gtk_text_view_new();
    gtk_text_view_set_editable(GTK_TEXT_VIEW(app->ast_textview), FALSE);
    gtk_container_add(GTK_CONTAINER(ast_scrolled), app->ast_textview);
    gtk_notebook_append_page(GTK_NOTEBOOK(app->notebook_reports), ast_scrolled, gtk_label_new("AST"));
    
    // Símbolos
    GtkWidget *symbols_scrolled = gtk_scrolled_window_new(NULL, NULL);
    app->symbols_textview = gtk_text_view_new();
    gtk_text_view_set_editable(GTK_TEXT_VIEW(app->symbols_textview), FALSE);
    gtk_container_add(GTK_CONTAINER(symbols_scrolled), app->symbols_textview);
    gtk_notebook_append_page(GTK_NOTEBOOK(app->notebook_reports), symbols_scrolled, gtk_label_new("Símbolos"));
    
    // Errores
    GtkWidget *errors_scrolled = gtk_scrolled_window_new(NULL, NULL);
    app->errors_textview = gtk_text_view_new();
    gtk_text_view_set_editable(GTK_TEXT_VIEW(app->errors_textview), FALSE);
    gtk_container_add(GTK_CONTAINER(errors_scrolled), app->errors_textview);
    gtk_notebook_append_page(GTK_NOTEBOOK(app->notebook_reports), errors_scrolled, gtk_label_new("Errores"));
}

void javalang_app_destroy(JavaLangApp *app) {
    if (app->current_filename) {
        g_free(app->current_filename);
    }
    g_free(app);
}
