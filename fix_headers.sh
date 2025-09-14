#!/bin/bash

echo "🔧 ARREGLANDO HEADERS Y DEPENDENCIAS"
echo "===================================="

# Agregar #define _GNU_SOURCE a common.h para strdup
if [ -f "include/common.h" ]; then
    if ! grep -q "_GNU_SOURCE" include/common.h; then
        echo "🔧 Agregando _GNU_SOURCE a common.h..."
        sed -i '1i#define _GNU_SOURCE' include/common.h
    fi
    
    if ! grep -q "#include <string.h>" include/common.h; then
        echo "🔧 Agregando #include <string.h> a common.h..."
        sed -i '2i#include <string.h>' include/common.h
    fi
fi

# Agregar includes necesarios a ast.c
if [ -f "src/ast.c" ]; then
    if ! grep -q "_GNU_SOURCE" src/ast.c; then
        echo "🔧 Agregando _GNU_SOURCE a ast.c..."
        sed -i '1i#define _GNU_SOURCE' src/ast.c
    fi
    
    if ! grep -q "#include <string.h>" src/ast.c; then
        echo "🔧 Agregando #include <string.h> a ast.c..."
        sed -i '2i#include <string.h>' src/ast.c
    fi
fi

# Agregar includes necesarios a semantic.c
if [ -f "src/semantic.c" ]; then
    if ! grep -q "_GNU_SOURCE" src/semantic.c; then
        echo "🔧 Agregando _GNU_SOURCE a semantic.c..."
        sed -i '1i#define _GNU_SOURCE' src/semantic.c
    fi
    
    if ! grep -q "#include <string.h>" src/semantic.c; then
        echo "🔧 Agregando #include <string.h> a semantic.c..."
        sed -i '2i#include <string.h>' src/semantic.c
    fi
fi

# Verificar que el lexer devuelve tokens simbólicos
if [ -f "lexer/lexer.l" ]; then
    if grep -q "return [0-9]" lexer/lexer.l; then
        echo "⚠️  ADVERTENCIA: lexer.l devuelve números en lugar de tokens simbólicos"
        echo "   Esto causará errores de compilación con el nuevo parser"
        echo "   💡 Reemplaza 'return 123;' con 'return PUBLIC;' etc."
    else
        echo "✅ Lexer devuelve tokens simbólicos correctamente"
    fi
fi

echo "✅ Headers arreglados"