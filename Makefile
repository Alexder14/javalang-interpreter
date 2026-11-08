# Makefile para JavaLang Interpreter - Fase 4
# ============================================

# Compilador y flags
CC = gcc
CFLAGS = -Wall -std=c99 -g -D_GNU_SOURCE -DTEST_SEMANTIC
INCLUDES = -Iinclude -Iparser
LIBS = -lfl

# Suprimir algunos warnings específicos
CFLAGS += -Wno-unused-function -Wno-unused-variable

# Directorios
SRCDIR = src
INCDIR = include
PARSERDIR = parser
LEXERDIR = lexer
BUILDDIR = build

# Archivos fuente
SOURCES = $(SRCDIR)/main.c $(SRCDIR)/ast.c $(SRCDIR)/semantic.c $(SRCDIR)/common.c
PARSER_SRC = $(PARSERDIR)/parser.tab.c
LEXER_SRC = $(LEXERDIR)/lex.yy.c

# Objetivo principal
TARGET = javalang_interpreter

# Regla principal
all: $(TARGET)

# Crear directorio de build si no existe
$(BUILDDIR):
	mkdir -p $(BUILDDIR)

# Generar lexer
$(LEXER_SRC): $(LEXERDIR)/lexer.l
	@echo "🔍 Generando lexer con Flex..."
	flex -o $(LEXER_SRC) $(LEXERDIR)/lexer.l

# Generar parser
$(PARSER_SRC): $(PARSERDIR)/parser.y
	@echo "📝 Generando parser con Bison..."
	bison -d -o $(PARSER_SRC) $(PARSERDIR)/parser.y

# Compilar interpretador principal
$(TARGET): $(LEXER_SRC) $(PARSER_SRC) $(SOURCES) | $(BUILDDIR)
	@echo "🏗️ Compilando interpretador completo..."
	$(CC) $(CFLAGS) $(INCLUDES) -o $(TARGET) \
		$(SOURCES) $(PARSER_SRC) $(LEXER_SRC) $(LIBS) || \
	$(CC) $(CFLAGS) $(INCLUDES) -o $(TARGET) \
		$(SOURCES) $(PARSER_SRC) $(LEXER_SRC)

# Limpiar archivos generados
clean:
	@echo "🧹 Limpiando archivos generados..."
	rm -f $(TARGET)
	rm -f $(LEXER_SRC)
	rm -f $(PARSER_SRC)
	rm -f $(PARSERDIR)/parser.tab.h
	rm -f *.output
	rm -rf $(BUILDDIR)

# Limpiar todo incluyendo reportes
clean-all: clean
	@echo "🧹 Limpiando todos los archivos..."
	rm -f *.txt *.dot *.png
	rm -f examples/*.txt examples/*.dot examples/*.png

# Compilar solo el lexer para testing
test-lexer: $(LEXER_SRC)
	@echo "🔍 Compilando lexer para testing..."
	$(CC) -DTEST_LEXER $(CFLAGS) $(INCLUDES) -o test_lexer $(LEXER_SRC) $(SRCDIR)/common.c $(LIBS) || \
	$(CC) -DTEST_LEXER $(CFLAGS) $(INCLUDES) -o test_lexer $(LEXER_SRC) $(SRCDIR)/common.c

# Instalar dependencias (solo informativo)
install-deps:
	@echo "📦 Para instalar dependencias manualmente:"
	@echo "   sudo apt-get install flex bison gcc make"
	@echo "   sudo apt-get install graphviz (opcional)"

# Ejecutar tests básicos
check: $(TARGET)
	@echo "🧪 Ejecutando tests básicos..."
	@if [ -f examples/test1.usl ]; then \
		echo "📝 Probando con examples/test1.usl"; \
		./$(TARGET) examples/test1.usl; \
	else \
		echo "⚠️  Archivo examples/test1.usl no encontrado"; \
	fi

# Mostrar información del proyecto
info:
	@echo "╔════════════════════════════════════════════════════════════════════════╗"
	@echo "║                      JAVALANG INTERPRETER v1.0                        ║"
	@echo "║                          Fase 4 - Análisis Semántico                  ║"
	@echo "╚════════════════════════════════════════════════════════════════════════╝"
	@echo ""
	@echo "🎯 Objetivos completados:"
	@echo "   ✅ Fase 1: Configuración y preparación"
	@echo "   ✅ Fase 2: Analizador léxico (Flex)"
	@echo "   ✅ Fase 3: Analizador sintáctico (Bison) + AST"
	@echo "   🚀 Fase 4: Analizador semántico + Tabla de símbolos"
	@echo ""
	@echo "📁 Estructura del proyecto:"
	@echo "   📂 src/          - Código fuente principal"
	@echo "   📂 include/      - Archivos de cabecera"
	@echo "   📂 lexer/        - Definiciones del lexer (Flex)"
	@echo "   📂 parser/       - Definiciones del parser (Bison)"
	@echo "   📂 examples/     - Archivos de prueba .usl"
	@echo ""
	@echo "🔧 Comandos disponibles:"
	@echo "   make             - Compilar todo el proyecto"
	@echo "   make clean       - Limpiar archivos generados"
	@echo "   make test        - Ejecutar tests básicos"
	@echo "   make test-lexer  - Compilar solo el lexer"

# Help
help: info

# Phony targets
.PHONY: all clean clean-all test test-lexer install-deps info help
# Pruebas: los ejemplos válidos deben compilar; los *error* deben fallar
check-ejemplos: $(TARGET)
	@fail=0; \
	for f in examples/*.usl tests/test_files/*.usl; do \
		case $$f in *error*) want=fail;; *) want=ok;; esac; \
		if ./$(TARGET) $$f 2>&1 | grep -q "Compilación exitosa"; then got=ok; else got=fail; fi; \
		if [ $$got = $$want ]; then echo "PASS $$f"; else echo "FAIL $$f (esperado $$want)"; fail=1; fi; \
	done; \
	rm -f *_ast.txt *_errors.txt; \
	exit $$fail
