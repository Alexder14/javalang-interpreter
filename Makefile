# Makefile para el Compilador JavaLang
# Proyecto de Organización de Lenguajes y Compiladores 2

# Variables de configuración
CC = gcc
CFLAGS = -Wall -std=c99 -g
INCLUDES = -Iinclude -Iparser
LIBS = -lfl

# Directorios
SRC_DIR = src
INCLUDE_DIR = include
PARSER_DIR = parser
LEXER_DIR = lexer
EXAMPLES_DIR = examples

# Archivos fuente
COMMON_SOURCES = $(SRC_DIR)/common.c
AST_SOURCES = $(SRC_DIR)/ast.c
SEMANTIC_SOURCES = $(SRC_DIR)/semantic.c
MAIN_SOURCES = $(SRC_DIR)/main.c

# Archivos generados
LEXER_OUTPUT = $(LEXER_DIR)/lex.yy.c
PARSER_OUTPUT = $(PARSER_DIR)/parser.tab.c
PARSER_HEADER = $(PARSER_DIR)/parser.tab.h

# Ejecutables
LEXER_TEST = test_lexer
PARSER_TEST = test_parser
SEMANTIC_TEST = test_semantic
INTERPRETER = javalang_interpreter

# Regla principal - compila todo
all: $(INTERPRETER) $(SEMANTIC_TEST) $(PARSER_TEST) $(LEXER_TEST)
	@echo "╔════════════════════════════════════════════════════════════════════════╗"
	@echo "║                     ¡COMPILACIÓN COMPLETADA!                          ║"
	@echo "╚════════════════════════════════════════════════════════════════════════╝"
	@echo "✅ Todos los componentes compilados exitosamente"
	@echo ""
	@echo "📋 Ejecutables disponibles:"
	@echo "   • $(INTERPRETER)  - Interpretador completo"
	@echo "   • $(SEMANTIC_TEST)   - Test de análisis semántico"
	@echo "   • $(PARSER_TEST)     - Test de análisis sintáctico"
	@echo "   • $(LEXER_TEST)      - Test de análisis léxico"

# Fase 1: Solo configuración (ya completada)
phase1:
	@echo "✅ Fase 1: Configuración - Ya completada"

# Fase 2: Analizador léxico
phase2: $(LEXER_TEST)
	@echo "✅ Fase 2: Analizador léxico completado"

# Fase 3: Analizador sintáctico y AST
phase3: $(PARSER_TEST)
	@echo "✅ Fase 3: Analizador sintáctico completado"

# Fase 4: Análisis semántico
phase4: $(SEMANTIC_TEST) $(INTERPRETER)
	@echo "✅ Fase 4: Análisis semántico completado"

# Compilar interpretador completo
$(INTERPRETER): $(LEXER_OUTPUT) $(PARSER_OUTPUT) $(COMMON_SOURCES) $(AST_SOURCES) $(SEMANTIC_SOURCES) $(VISUALIZER_SOURCES) $(REPORTS_SOURCES) $(MAIN_SOURCES)
	@echo "🏗️ Compilando interpretador completo..."
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ \
		$(MAIN_SOURCES) $(PARSER_OUTPUT) $(LEXER_OUTPUT) \
		$(AST_SOURCES) $(SEMANTIC_SOURCES) $(VISUALIZER_SOURCES) $(REPORTS_SOURCES) $(COMMON_SOURCES) $(LIBS) 2>/dev/null || \
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ \
		$(MAIN_SOURCES) $(PARSER_OUTPUT) $(LEXER_OUTPUT) \
		$(AST_SOURCES) $(SEMANTIC_SOURCES) $(VISUALIZER_SOURCES) $(REPORTS_SOURCES) $(COMMON_SOURCES)

