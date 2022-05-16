.SUFFIXES:
.SUFFIXES: .cpp .o

LEX = win_flex
YACC = win_bison
YFLAGS = -dv
DEFINES =
CXX = g++
CC = gcc
INCLUDES = -I .
CFLAGS = $(INCLUDES) $(DEFINES)  -g -Wall -pipe -DUSING_GCC
CXXFLAGS = $(INCLUDES) $(DEFINES)  -g -Wall -pipe -DUSING_GCC
LDFLAGS = -lm -g

SCANNER = scanner.cpp
PARSER  = parser.cpp parser.hpp location.hh position.hh stack.hh

OBJS = 	scanner.o parser.o main.o compiler.o utils.o option.o \
	 	ast/ast.o ast/ast_program.o ast/ast_step.o ast/ast_raw_string.o \
		ast/ast_interval.o ast/ast_single_int.o \
		translate/translation.o \
		builder/step.o builder/timeline.o


all: $(SCANNER) $(PARSER) $(OBJS)
	$(CXX) $(OBJS) $(LDFLAGS) -o build/GMAM.exe

$(SCANNER): frontend/scanner.l
	$(LEX) $(LFLAGS) $<

$(PARSER): frontend/parser.y
	$(YACC) $(YFLAGS) $<

clean:
	rm build/GMAM.exe $(SCANNER) $(PARSER) parser.output $(OBJS)

main.o: compiler.hpp utils.hpp define.hpp
scanner.o: parser.hpp location.hpp
parser.o: ast/ast.hpp location.hpp compiler.hpp define.hpp
utils.o: utils.hpp
compiler.o: builder/timeline.hpp translate/translation.hpp compiler.hpp utils.hpp
option.o: option.hpp
ast/ast.o: ast/ast.hpp location.hpp define.hpp
ast/ast_program.o: ast/ast.hpp location.hpp visitor.hpp define.hpp
ast/ast_step.o: ast/ast.hpp location.hpp visitor.hpp define.hpp
ast/ast_interval.o: ast/ast.hpp location.hpp visitor.hpp define.hpp
ast/ast_single_int.o: ast/ast.hpp location.hpp visitor.hpp define.hpp
ast/ast_raw_string.o: ast/ast.hpp location.hpp visitor.hpp define.hpp
translate/translation.o: translate/translation.hpp ast/ast.hpp visitor.hpp define.hpp
translate/translation.o: builder/timeline.hpp builder/step.hpp
builder/timeline.o: builder/step.hpp builder/timeline.hpp define.hpp
builder/step.o: builder/step.hpp define.hpp