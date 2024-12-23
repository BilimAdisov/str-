OPT = -fprofile-arcs -ftest-coverage -g
C_FILES = s21_string.c 
O_FILES = s21_string.o 
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

test.c: test.check
	checkmk clean_mode=1 test.check > test.c

clean:
	rm -rf *.o *.gch *.out *.gcno *.gcda *.info *.gcov *.a
	rm -rf report/
	rm -rf temp/
	rm -rf test.c
	rm -rf valgrind_output.log

style:
	clang-format -style=file --assume-filename=..\materials\linters\.clang-format -i *.c *.h

valgrind-check:
	valgrind --log-file=valgrind_output.log --tool=memcheck --leak-check=yes ./a.out 