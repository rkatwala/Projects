all:
	flex lexer.lex
	bison -v -d --file-prefix=y compiler.y
	g++ -std=c++11 -o parser.exe lex.yy.c y.tab.c -lfl

parser_test_basic:
	flex lexer.lex
	bison -v -d --file-prefix=y compiler.y
	g++ -std=c++11 -o parser.exe lex.yy.c y.tab.c -lfl
	./parser.exe ../programs/basic.nerj

parser_test_array:
	flex lexer.lex
	bison -v -d --file-prefix=y compiler.y
	g++ -std=c++11 -o parser.exe lex.yy.c y.tab.c -lfl
	./parser.exe ../programs/array_test.nerj

parser_test_function_call:
	flex lexer.lex
	bison -v -d --file-prefix=y compiler.y
	g++ -std=c++11 -o parser.exe lex.yy.c y.tab.c -lfl
	./parser.exe ../programs/function_test.nerj

parser_test_syntax_error:
	flex lexer.lex
	bison -v -d --file-prefix=y compiler.y
	g++ -std=c++11 -o parser.exe lex.yy.c y.tab.c -lfl
	./parser.exe ../programs/parser_syntax_test.nerj

parser_test_loop:
	flex lexer.lex
	bison -v -d --file-prefix=y compiler.y
	g++ -std=c++11 -o parser.exe lex.yy.c y.tab.c -lfl
	./parser.exe ../programs/loop_test_case.nerj

parser_test_if_else:
	flex lexer.lex
	bison -v -d --file-prefix=y compiler.y
	g++ -std=c++11 -o parser.exe lex.yy.c y.tab.c -lfl
	./parser.exe ../programs/if_and_else_test_case.nerj

break: 
	flex lexer.lex
	bison -v -d --file-prefix=y compiler.y
	g++ -std=c++11 -o parser.exe lex.yy.c y.tab.c -lfl
	./parser.exe ../programs/break.nerj

nested_while:
	flex lexer.lex
	bison -v -d --file-prefix=y compiler.y
	g++ -std=c++11 -o parser.exe lex.yy.c y.tab.c -lfl
	./parser.exe ../programs/nested_while.nerj

lex_test:
	flex lexer.lex
	g++ lex.yy.c -lfl -o lexer.exe
	./lexer.exe < ../programs/lexer_test.nerj


lex_test_invalid_ident:
	flex lexer.lex
	g++ lex.yy.c -lfl -o lexer.exe
	./lexer.exe < ../programs/lexer_test_invalid_identifier.nerj

lex_test_invalid_char:
	flex lexer.lex
	g++ lex.yy.c -lfl -o lexer.exe
	./lexer.exe < ../programs/lexer_test_invalid_character.nerj

lex_test_ws:
	flex lexer.lex
	g++ lex.yy.c -lfl -o lexer.exe
	./lexer.exe < ../programs/lexer_test_whitespace.nerj
