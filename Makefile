CC    = gcc
BISON = bison
FLEX  = flex

all:
	cd src && $(BISON) -d parser.y
	cd src && $(FLEX) lexer.l
	$(CC) -I include/ -Wall -Wno-unused-function -o compiler.exe \
	    src/parser.tab.c src/lex.yy.c \
	    src/main.c src/ast.c src/value.c src/symtab.c src/functab.c \
	    src/semantic.c src/tac.c src/exec.c

test:
	powershell -ExecutionPolicy Bypass -File tests/run_tests.ps1

clean:
	powershell -ExecutionPolicy Bypass -File clean.ps1


// Get-Content .\tests\my_test.txt | .\compiler.exe