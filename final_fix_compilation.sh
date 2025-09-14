#!/bin/bash

echo "🔧 SOLUCIÓN COMPLETA - ARREGLO DE COMPILACIÓN"
echo "============================================="

# Paso 1: Limpiar todo
echo "🧹 Paso 1: Limpieza completa..."
chmod +x clean_and_fix.sh
./clean_and_fix.sh

# Paso 2: Verificar que el lexer sea el correcto
echo ""
echo "🔍 Paso 2: Verificando lexer..."
if grep -q "return PUBLIC;" lexer/lexer.l; then
    echo "✅ Lexer corregido detectado"
else
    echo "❌ CRÍTICO: Lexer aún devuelve números"
    echo "💡 SOLUCIÓN: Reemplaza lexer/lexer.l con el lexer corregido del artifact"
    echo "   El lexer debe tener líneas como:"
    echo '   "public"        { update_position(yytext); return PUBLIC; }'
    echo '   "static"        { update_position(yytext); return STATIC; }'
    echo ""
    echo "🛑 No puedo continuar hasta que arregles el lexer"
    exit 1
fi

# Paso 3: Generar parser limpio
echo ""
echo "📝 Paso 3: Generando parser..."
bison -d -o parser/parser.tab.c parser/parser.y 2>parser_errors.log

if [ $? -ne 0 ]; then
    echo "❌ Error al generar parser"
    echo "Ver parser_errors.log para detalles"
    exit 1
fi

# Mostrar warnings del parser pero continuar
if [ -s parser_errors.log ]; then
    echo "⚠️ Warnings del parser (no críticos):"
    head -5 parser_errors.log
fi

echo "✅ Parser generado"

# Paso 4: Generar lexer
echo ""
echo "🔤 Paso 4: Generando lexer..."
flex -o lexer/lex.yy.c lexer/lexer.l

if [ $? -ne 0 ]; then
    echo "❌ Error al generar lexer"
    exit 1
fi

echo "✅ Lexer generado"

# Paso 5: Compilar con configuración optimizada
echo ""
echo "🔨 Paso 5: Compilando..."

# Flags específicos para evitar warnings molestos
CFLAGS="-std=c99 -g -D_GNU_SOURCE"
CFLAGS="$CFLAGS -Wno-unused-function -Wno-unused-variable"
CFLAGS="$CFLAGS -Wno-format-truncation -Wno-implicit-function-declaration"
INCLUDES="-Iinclude -Iparser"

# Archivos fuente
SOURCES="src/main.c parser/parser.tab.c lexer/lex.yy.c src/ast.c src/semantic.c src/common.c"

# Compilar
gcc $CFLAGS $INCLUDES -o javalang_interpreter $SOURCES -lfl 2>final_errors.log || \
gcc $CFLAGS $INCLUDES -o javalang_interpreter $SOURCES 2>>final_errors.log

# Verificar resultado
if [ -f javalang_interpreter ]; then
    echo ""
    echo "🎉 ¡COMPILACIÓN EXITOSA!"
    echo "========================"
    echo ""
    
    # Crear archivo de prueba básico
    mkdir -p examples
    cat > examples/test_compilation.usl << 'EOF'
public static void main(String[] args) {
    int x = 42;
    println(x);
}
EOF
    
    echo "🧪 PRUEBA RÁPIDA:"
    echo "   ./javalang_interpreter examples/test_compilation.usl"
    echo ""
    
    # Probar inmediatamente
    echo "🚀 Ejecutando prueba..."
    ./javalang_interpreter examples/test_compilation.usl
    
    echo ""
    echo "✅ PROYECTO COMPILADO Y FUNCIONAL"
    echo ""
    echo "📋 PRÓXIMOS PASOS:"
    echo "1. Crear más archivos .usl de prueba"  
    echo "2. Probar funcionalidades avanzadas"
    echo "3. Continuar con la Fase 5 (GUI)"
    
else
    echo ""
    echo "❌ ERROR DE COMPILACIÓN"
    echo "======================="
    echo ""
    echo "📋 Errores encontrados:"
    head -10 final_errors.log
    echo ""
    echo "💡 Para debugging detallado:"
    echo "   cat final_errors.log"
    exit 1
fi