CC = gcc
CFLAGS = -Wall -std=c99 -g

all: javalang_interpreter

javalang_interpreter: src/main.c src/common.c
mkdir -p obj
$(CC) $(CFLAGS) -Iinclude -o javalang_interpreter src/main.c src/common.c

check-tools:
@echo "=== Verificando Herramientas ==="
@which gcc && echo "GCC: ✅" || echo "ERROR: gcc no encontrado"
@which flex && echo "Flex: ✅" || echo "ERROR: flex no encontrado"
@which bison && echo "Bison: ✅" || echo "ERROR: bison no encontrado"

test: javalang_interpreter
@echo "=== Probando Ejecutable ==="
./javalang_interpreter examples/test1.usl

clean:
rm -f javalang_interpreter
rm -rf obj

help:
@echo "Comandos disponibles:"
@echo "  make              - Compilar proyecto"
@echo "  make check-tools  - Verificar herramientas"
@echo "  make test         - Probar ejecutable"
@echo "  make clean        - Limpiar archivos"

.PHONY: all check-tools test clean help
