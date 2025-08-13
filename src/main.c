#include "common.h"

int main(int argc, char **argv) {
    printf("JavaLang Interpreter v1.0\n");
    printf("Universidad San Carlos de Guatemala\n");
    printf("Organización de Lenguajes y Compiladores 2\n\n");
    
    if (argc < 2) {
        printf("Uso: %s archivo.usl\n", argv[0]);
        return 1;
    }
    
    printf("Archivo a procesar: %s\n", argv[1]);
    printf("Estado: Configuración completada ✅\n");
    printf("Próximo paso: Implementar analizador léxico\n");
    
    return 0;
}
