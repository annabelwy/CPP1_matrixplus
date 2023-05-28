CC = g++ -Wall -Werror -Wextra
OS := $(shell uname)

ifeq ($(OS),Linux)
FLAGS = -lgtest -lm -lpthread -lrt -lsubunit -fprofile-arcs -ftest-coverage
else
FLAGS = -lgtest -lm -lpthread -fprofile-arcs -ftest-coverage
endif

all: test

clean:
	rm -rf *.o *.a unit_test main
	rm -rf *.gcno *gcda *.gcov gcov
	rm -rf report report.info
	rm -rf *.dSYM

test: clean s21_matrix_oop.a
	$(CC) unit_test.cpp s21_matrix_oop.a $(FLAGS) -o unit_test
	./unit_test

s21_matrix_oop.a: s21_matrix_oop.cpp s21_matrix_operators.cpp
	$(CC) -c s21_matrix_oop.cpp s21_matrix_operators.cpp
	ar -crs s21_matrix_oop.a *.o

gcov_reprt: clean
	$(CC) unit_test.cpp s21_matrix_oop.cpp s21_matrix_operators.cpp $(FLAGS) -o unit_test
	./unit_test
	lcov -t "./unit_test" -o report.info --no-external -c -d .
	genhtml -o report report.info
	open ./report/index.html
	rm -rf *.gcno *gcda *.gco

clang:
	cp ../materials/linters/.clang-format ./
	clang-format -n *.cpp *.h
	rm .clang-format


leak: clean test
	leaks -atExit -- ./unit_test