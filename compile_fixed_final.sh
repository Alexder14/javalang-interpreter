#!/bin/bash

echo "🚀 COMPILACIÓN FINAL - PARSER CORREGIDO FASE 4"
echo "==============================================="

# Hacer ejecutables los scripts de ayuda
chmod +x fix_headers.sh 2>/dev/null

# Paso 1: Arreglar headers
echo "📝 Paso 1: Arreglando headers..."
if [ -f "fix_headers.sh" ]; then
    ./fix_headers.sh
else
    echo "🔧 Arreglando headers manualmente..."
    
    # Agregar define _GNU_SOURCE a archivos principales
    for file in "src/ast.c" "src/semantic.c" "src/common.c"; do
        if [ -f "$file" ] && ! head -1 "$file" | grep -q "_GNU_SOURCE"; then
            sed -i '1i#define _GNU_SOURCE' "$file"
        fi
    done
    
    echo "✅ Headers básicos arreglados"
fi

# Paso 2: Limpiar archivos anteriores
echo ""
echo "🧹 Paso 2: Limpiando archivos anteriores..."
rm -f javalang_interpreter parser/parser.tab.* lexer/lex.yy.c parser/*.output

# Paso 3: Verificar dependencias
echo ""
echo "🔍 Paso 3: Verificando dependencias..."
missing_deps=()

if ! command -v bison &> /dev/null; then
    missing_deps+="bison"
fi

if ! command -v flex &> /dev/null; then
    missing_deps+="flex"
fi

if ! command -v gcc &> /dev/null; then
    missing_deps+="gcc"
fi

if [ ${#missing_deps[@]} -ne 0 ]; then
    echo "❌ Faltan dependencias: ${missing_deps[*]}"
    echo "💡 Ejecuta: sudo apt install ${missing_deps[*]}"
    exit 1
fi

echo "✅ Todas las dependencias disponibles"

# Paso 4: Generar parser con Bison
echo ""
echo "📝 Paso 4: Generando parser corregido..."
bison -d -v -o parser/parser.tab.c parser/parser.y
if [ $? -ne 0 ]; then
    echo "❌ Error al generar parser"
    echo ""
    echo "🔧 POSIBLES SOLUCIONES:"
    echo "1. Reemplaza parser/parser.y con el parser corregido del artifact"
    echo "2. Verifica que todos los %type estén correctamente definidos"
    echo "3. Revisa si falta algún %token en la definición"
    exit 1
fi

if [ ! -f "parser/parser.tab.c" ] || [ ! -f "parser/parser.tab.h" ]; then
    echo "❌ Archivos de parser no se generaron correctamente"
    exit 1
fi

echo "✅ Parser generado exitosamente"

# Paso 5: Generar lexer
echo ""
echo "🔤 Paso 5: Generando lexer..."
flex -o lexer/lex.yy.c lexer/lexer.l
if [ $? -ne 0 ]; then
    echo "❌ Error al generar lexer"
    exit 1
fi

if [ ! -f "lexer/lex.yy.c" ]; then
    echo "❌ Archivo de lexer no se generó"
    exit 1
fi

echo "✅ Lexer generado exitosamente"

# Paso 6: Compilar con flags optimizados
echo ""
echo "🔨 Paso 6: Compilando interpretador..."

# Flags de compilación mejorados
CFLAGS="-Wall -std=c99 -g -D_GNU_SOURCE -Wno-unused-function -Wno-unused-variable"
INCLUDES="-Iinclude -Iparser"
SOURCES="src/main.c parser/parser.tab.c lexer/lex.yy.c src/ast.c src/semantic.c src/common.c"

# Intentar compilación con libfl
echo "🔧 Intentando compilación con libfl..."
gcc $CFLAGS $INCLUDES -o javalang_interpreter $SOURCES -lfl 2>compilation_errors.log

# Si falla, intentar sin libfl
if [ $? -ne 0 ]; then
    echo "🔧 Intentando sin libfl..."
    gcc $CFLAGS $INCLUDES -o javalang_interpreter $SOURCES 2>>compilation_errors.log
fi

# Verificar resultado final
if [ -f javalang_interpreter ]; then
    echo ""
    echo "🎉 ¡COMPILACIÓN EXITOSA!"
    echo "========================================"
    echo ""
    echo "📊 ESTADO DEL PROYECTO:"
    echo "   ✅ Fase 1: Configuración"
    echo "   ✅ Fase 2: Analizador léxico" 
    echo "   ✅ Fase 3: Analizador sintáctico"
    echo "   ✅ Fase 4: AST y análisis semántico"
    echo ""
    echo "🧪 PRUEBAS DISPONIBLES:"
    
    # Crear archivo de prueba básico si no existe
    if [ ! -f "examples/test_basic.usl" ]; then
        mkdir -p examples
        cat > examples/test_basic.usl << 'EOF'
public static void main(String[] args) {
    int x = 5;
    int y = 10;
    int suma = x + y;
    println(suma);
}
EOF
        echo "📝 Creado examples/test_basic.usl"
    fi
    
    echo ""
    echo "🚀 COMANDOS PARA PROBAR:"
    echo "   ./javalang_interpreter examples/test_basic.usl"
    
    if [ -f "examples/test1.usl" ]; then
        echo "   ./javalang_interpreter examples/test1.usl"
    fi
    
    echo ""
    echo "📋 REPORTES GENERADOS:"
    echo "   - Tokens reconocidos"
    echo "   - AST construido"
    echo "   - Tabla de símbolos"
    echo "   - Errores detectados (si los hay)"
    echo ""
    echo "💡 SIGUIENTE FASE: GUI con GTK3"
    
    # Mostrar warnings si los hay
    if [ -s compilation_errors.log ]; then
        echo ""
        echo "⚠️  WARNINGS (no críticos):"
        head -10 compilation_errors.log | grep "warning:" | head -5
        echo "   (Ver compilation_errors.log para detalles completos)"
    fi
    
else
    echo ""
    echo "❌ ERROR EN LA COMPILACIÓN"
    echo "========================================"
    echo ""
    echo "🔧 ERRORES ENCONTRADOS:"
    if [ -s compilation_errors.log ]; then
        head -20 compilation_errors.log
    else
        echo "   No se pudo determinar la causa del error"
    fi
    echo ""
    echo "🛠️  POSIBLES SOLUCIONES:"
    echo "1. Verifica que parser/parser.y sea el corregido"
    echo "2. Revisa que existan todos los .h en include/"
    echo "3. Ejecuta: make clean && make all"
    echo "4. Verifica la salida completa en compilation_errors.log"
    exit 1
fi

# Limpiar archivo temporal si no hay errores críticos
if [ ! -s compilation_errors.log ]; then
    rm -f compilation_errors.log
fi