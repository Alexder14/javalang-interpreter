#include "../include/javalang_gui.h"

int main(int argc, char *argv[]) {
    gtk_init(&argc, &argv);
    
    printf("🚀 Iniciando JavaLang GUI Advanced...\n");
    
    JavaLangApp *app = javalang_app_new();
    if (!app) {
        fprintf(stderr, "❌ Error: No se pudo crear la aplicación GUI\n");
        return 1;
    }
    
    javalang_app_run(app);
    gtk_main();
    javalang_app_destroy(app);
    
    return 0;
}
