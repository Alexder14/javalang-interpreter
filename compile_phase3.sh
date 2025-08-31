#!/bin/bash

echo "🚀 COMPILANDO FASE 3: ANALIZADOR SINTÁCTICO (VERSIÓN CORREGIDA)"
echo "============================================================="

# Colores para output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[0;33m'
BLUE='\033[0;34m'
NC='\033[0m'

print_step() { echo -e "${BLUE}$1${NC}"; }
print_success() { echo -e "${GREEN}✅ $1${NC}"; }
print_error() { echo -e "${RED}❌ $1${NC}"; }
print_warning() { echo -e "${YELLOW}⚠️  $1${NC}"; }

# Verificar que estamos en el directorio correcto
if [ ! -d "include" ] || [ ! -d "src" ]; then
    print_error "No se encuentran los directorios include/ y src/"
    echo "Ejecuta este script desde la raíz del proyecto"
    exit 1
fi

# Limpiar archivos anteriores
print_step "🧹 Limpiando archivos anteriores..."
rm -f test_parser parser/parser.tab.* lexer/lex.yy.c *.o

# Verificar que los archivos necesarios existen
print_step "📋 Verificando archivos necesarios..."

required_files=(
    "include/common.h"
    "src/common.c"
    "include/ast.h" 
    "src/ast.c"
)

missing_files=()
for file in "${required_files[@]}"; do
    if [ ! -f "$file" ]; then
        missing_files+=("$file")
    fi
done

if [ ${#missing_files[@]} -ne 0 ]; then
    print_error "Faltan los siguientes archivos:"
    for file in "${missing_files[@]}"; do
        echo "  - $file"
    done
    print_warning "Usa los archivos que creé en los artifacts"
    exit 1
fi

print_success "Todos los archivos necesarios están presentes"

# Paso 1: Generar parser con Bison (esto crea parser.tab.h)
print_step "📝 Paso 1: Generando parser con Bison..."
if bison -d -v -o parser/parser.tab.c parser/parser.y 2>bison.log; then
    print_success "Parser generado correctamente"
    
    # Verificar si hay warnings de shift/reduce
    if grep -q "shift/reduce" bison.log; then
        conflicts=$(grep -o "[0-9]* shift/reduce" bison.log)
        print_warning "Advertencia: $conflicts conflictos (esto es normal)"
    fi
else
    print_error "Error al generar parser con Bison"
    echo "Detalles del error:"
    cat bison.log
    exit 1
fi

# Verificar que se creó el archivo de cabecera
if [ ! -f "parser/parser.tab.h" ]; then
    print_error "No se generó parser.tab.h"
    exit 1
fi

print_success "Archivos generados: parser.tab.c y parser.tab.h"

# Paso 2: Generar lexer con Flex (ahora puede incluir parser.tab.h)
print_step "🔤 Paso 2: Generando lexer con Flex..."
if flex -o lexer/lex.yy.c lexer/lexer.l 2>flex.log; then
    print_success "Lexer generado correctamente"
else
    print_error "Error al generar lexer con Flex"
    echo "Detalles del error:"
    cat flex.log
    exit 1
fi

# Paso 3: Compilar test_parser
print_step "🔨 Paso 3: Compilando test_parser..."

# Comando de compilación con todos los include paths necesarios
gcc_cmd="gcc -DTEST_PARSER -Wall -std=c99 -g"
gcc_cmd+=" -Iinclude -Iparser -Ilexer"
gcc_cmd+=" -o test_parser"
gcc_cmd+=" parser/parser.tab.c lexer/lex.yy.c src/ast.c src/common.c"

print_step "Comando de compilación:"
echo "$gcc_cmd"

# Intentar compilar con libfl primero
if $gcc_cmd -lfl 2>gcc.log; then
    print_success "Compilación exitosa (con libfl)"
elif $gcc_cmd 2>gcc.log; then
    print_success "Compilación exitosa (sin libfl)"
else
    print_error "Error en la compilación"
    echo "Detalles del error:"
    cat gcc.log
    echo ""
    print_step "Errores más comunes y soluciones:"
    echo "1. Si falta 'parser.tab.h': Verifica que Bison se ejecutó correctamente"
    echo "2. Si hay errores de sintaxis: Revisa parser.y y lexer.l"
    echo "3. Si faltan funciones: Verifica que ast.c esté completo"
    echo "4. Si hay conflictos de tipos: Revisa las definiciones en los .h"
    exit 1
fi

# Verificar que el ejecutable se creó
if [ ! -f "test_parser" ]; then
    print_error "El ejecutable test_parser no fue creado"
    exit 1
fi

# Limpiar archivos temporales
rm -f bison.log flex.log gcc.log

print_success "¡COMPILACIÓN EXITOSA!"
echo ""
echo "📊 Archivos generados:"
echo "  ✅ parser/parser.tab.c    (parser de Bison)"
echo "  ✅ parser/parser.tab.h    (definiciones de tokens)"
echo "  ✅ lexer/lex.yy.c         (lexer de Flex)"
echo "  ✅ test_parser            (ejecutable de prueba)"
echo ""

# Crear archivos de ejemplo básicos si no existen
if [ ! -d "examples" ]; then
    mkdir -p examples
fi

if [ ! -f "examples/test_basico.usl" ]; then
    print_step "📝 Creando archivo de ejemplo básico..."
    
    cat > examples/test_basico.usl << 'EOF'
public static void main() {
    int x = 10;
    println("Hola mundo");
}
EOF
    
    print_success "Archivo de ejemplo creado: examples/test_basico.usl"
fi

# Hacer una prueba básica
print_step "🧪 Realizando prueba básica..."
echo "Archivo de prueba:"
echo "----------------------------------------"
cat examples/test_basico.usl
echo "----------------------------------------"
echo ""

if ./test_parser examples/test_basico.usl; then
    print_success "¡Prueba básica exitosa!"
    echo ""
    print_success "FASE 3 COMPILADA CORRECTAMENTE"
    echo ""
    echo "🎯 Para probar:"
    echo "   ./test_parser examples/test_basico.usl"
    echo ""
    echo "📊 Estado del proyecto:"
    echo "   ✅ Fase 1: Configuración"
    echo "   ✅ Fase 2: Analizador léxico"
    echo "   ✅ Fase 3: Analizador sintáctico"
    echo "   🚀 Listo para Fase 4: Análisis semántico"
else
    print_error "La prueba básica falló"
    echo "Revisa los archivos parser.y, lexer.l, ast.c y common.c"
    echo ""
    echo "Para debug, puedes:"
    echo "1. Verificar errores de sintaxis en el archivo .usl"
    echo "2. Compilar con -DDEBUG_LEXER para ver tokens"
    echo "3. Revisar que todas las funciones del AST estén implementadas"
    exit 1
fi