# Test de análisis semántico
$(SEMANTIC_TEST): $(LEXER_OUTPUT) $(PARSER_OUTPUT) $(COMMON_SOURCES) $(AST_SOURCES) $(SEMANTIC_SOURCES) $(VISUALIZER_SOURCES) $(REPORTS_SOURCES) $(SRC_DIR)/test_semantic.c
	@echo "🔬 Compilando test de análisis semántico..."
	$(CC) -DTEST_SEMANTIC $(CFLAGS) $(INCLUDES) -o $@ \
		$(SRC_DIR)/test_semantic.c $(PARSER_OUTPUT) $(LEXER_OUTPUT) \
		$(AST_SOURCES) $(SEMANTIC_SOURCES) $(VISUALIZER_SOURCES) $(REPORTS_SOURCES) $(COMMON_SOURCES) $(LIBS) 2>/dev/null || \
	$(CC) -DTEST_SEMANTIC $(CFLAGS) $(INCLUDES) -o $@ \
		$(SRC_DIR)/test_semantic.c $(PARSER_OUTPUT) $(LEXER_OUTPUT) \
		$(AST_SOURCES) $(SEMANTIC_SOURCES) $(VISUALIZER_SOURCES) $(REPORTS_SOURCES) $(COMMON_SOURCES)

# Test de análisis sintáctico
$(PARSER_TEST): $(LEXER_OUTPUT) $(PARSER_OUTPUT) $(COMMON_SOURCES) $(AST_SOURCES)
	@echo "📝 Compilando test de análisis sintáctico..."
	$(CC) -DTEST_PARSER $(CFLAGS) $(INCLUDES) -o $@ \
		$(PARSER_OUTPUT) $(LEXER_OUTPUT) $(AST_SOURCES) $(COMMON_SOURCES) $(LIBS) 2>/dev/null || \
	$(CC) -DTEST_PARSER $(CFLAGS) $(INCLUDES) -o $@ \
		$(PARSER_OUTPUT) $(LEXER_OUTPUT) $(AST_SOURCES) $(COMMON_SOURCES)

# Test de analizador léxico
$(LEXER_TEST): $(LEXER_OUTPUT) $(COMMON_SOURCES)
	@echo "🔍 Compilando test de analizador léxico..."
	$(CC) -DTEST_LEXER $(CFLAGS) $(INCLUDES) -o $@ \
		$(LEXER_OUTPUT) $(COMMON_SOURCES) $(LIBS) 2>/dev/null || \
	$(CC) -DTEST_LEXER $(CFLAGS) $(INCLUDES) -o $@ \
		$(LEXER_OUTPUT) $(COMMON_SOURCES)

# Generar parser con Bison
$(PARSER_OUTPUT): $(PARSER_DIR)/parser.y
	@echo "📝 Generando parser con Bison..."
	bison -d -o $@ $<

# Generar lexer con Flex
$(LEXER_OUTPUT): $(LEXER_DIR)/lexer.l
	@echo "🔍 Generando lexer con Flex..."
	flex -o $@ $<

# Limpiar archivos generados
clean:
	@echo "🧹 Limpiando archivos generados..."
	rm -f $(LEXER_OUTPUT) $(PARSER_OUTPUT) $(PARSER_HEADER)
	rm -f $(INTERPRETER) $(SEMANTIC_TEST) $(PARSER_TEST) $(LEXER_TEST)
	@echo "✅ Limpieza completada"

