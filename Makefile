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
SOURCES = $(SRCDIR)/main.c $(SRCDIR)/ast.c $(SRCDIR)/semantic.c $(SRCDIR)/interpreter.c $(SRCDIR)/ast_dot.c $(SRCDIR)/common.c
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
	rm -f $(REPORT_FILES); \
	exit $$fail

# Ejecución: cada tests/run/X.usl se ejecuta y su salida debe ser igual a tests/run/X.out
# (los X.usl con "error" en el nombre deben terminar con error en ejecución).
check-ejecucion: $(TARGET)
	@fail=0; \
	for f in tests/run/*.usl; do \
		b=$${f%.usl}; \
		got=$$(./$(TARGET) $$f 2>&1 | awk '/Ejecutando código/{f=1;skip=1;next} f&&skip{skip=0;next} f&&/^═══/{exit} f{print}'); \
		want=$$(cat $$b.out); \
		./$(TARGET) $$f >/dev/null 2>&1; rc=$$?; \
		case $$f in *error*) wantrc=1;; *) wantrc=0;; esac; \
		if [ "$$got" = "$$want" ] && [ $$rc = $$wantrc ]; then echo "PASS $$f"; \
		else echo "FAIL $$f (salida o código de retorno distintos)"; fail=1; fi; \
	done; \
	rm -f $(REPORT_FILES); exit $$fail

# Semántica: cada tests/semantica/X.usl debe fallar y reportar el mensaje que está en X.msg
check-semantica: $(TARGET)
	@fail=0; \
	for f in tests/semantica/*.usl; do \
		b=$${f%.usl}; want=$$(cat $$b.msg); \
		out=$$(./$(TARGET) $$f 2>&1); \
		if echo "$$out" | grep -qF -- "$$want"; then echo "PASS $$f"; \
		else echo "FAIL $$f (no aparece: $$want)"; fail=1; fi; \
	done; \
	rm -f $(REPORT_FILES); exit $$fail

# Reportes: se generan los archivos de AST (grafo), símbolos y errores
check-reportes: $(TARGET)
	@mkdir -p build/rep && cp tests/run/funciones.usl build/rep/ && (cd build/rep && ../../$(TARGET) funciones.usl >/dev/null 2>&1); \
	fail=0; \
	for f in funciones_errors.txt funciones_symbols.txt funciones_ast.txt funciones_ast.dot; do \
		if [ -s build/rep/$$f ]; then echo "PASS $$f"; else echo "FAIL $$f (no se generó)"; fail=1; fi; \
	done; \
	grep -q "digraph AST" build/rep/funciones_ast.dot && echo "PASS dot válido" || { echo "FAIL dot"; fail=1; }; \
	grep -q "Tipo simbolo" build/rep/funciones_symbols.txt && echo "PASS columnas de la tabla" || { echo "FAIL columnas"; fail=1; }; \
	exit $$fail

# Todas las pruebas
check-todo: check-ejemplos check-ejecucion check-semantica check-reportes

# Variante con la precedencia de + y - intercambiada con la de * / %
# (genera ./javalang_interpreter_inv sin modificar parser/parser.y)
REPORT_FILES = *_ast.txt *_ast.dot *_ast.png *_errors.txt *_symbols.txt
INV_DIR = $(BUILDDIR)/inv
precedencia-invertida: $(LEXERDIR)/lexer.l $(PARSERDIR)/parser.y $(SOURCES)
	@echo "🔁 Generando intérprete con precedencia de + - y * / % intercambiada..."
	mkdir -p $(INV_DIR)
	sed -e 's/^%left PLUS MINUS$$/%left @@TMP@@/' \
	    -e 's/^%left MULTIPLY DIVIDE MODULO$$/%left PLUS MINUS/' \
	    -e 's/^%left @@TMP@@$$/%left MULTIPLY DIVIDE MODULO/' \
	    $(PARSERDIR)/parser.y > $(INV_DIR)/parser.y
	@grep -n "^%left PLUS MINUS\|^%left MULTIPLY" $(INV_DIR)/parser.y
	bison -d -o $(INV_DIR)/parser.tab.c $(INV_DIR)/parser.y
	flex -o $(INV_DIR)/lex.yy.c $(LEXERDIR)/lexer.l
	$(CC) $(CFLAGS) -I$(INV_DIR) -Iinclude -o javalang_interpreter_inv \
		$(SOURCES) $(INV_DIR)/parser.tab.c $(INV_DIR)/lex.yy.c $(LIBS)
	@echo "✅ ./javalang_interpreter_inv listo"

.PHONY: check-ejecucion precedencia-invertida check-semantica check-reportes check-todo
