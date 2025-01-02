OPT = -fprofile-arcs -ftest-coverage -g
C_FILES = s21_string.c s21_sprintf.c s21_insert.c s21_to_lower.c s21_to_upper.c s21_trim.c
O_FILES = s21_string.o s21_sprintf.o s21_insert.o s21_to_lower.o s21_to_upper.o s21_trim.o
CCFLAGS = -Wall -Werror -Wextra -std=c11

SHELLNAME:=$(shell uname)
ifeq ($(SHELLNAME), Linux)
  LIBS = -lcheck -lpthread -lm -lsubunit
else ifeq ($(SHELLNAME), Darwin)
  LIBS= -lcheck -lm -lpthread
endif

all: clean s21_string.a 

s21_string.a:
	gcc -c $(CCFLAGS) $(C_FILES) -g
	ar rcs s21_string.a $(O_FILES)
	ranlib s21_string.a

test: test.c $(O_FILES)
	gcc -c $(CCFLAGS) test.c
	gcc $(OPT) test.o $(O_FILES) $(LIBS)
	./a.out

gcov_report: clean test.c 
	gcc --coverage -c $(CCFLAGS) test.c $(C_FILES) $(LIBS)
	gcc --coverage test.o $(O_FILES) $(LIBS)
	./a.out
	lcov -t "coverage_report" -o coverage.info -c -d .
	genhtml -o report coverage.info

clean:
	rm -rf *.o *.gch *.out *.gcno *.gcda *.info *.gcov *.a
	rm -rf report/
	rm -rf temp/
	rm -rf valgrind_output.log

style:
	clang-format -style=Google -i *.c *.h

valgrind-check:
	valgrind --log-file=valgrind_output.log --tool=memcheck --leak-check=yes --track-origins=yes ./a.out 