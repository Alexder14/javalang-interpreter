#!/bin/bash

echo "🚀 COMPILANDO FASE 3: ANALIZADOR SINTÁCTICO"
echo "==========================================="

# Limpiar archivos anteriores
echo "🧹 Limpiando archivos anteriores..."
rm -f test_parser parser/parser.tab.* lexer/lex.yy.c

# Generar parser con Bison
echo "📝 Generando parser con Bison..."
bison -d -o parser/parser.tab.c parser/parser.y

# Generar lexer con Flex
echo "�� Generando lexer con Flex..."
flex -o lexer/lex.yy.c lexer/lexer.l

# Compilar test del parser
echo "🔨 Compilando test_parser..."
gcc -DTEST_PARSER -Wall -std=c99 -g -Iinclude -Iparser -o test_parser \
    parser/parser.tab.c lexer/lex.yy.c src/ast.c src/common.c -lfl 2>/dev/null || \
gcc -DTEST_PARSER -Wall -std=c99 -g -Iinclude -Iparser -o test_parser \
    parser/parser.tab.c lexer/lex.yy.c src/ast.c src/common.c

# Verificar compilación
if [ -f test_parser ]; then
    echo "✅ ¡COMPILACIÓN EXITOSA!"
    echo ""
    echo "🧪 Para probar:"
    echo "   ./test_parser examples/test1.usl"
    echo "   ./test_parser examples/test_completo.usl"
    echo ""
    echo "📊 Estado del proyecto:"
    echo "   ✅ Fase 1: Configuración"
    echo "   ✅ Fase 2: Analizador léxico"
    echo "   ✅ Fase 3: Analizador sintáctico"
    echo "   🚀 Listo para probar parsing completo!"
else
    echo "❌ Error en la compilación"
    echo "Verificando dependencias..."
    which bison || echo "❌ Bison no encontrado"
    which flex || echo "❌ Flex no encontrado"
fi
