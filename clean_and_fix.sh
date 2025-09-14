#!/bin/bash

echo "🧹 LIMPIEZA Y ARREGLO COMPLETO"
echo "============================="

# Función para limpiar _GNU_SOURCE malformado
clean_gnu_source() {
    local file="$1"
    if [ -f "$file" ]; then
        # Eliminar líneas con _GNU_SOURCE malformado
        sed -i '/^\s*#define.*\*GNU\*SOURCE/d' "$file"
        sed -i '/^\s*#define\s*_GNU_SOURCE/d' "$file" 
        echo "🔧 Limpiado $file"
    fi
}

# Limpiar archivos de fuente
echo "🔧 Limpiando headers malformados..."
clean_gnu_source "include/common.h"
clean_gnu_source "src/ast.c" 
clean_gnu_source "src/semantic.c"
clean_gnu_source "src/common.c"

# Agregar _GNU_SOURCE correctamente solo donde es necesario
echo "🔧 Agregando _GNU_SOURCE correctamente..."

# En common.h
if [ -f "include/common.h" ] && ! grep -q "^#define _GNU_SOURCE" include/common.h; then
    sed -i '1i#define _GNU_SOURCE' include/common.h
    echo "✅ _GNU_SOURCE agregado a common.h"
fi

# Verificar que el lexer corregido esté en su lugar
if [ -f "lexer/lexer.l" ]; then
    if grep -q "return PUBLIC;" lexer/lexer.l; then
        echo "✅ Lexer ya usa tokens simbólicos"
    else
        echo "⚠️  Lexer aún usa números. Reemplázalo con el lexer corregido."
    fi
fi

# Limpiar archivos generados
echo "🧹 Limpiando archivos generados..."
rm -f javalang_interpreter 
rm -f parser/parser.tab.*
rm -f lexer/lex.yy.c
rm -f *.log
rm -f parser/*.output

echo "✅ Limpieza completada"