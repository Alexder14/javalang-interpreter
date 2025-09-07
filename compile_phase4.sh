#!/bin/bash

echo "🚀 COMPILANDO FASE 4: ANÁLISIS SEMÁNTICO"
echo "========================================"

# Limpiar archivos anteriores
echo "🧹 Limpiando archivos anteriores..."
rm -f javalang_interpreter parser/parser.tab.* lexer/lex.yy.c

# Verificar dependencias
echo "🔍 Verificando dependencias..."
if ! command -v bison &> /dev/null; then
    echo "❌ Bison no encontrado. Instalar con: sudo apt install bison"
    exit 1
fi

if ! command -v flex &> /dev/null; then
    echo "❌ Flex no encontrado. Instalar con: sudo apt install flex"
    exit 1
fi

if ! command -v gcc &> /dev/null; then
    echo "❌ GCC no encontrado. Instalar con: sudo apt install gcc"
    exit 1
fi

echo "✅ Todas las dependencias están disponibles"

# Generar parser con Bison
echo "📝 Generando parser con Bison..."
bison -d -o parser/parser.tab.c parser/parser.y
if [ $? -ne 0 ]; then
    echo "❌ Error al generar parser con Bison"
    exit 1
fi

# Generar lexer con Flex
echo "🔤 Generando lexer con Flex..."
flex -o lexer/lex.yy.c lexer/lexer.l
if [ $? -ne 0 ]; then
    echo "❌ Error al generar lexer con Flex"
    exit 1
fi

# Compilar interpretador principal
echo "🔨 Compilando interpretador JavaLang..."
gcc -Wall -std=c99 -g -Iinclude -Iparser -o javalang_interpreter \
    src/main.c \
    parser/parser.tab.c \
    lexer/lex.yy.c \
    src/ast.c \
    src/semantic.c \
    src/common.c \
    -lfl 2>/dev/null || \
gcc -Wall -std=c99 -g -Iinclude -Iparser -o javalang_interpreter \
    src/main.c \
    parser/parser.tab.c \
    lexer/lex.yy.c \
    src/ast.c \
    src/semantic.c \
    src/common.c

# Verificar compilación
if [ -f javalang_interpreter ]; then
    echo "✅ ¡COMPILACIÓN EXITOSA!"
    echo ""
    echo "🧪 Para probar el análisis semántico:"
    echo "   ./javalang_interpreter examples/test1.usl"
    echo "   ./javalang_interpreter -r examples/test_completo.usl"
    echo "   ./javalang_interpreter --verbose examples/ejemplo_errores.usl"
    echo ""
    echo "📊 Estado del proyecto:"
    echo "   ✅ Fase 1: Configuración"
    echo "   ✅ Fase 2: Analizador léxico"
    echo "   ✅ Fase 3: Analizador sintáctico y AST"
    echo "   ✅ Fase 4: Análisis semántico y tabla de símbolos"
    echo "   🚀 ¡Listo para probar análisis semántico completo!"
    echo ""
    echo "🎯 Funcionalidades de Fase 4:"
    echo "   - Tabla de símbolos completa"
    echo "   - Validaciones semánticas"
    echo "   - Reportes de errores detallados"
    echo "   - Análisis de tipos y ámbitos"
    echo ""
    echo "💡 Opciones disponibles:"
    echo "   -r, --reports     : Generar reportes de tabla de símbolos y errores"
    echo "   -g, --graphviz    : Generar visualización del AST"
    echo "   -V, --visualize   : Visualización completa"
    echo "   --verbose         : Mostrar información detallada"
    echo "   -h, --help        : Mostrar ayuda completa"
else
    echo "❌ Error en la compilación"
    echo ""
    echo "🔧 Posibles soluciones:"
    echo "   1. Verificar que todos los archivos estén presentes"
    echo "   2. Instalar dependencias faltantes:"
    echo "      sudo apt update"
    echo "      sudo apt install flex bison gcc make"
    echo "   3. Verificar permisos de escritura en el directorio"
    echo "   4. Revisar errores específicos arriba"
    exit 1
fi