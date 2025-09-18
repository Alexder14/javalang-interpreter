CC = gcc
CFLAGS = -std=c99 -g -Iinclude -w
BISON = bison
FLEX = flex

TARGET = javalang_advanced
SOURCES = src/main.c src/javalang.c parser/parser.tab.c lexer/lex.yy.c

all: $(TARGET)

parser/parser.tab.c: parser/parser.y
	$(BISON) -d -o parser/parser.tab.c parser/parser.y

lexer/lex.yy.c: lexer/lexer.l
	$(FLEX) -o lexer/lex.yy.c lexer/lexer.l

$(TARGET): parser/parser.tab.c lexer/lex.yy.c $(SOURCES)
	$(CC) $(CFLAGS) -o $(TARGET) $(SOURCES)

test: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET) parser/parser.tab.* lexer/lex.yy.c

.PHONY: all clean test
