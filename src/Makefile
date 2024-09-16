
CC = g++ -std=c++17
CFLAGS = -Wall -Wextra -Werror -g

SYSSHELL:=$(shell uname)
ifeq ($(SYSSHELL), Linux)
	TFLAGS=-lgtest_main  -lgtest -lpthread --coverage
else
	TFLAGS=$(shell pkg-config --cflags --libs check) --coverage
endif


all: test

s21_matrix_oop.a:
	$(CC) $(CFLAGS) S21Matrix.cpp operators_.cpp -c
	ar rvs s21_matrix_oop.a *.o
	rm -rf *.o

test: clean s21_matrix_oop.a
	$(CC) $(CFLAGS) test.cpp $(TFLAGS) -c s21_matrix_oop.h
	$(CC) $(CFLAGS) test.o $(TFLAGS) -o test s21_matrix_oop.a

clean:
	rm -rf *.gcno *.info *.gcda *.o *.a s21_matrix_oop.h.gch test report

valgrind_check: test
	valgrind -s  --leak-check=full --show-leak-kinds=all --track-origins=yes ./test

style_check:
	cp ../materials/linters/.clang-format .
	clang-format -n *.cpp *.h
	rm ./.clang-format

style_fix:
	cp ../materials/linters/.clang-format .
	clang-format -i *.cpp *.h
	rm ./.clang-format









