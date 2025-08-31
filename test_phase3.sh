#!/bin/bash

echo "🚀 FASE 3: COMPILACIÓN Y PRUEBAS DEL ANALIZADOR SINTÁCTICO"
echo "========================================================="

# Colores para output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[0;33m'
BLUE='\033[0;34m'
MAGENTA='\033[0;35m'
CYAN='\033[0;36m'
NC='\033[0m' # No Color

# Función para imprimir con colores
print_step() {
    echo -e "${CYAN}$1${NC}"
}

print_success() {
    echo -e "${GREEN}✅ $1${NC}"
}

print_error() {
    echo -e "${RED}❌ $1${NC}"
}

print_info() {
    echo -e "${BLUE}ℹ️  $1${NC}"
}

# Verificar dependencias
print_step "🔧 Verificando dependencias..."
missing_tools=()

if ! command -v gcc &> /dev/null; then
    missing_tools+=("gcc")
fi

if ! command -v flex &> /dev/null; then
    missing_tools+=("flex")
fi

if ! command -v bison &> /dev/null; then
    missing_tools+=("bison")
fi

if [ ${#missing_tools[@]} -ne 0 ]; then
    print_error "Faltan las siguientes herramientas: ${missing_tools[*]}"
    echo "Instala con: sudo apt-get install gcc flex bison"
    exit 1
fi

print_success "Todas las dependencias están instaladas"

# Crear directorios necesarios
print_step "📁 Creando directorios necesarios..."
mkdir -p examples parser include src lexer

# Limpiar archivos anteriores
print_step "🧹 Limpiando archivos anteriores..."
rm -f test_parser parser/parser.tab.* lexer/lex.yy.c

# Generar parser con Bison
print_step "📝 Generando parser con Bison..."
if bison -d -o parser/parser.tab.c parser/parser.y; then
    print_success "Parser generado correctamente"
else
    print_error "Error al generar parser con Bison"
    exit 1
fi

# Generar lexer con Flex (asumiendo que ya existe)
if [ -f "lexer/lexer.l" ]; then
    print_step "🔤 Generando lexer con Flex..."
    if flex -o lexer/lex.yy.c lexer/lexer.l; then
        print_success "Lexer generado correctamente"
    else
        print_error "Error al generar lexer con Flex"
        exit 1
    fi
else
    print_info "No se encontró lexer/lexer.l, asumiendo que ya existe lex.yy.c"
fi

# Compilar test del parser
print_step "🔨 Compilando test_parser..."
gcc_command="gcc -DTEST_PARSER -Wall -std=c99 -g -Iinclude -Iparser -o test_parser parser/parser.tab.c lexer/lex.yy.c src/ast.c src/common.c"

# Intentar compilar con -lfl primero, si falla sin -lfl
if $gcc_command -lfl 2>/dev/null || $gcc_command 2>/dev/null; then
    print_success "test_parser compilado correctamente"
else
    print_error "Error en la compilación"
    exit 1
fi

# Verificar que el ejecutable existe
if [ ! -f "test_parser" ]; then
    print_error "El ejecutable test_parser no fue creado"
    exit 1
fi

# Crear archivos de ejemplo si no existen
if [ ! -f "examples/test1.usl" ]; then
    print_step "📝 Creando archivos de ejemplo..."
    
    cat > examples/test1.usl << 'EOF'
// Ejemplo básico de JavaLang
public static void main() {
    int numero = 10;
    float decimal = 3.14;
    boolean activo = true;
    String mensaje = "Hola JavaLang";
    
    println("El número es: " + numero);
    println(mensaje);
}
EOF

    cat > examples/test_completo.usl << 'EOF'
// Ejemplo completo de JavaLang
public static void main() {
    int edad = 25;
    String nombre = "Juan";
    
    if (edad >= 18) {
        println("Es mayor de edad");
    } else {
        println("Es menor de edad");
    }
    
    for (int i = 0; i < 3; i = i + 1) {
        println("Iteración: " + i);
    }
    
    int[] numeros = {1, 2, 3};
    println("Primer número: " + numeros[0]);
}
EOF

    print_success "Archivos de ejemplo creados"
fi

# Ejecutar pruebas
echo ""
print_step "🧪 EJECUTANDO PRUEBAS"
echo "====================="

test_files=("examples/test1.usl" "examples/test_completo.usl")
passed_tests=0
total_tests=0

for test_file in "${test_files[@]}"; do
    if [ -f "$test_file" ]; then
        total_tests=$((total_tests + 1))
        echo ""
        print_info "Probando: $test_file"
        echo "----------------------------------------"
        
        if ./test_parser "$test_file"; then
            passed_tests=$((passed_tests + 1))
            print_success "Prueba exitosa: $test_file"
        else
            print_error "Prueba falló: $test_file"
        fi
        
        echo "----------------------------------------"
    fi
done

# Mostrar resumen
echo ""
print_step "📊 RESUMEN DE RESULTADOS"
echo "========================"

echo "Pruebas pasadas: $passed_tests/$total_tests"

if [ $passed_tests -eq $total_tests ]; then
    print_success "¡Todas las pruebas pasaron!"
    echo ""
    print_success "FASE 3 COMPLETADA EXITOSAMENTE"
    echo ""
    echo "📋 Estado del proyecto:"
    echo "   ✅ Fase 1: Configuración"
    echo "   ✅ Fase 2: Analizador léxico" 
    echo "   ✅ Fase 3: Analizador sintáctico"
    echo "   🚀 Listo para Fase 4: Análisis semántico"
    echo ""
    echo "🎯 Próximos pasos:"
    echo "   - Implementar tabla de símbolos"
    echo "   - Agregar validaciones semánticas"
    echo "   - Crear interpretador/ejecutor"
    echo "   - Desarrollar GUI con GTK3"
else
    print_error "Algunas pruebas fallaron"
    echo "Revisa los errores anteriores y corrige antes de continuar"
fi

# Información adicional
echo ""
print_info "Para probar manualmente:"
echo "  ./test_parser examples/test1.usl"
echo "  ./test_parser examples/test_completo.usl"
echo ""
print_info "Archivos generados:"
echo "  - test_parser (ejecutable de prueba)"
echo "  - parser/parser.tab.c (parser generado por Bison)"
echo "  - parser/parser.tab.h (cabeceras del parser)"
echo "  - lexer/lex.yy.c (lexer generado por Flex)"

exit 0