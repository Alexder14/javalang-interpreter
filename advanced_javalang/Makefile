# Makefile para Advanced JavaLang con GUI
CC = gcc
CFLAGS = -std=c99 -g -Iinclude -Igui/include -Wall -D_GNU_SOURCE
BISON = bison
FLEX = flex

# GTK
GTK_CFLAGS = $(shell pkg-config --cflags gtk+-3.0 gtksourceview-3.0 2>/dev/null)
GTK_LIBS = $(shell pkg-config --libs gtk+-3.0 gtksourceview-3.0 2>/dev/null)

# Targets
TARGET_CLI = javalang_advanced
TARGET_GUI = javalang_gui

# Fuentes
CLI_SOURCES = src/main.c src/javalang.c parser/parser.tab.c lexer/lex.yy.c
GUI_SOURCES = gui/src/main_gui.c gui/src/javalang_app.c gui/src/callbacks.c \
              src/javalang.c parser/parser.tab.c lexer/lex.yy.c

.PHONY: all clean cli gui test-cli run-gui help

all: $(TARGET_CLI) $(TARGET_GUI)
	@echo "✅ Compilación completada"
	@echo "🚀 Ejecutables disponibles:"
	@echo "   CLI: ./$(TARGET_CLI)"
	@echo "   GUI: ./$(TARGET_GUI)"

# Generar archivos del parser
parser/parser.tab.c parser/parser.tab.h: parser/parser.y
	@echo "🔧 Generando parser..."
	$(BISON) -d -o parser/parser.tab.c parser/parser.y

# Generar archivos del lexer  
lexer/lex.yy.c: lexer/lexer.l parser/parser.tab.h
	@echo "🔧 Generando lexer..."
	$(FLEX) -o lexer/lex.yy.c lexer/lexer.l

# Compilar versión CLI
$(TARGET_CLI): parser/parser.tab.c lexer/lex.yy.c $(CLI_SOURCES)
	@echo "🏗️  Compilando CLI..."
	$(CC) $(CFLAGS) -o $(TARGET_CLI) $(CLI_SOURCES)

# Compilar versión GUI
$(TARGET_GUI): parser/parser.tab.c lexer/lex.yy.c $(GUI_SOURCES)
	@echo "🖥️  Compilando GUI..."
	@if pkg-config --exists gtk+-3.0 gtksourceview-3.0; then \
		$(CC) $(CFLAGS) $(GTK_CFLAGS) -o $(TARGET_GUI) $(GUI_SOURCES) $(GTK_LIBS); \
	else \
		echo "⚠️  GTK3 no encontrado - omitiendo GUI"; \
		echo "   Para instalar: sudo apt install libgtk-3-dev libgtksourceview-3.0-dev"; \
	fi

# Solo CLI
cli: $(TARGET_CLI)

# Solo GUI  
gui: $(TARGET_GUI)

# Probar CLI
test-cli: $(TARGET_CLI)
	@echo "🧪 Ejecutando prueba CLI..."
	./$(TARGET_CLI)

# Ejecutar GUI
run-gui: $(TARGET_GUI)
	@echo "🚀 Iniciando GUI..."
	./$(TARGET_GUI) &

# Limpiar
clean:
	@echo "🧹 Limpiando archivos generados..."
	rm -f $(TARGET_CLI) $(TARGET_GUI)
	rm -f parser/parser.tab.c parser/parser.tab.h
	rm -f lexer/lex.yy.c

# Ayuda
help:
	@echo "📖 MAKEFILE JAVALANG ADVANCED"
	@echo "============================"
	@echo "make          - Compilar CLI y GUI"
	@echo "make cli      - Solo CLI"
	@echo "make gui      - Solo GUI"  
	@echo "make test-cli - Probar CLI"
	@echo "make run-gui  - Ejecutar GUI"
	@echo "make clean    - Limpiar archivos"
