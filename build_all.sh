#!/bin/bash

echo "🚀 COMPILANDO PROYECTO JAVALANG COMPLETO"
echo "========================================"

# Limpiar archivos anteriores
echo "🧹 Limpiando archivos anteriores..."
rm -f javalang_interpreter test_lexer lexer/lex.yy.c

# Compilar interpretador principal
echo "🔨 Compilando interpretador principal..."
gcc -Wall -std=c99 -g -Iinclude -o javalang_interpreter src/main.c src/common.c

# Compilar analizador léxico
echo "🔍 Compilando analizador léxico..."
flex -o lexer/lex.yy.c lexer/lexer.l
gcc -DTEST_LEXER -Wall -std=c99 -g -Iinclude -o test_lexer lexer/lex.yy.c src/common.c -lfl 2>/dev/null || \
gcc -DTEST_LEXER -Wall -std=c99 -g -Iinclude -o test_lexer lexer/lex.yy.c src/common.c

# Verificar compilación
if [ -f javalang_interpreter ] && [ -f test_lexer ]; then
    echo "✅ ¡COMPILACIÓN EXITOSA!"
    echo ""
    echo "🧪 Para probar:"
    echo "   ./javalang_interpreter examples/test1.usl"
    echo "   ./test_lexer examples/test_completo.usl"
    echo ""
    echo "📊 Estado del proyecto:"
    echo "   ✅ Fase 1: Configuración"
    echo "   ✅ Fase 2: Analizador léxico"
    echo "   🚀 Listo para Fase 3: Analizador sintáctico"
else
    echo "❌ Error en la compilación"
    exit 1
fi
