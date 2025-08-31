#!/bin/bash

echo "🔍 DIAGNÓSTICO DE COMPILACIÓN - FASE 3"
echo "====================================="

# Colores
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[0;33m'
BLUE='\033[0;34m'
NC='\033[0m'

print_check() { echo -e "${BLUE}🔍 $1${NC}"; }
print_ok() { echo -e "${GREEN}✅ $1${NC}"; }
print_error() { echo -e "${RED}❌ $1${NC}"; }
print_warning() { echo -e "${YELLOW}⚠️  $1${NC}"; }

echo ""
print_check "1. Verificando estructura de directorios..."

required_dirs=("include" "src" "parser" "lexer" "examples")
for dir in "${required_dirs[@]}"; do
    if [ -d "$dir" ]; then
        print_ok "Directorio $dir existe"
    else
        print_error "Falta directorio $dir"
        echo "   Solución: mkdir -p $dir"
    fi
done

echo ""
print_check "2. Verificando archivos de cabecera..."

if [ -f "include/common.h" ]; then
    print_ok "include/common.h existe"
    if grep -q "typedef enum" include/common.h; then
        print_ok "common.h contiene definiciones de tipos"
    else
        print_warning "common.h parece estar incompleto"
    fi
else
    print_error "Falta include/common.h"
fi

if [ -f "include/ast.h" ]; then
    print_ok "include/ast.h existe"
    if grep -q "typedef struct ASTNode" include/ast.h; then
        print_ok "ast.h contiene definición de ASTNode"
    else
        print_warning "ast.h parece estar incompleto"
    fi
else
    print_error "Falta include/ast.h"
fi

echo ""
print_check "3. Verificando archivos de implementación..."

if [ -f "src/common.c" ]; then
    print_ok "src/common.c existe"
    if grep -q "line_num" src/common.c; then
        print_ok "common.c define variables globales"
    else
        print_warning "common.c parece estar incompleto"
    fi
else
    print_error "Falta src/common.c"
fi

if [ -f "src/ast.c" ]; then
    print_ok "src/ast.c existe"
    if grep -q "create_node" src/ast.c; then
        print_ok "ast.c contiene funciones de creación de nodos"
    else
        print_warning "ast.c parece estar incompleto"
    fi
else
    print_error "Falta src/ast.c"
fi

echo ""
print_check "4. Verificando lexer..."

if [ -f "lexer/lexer.l" ]; then
    print_ok "lexer/lexer.l existe"
    if grep -q "PUBLIC" lexer/lexer.l; then
        print_ok "lexer.l tiene tokens simbólicos (compatible con parser)"
    else
        print_warning "lexer.l devuelve números, no tokens simbólicos"
        echo "   Esto causará errores de compilación con el parser de Bison"
        echo "   Solución: Usa el lexer.l actualizado de los artifacts"
    fi
else
    print_error "Falta lexer/lexer.l"
fi

echo ""
print_check "5. Verificando parser..."

if [ -f "parser/parser.y" ]; then
    print_ok "parser/parser.y existe"
    if grep -q "%token.*PUBLIC" parser/parser.y; then
        print_ok "parser.y define tokens simbólicos"
    else
        print_warning "parser.y no define tokens correctamente"
    fi
    
    if grep -q "%type.*program" parser/parser.y; then
        print_ok "parser.y define tipos de nodos"
    else
        print_warning "parser.y no define tipos de nodos"
    fi
else
    print_error "Falta parser/parser.y"
fi

echo ""
print_check "6. Verificando herramientas del sistema..."

tools=("gcc" "flex" "bison")
all_tools_present=true

for tool in "${tools[@]}"; do
    if command -v $tool &> /dev/null; then
        version=$($tool --version | head -n1)
        print_ok "$tool instalado ($version)"
    else
        print_error "$tool no está instalado"
        all_tools_present=false
    fi
done

if [ "$all_tools_present" = false ]; then
    echo ""
    echo "Instala las herramientas faltantes con:"
    echo "sudo apt-get update && sudo apt-get install gcc flex bison"
fi

echo ""
print_check "7. Intentando compilación de prueba..."

# Limpiar archivos anteriores
rm -f parser/parser.tab.* lexer/lex.yy.c test_parser 2>/dev/null

# Generar parser
if bison -d -o parser/parser.tab.c parser/parser.y 2>bison_errors.log; then
    print_ok "Parser generado con Bison"
    if [ -s bison_errors.log ]; then
        print_warning "Advertencias de Bison:"
        cat bison_errors.log | head -5
    fi
else
    print_error "Error al generar parser con Bison"
    echo "Errores de Bison:"
    cat bison_errors.log
    rm -f bison_errors.log
    echo ""
    echo "DIAGNÓSTICO: Problema en parser/parser.y"
    echo "Solución: Reemplaza parser.y con el archivo de los artifacts"
    exit 1
fi

# Generar lexer
if flex -o lexer/lex.yy.c lexer/lexer.l 2>flex_errors.log; then
    print_ok "Lexer generado con Flex"
    if [ -s flex_errors.log ]; then
        print_warning "Advertencias de Flex:"
        cat flex_errors.log
    fi
else
    print_error "Error al generar lexer con Flex"
    echo "Errores de Flex:"
    cat flex_errors.log
    rm -f flex_errors.log
    echo ""
    echo "DIAGNÓSTICO: Problema en lexer/lexer.l"
    echo "Solución: Reemplaza lexer.l con el archivo de los artifacts"
    exit 1
fi

# Compilar
print_check "Compilando con gcc..."
gcc_cmd="gcc -DTEST_PARSER -Wall -std=c99 -g -Iinclude -Iparser -o test_parser parser/parser.tab.c lexer/lex.yy.c src/ast.c src/common.c"

if $gcc_cmd -lfl 2>gcc_errors.log; then
    print_ok "Compilación exitosa (con libfl)"
elif $gcc_cmd 2>gcc_errors.log; then
    print_ok "Compilación exitosa (sin libfl)"
else
    print_error "Error de compilación con gcc"
    echo ""
    echo "ERRORES DETALLADOS:"
    echo "=================="
    cat gcc_errors.log
    echo ""
    
    echo "DIAGNÓSTICO AUTOMÁTICO:"
    echo "====================="
    
    if grep -q "undefined reference" gcc_errors.log; then
        print_error "Error: Referencias indefinidas"
        echo "Esto indica que faltan implementaciones de funciones."
        echo ""
        echo "Soluciones:"
        echo "1. Verifica que src/ast.c esté completo"
        echo "2. Verifica que src/common.c esté completo"
        echo "3. Asegúrate de que todas las funciones declaradas estén implementadas"
    fi
    
    if grep -q "syntax error\|parse error" gcc_errors.log; then
        print_error "Error: Errores de sintaxis en código C"
        echo "Hay problemas de sintaxis en los archivos .c o .h"
        echo ""
        echo "Soluciones:"
        echo "1. Revisa los archivos de cabecera (.h) para declaraciones correctas"
        echo "2. Verifica que no falten ; o } en los archivos .c"
        echo "3. Asegúrate de que los tipos estén bien definidos"
    fi
    
    if grep -q "conflicting types\|redefinition" gcc_errors.log; then
        print_error "Error: Conflictos de definiciones"
        echo "Hay definiciones duplicadas o conflictivas"
        echo ""
        echo "Soluciones:"
        echo "1. Verifica que los .h tengan guards (#ifndef/#define/#endif)"
        echo "2. Asegúrate de que no haya definiciones duplicadas"
        echo "3. Revisa que los tipos en .h coincidan con las implementaciones en .c"
    fi
    
    rm -f gcc_errors.log
    exit 1
fi

# Limpiar archivos temporales
rm -f bison_errors.log flex_errors.log gcc_errors.log

echo ""
print_ok "DIAGNÓSTICO COMPLETO - TODO FUNCIONA CORRECTAMENTE"
echo ""
echo "🎉 El proyecto está listo para la Fase 3!"
echo "Ejecuta: ./test_parser examples/archivo.usl"