# Limpiar todo incluyendo archivos de backup
distclean: clean
	@echo "🧹 Limpieza completa..."
	rm -f *~ $(SRC_DIR)/*~ $(INCLUDE_DIR)/*~ $(PARSER_DIR)/*~ $(LEXER_DIR)/*~
	rm -f *.o $(SRC_DIR)/*.o

# Probar el analizador léxico
test-lexer: $(LEXER_TEST)
	@echo "🧪 Probando analizador léxico..."
	@if [ -f $(EXAMPLES_DIR)/test1.usl ]; then \
		./$(LEXER_TEST) $(EXAMPLES_DIR)/test1.usl; \
	else \
		echo "❌ Archivo de prueba no encontrado: $(EXAMPLES_DIR)/test1.usl"; \
	fi

# Probar el analizador sintáctico
test-parser: $(PARSER_TEST)
	@echo "🧪 Probando analizador sintáctico..."
	@if [ -f $(EXAMPLES_DIR)/test1.usl ]; then \
		./$(PARSER_TEST) $(EXAMPLES_DIR)/test1.usl; \
	else \
		echo "❌ Archivo de prueba no encontrado: $(EXAMPLES_DIR)/test1.usl"; \
	fi

# Probar el analizador semántico
test-semantic: $(SEMANTIC_TEST)
	@echo "🧪 Probando analizador semántico..."
	@if [ -f $(EXAMPLES_DIR)/test_semantic.usl ]; then \
		./$(SEMANTIC_TEST) $(EXAMPLES_DIR)/test_semantic.usl; \
	else \
		echo "❌ Archivo de prueba no encontrado: $(EXAMPLES_DIR)/test_semantic.usl"; \
		echo "Creando archivo de prueba básico..."; \
		mkdir -p $(EXAMPLES_DIR); \
		echo "public class Test { public static void main() { int x = 5; System.out.println(x); } }" > $(EXAMPLES_DIR)/test_semantic.usl; \
		./$(SEMANTIC_TEST) $(EXAMPLES_DIR)/test_semantic.usl; \
	fi

# Probar el interpretador completo
test-interpreter: $(INTERPRETER)
	@echo "🧪 Probando interpretador completo..."
	@if [ -f $(EXAMPLES_DIR)/test_semantic.usl ]; then \
		./$(INTERPRETER) $(EXAMPLES_DIR)/test_semantic.usl; \
	else \
		echo "❌ Archivo de prueba no encontrado: $(EXAMPLES_DIR)/test_semantic.usl"; \
	fi

# Ejecutar todas las pruebas
test-all: test-lexer test-parser test-semantic test-interpreter
	@echo "🎯 Todas las pruebas completadas"

# Verificar dependencias
check-deps:
	@echo "🔍 Verificando dependencias..."
	@which flex > /dev/null || (echo "❌ Flex no encontrado"; exit 1)
	@which bison > /dev/null || (echo "❌ Bison no encontrado"; exit 1)
	@which gcc > /dev/null || (echo "❌ GCC no encontrado"; exit 1)
	@echo "✅ Todas las dependencias están instaladas"

# Mostrar ayuda
help:
	@echo "╔════════════════════════════════════════════════════════════════════════╗"
	@echo "║                    MAKEFILE COMPILADOR JAVALANG                       ║"
	@echo "╚════════════════════════════════════════════════════════════════════════╝"
	@echo ""
	@echo "📋 Objetivos principales:"
	@echo "   all              - Compilar todo el proyecto"
	@echo "   phase2           - Compilar solo Fase 2 (Analizador léxico)"
	@echo "   phase3           - Compilar solo Fase 3 (Analizador sintáctico)"
	@echo "   phase4           - Compilar solo Fase 4 (Análisis semántico)"
	@echo ""
	@echo "🧪 Objetivos de prueba:"
	@echo "   test-lexer       - Probar analizador léxico"
	@echo "   test-parser      - Probar analizador sintáctico"
	@echo "   test-semantic    - Probar analizador semántico"
	@echo "   test-interpreter - Probar interpretador completo"
	@echo "   test-all         - Ejecutar todas las pruebas"
	@echo ""
	@echo "🛠️ Objetivos de mantenimiento:"
	@echo "   clean            - Limpiar archivos generados"
	@echo "   distclean        - Limpieza completa"
	@echo "   check-deps       - Verificar dependencias"
	@echo "   help             - Mostrar esta ayuda"

# Declarar objetivos que no crean archivos
.PHONY: all phase1 phase2 phase3 phase4 clean distclean test-lexer test-parser test-semantic test-interpreter test-all check-deps help