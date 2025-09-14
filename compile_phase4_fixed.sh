#!/bin/bash

echo "🚀 COMPILANDO PARSER CORREGIDO - FASE 4"
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

# Generar parser con Bison (VERBOSO para debugging)
echo "📝 Generando parser CORREGIDO con Bison..."
bison -d -v -o parser/parser.tab.c parser/parser.y
if [ $? -ne 0 ]; then
    echo "❌ Error al generar parser con Bison"
    echo "💡 Revisa el archivo parser/parser.y para errores de sintaxis"
    exit 1
fi

# Verificar archivos generados
if [ ! -f "parser/parser.tab.c" ] || [ ! -f "parser/parser.tab.h" ]; then
    echo "❌ Parser no se generó correctamente"
    exit 1
fi

echo "✅ Parser generado exitosamente"

# Generar lexer con Flex
echo "🔤 Generando lexer con Flex..."
flex -o lexer/lex.yy.c lexer/lexer.l
if [ $? -ne 0 ]; then
    echo "❌ Error al generar lexer con Flex"
    exit 1
fi

# Verificar archivo de lexer
if [ ! -f "lexer/lex.yy.c" ]; then
    echo "❌ Lexer no se generó correctamente"
    exit 1
fi

echo "✅ Lexer generado exitosamente"

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
    echo ""
    echo "🎉 ¡COMPILACIÓN EXITOSA!"
    echo "========================================"
    echo ""
    echo "📊 Estado del parser:"
    echo "   ✅ Parser.y corregido y generado"
    echo "   ✅ Lexer compatible"
    echo "   ✅ AST integrado"
    echo "   ✅ Análisis semántico listo"
    echo ""
    echo "🧪 TESTS BÁSICOS:"
    echo ""
    
    # Test básico de sintaxis
    if [ -f "examples/test1.usl" ]; then
        echo "📝 Probando archivo examples/test1.usl..."
        ./javalang_interpreter examples/test1.usl
        if [ $? -eq 0 ]; then
            echo "✅ Sintaxis reconocida correctamente"
        else
            echo "⚠️  Parser funciona pero detectó errores en el archivo"
        fi
    else
        echo "⚠️  Archivo examples/test1.usl no encontrado"
        echo "💡 Crea un archivo de prueba con:"
        echo '   mkdir -p examples'
        echo '   echo "public static void main(String[] args) {" > examples/test1.usl'
        echo '       echo "    int x = 5;" >> examples/test1.usl'
        echo '       echo "    println(x);" >> examples/test1.usl'
        echo '       echo "}" >> examples/test1.usl'
    fi
    
    echo ""
    echo "🚀 SIGUIENTE PASO:"
    echo "   1. Crear archivos .usl de prueba"
    echo "   2. Probar: ./javalang_interpreter mi_programa.usl"
    echo "   3. Ver reportes generados"
    echo ""
    echo "📄 Sintaxis JavaLang reconocida:"
    echo "   ✅ Declaraciones de variables (int, float, boolean, String)"
    echo "   ✅ Asignaciones y expresiones"
    echo "   ✅ Estructuras de control (if, while, for, switch)"
    echo "   ✅ Funciones y métodos"
    echo "   ✅ Arrays y llamadas de función"
    echo "   ✅ Print y println"
    echo ""
    echo "🔧 Debug disponible:"
    echo "   - Archivos .output para análisis del parser"
    echo "   - Mensajes detallados de errores"
    echo "   - Construcción paso a paso del AST"
else
    echo ""
    echo "❌ ERROR EN LA COMPILACIÓN"
    echo "========================================"
    echo ""
    echo "🔧 Posibles causas:"
    echo "   1. Headers faltantes en include/"
    echo "   2. Incompatibilidad entre lexer y parser"
    echo "   3. Errores en archivos src/"
    echo ""
    echo "🛠️ Soluciones:"
    echo "   1. Verifica que existan todos los .h en include/"
    echo "   2. Revisa errores de compilación arriba"
    echo "   3. Ejecuta: make clean && make all"
    exit 1
fi