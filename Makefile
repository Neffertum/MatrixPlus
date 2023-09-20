CC = g++ -g
CFLAG = -std=c++17 -Wall -Werror -Wextra #-fsanitize=address #-Wpedantic
FILES = s21_matrix_oop.cc operator_and_help.cc s21_matrix_oop.h
LIBS = -lgtest -lgtest_main
OPEN = xdg-open

ifeq ($(shell uname -s), Darwin)
	OPEN=open
else
	LIBS+=-lm
	OPEN=xdg-open
endif

all: test

s21_matrix_oop.a: clean
	$(CC) $(CFLAG) -c s21_matrix_oop.cc -o 1.o
	$(CC) $(CFLAG) -c operator_and_help.cc -o 2.o
	ar rc s21_matrix_oop.a 1.o 2.o

test: s21_matrix_oop.a
	$(CC) $(CFLAG) -c tests.cc -o tests.o
	$(CC) $(CFLAG) tests.o s21_matrix_oop.a $(LIBS) -o tests
	./tests

gcov_report: clean
	@$(CC) $(CFLAG) -c --coverage s21_matrix_oop.cc -o 1.o
	@$(CC) $(CFLAG) -c --coverage operator_and_help.cc -o 2.o
	@$(CC) $(CFLAG) -c tests.cc -o tests.o
	@$(CC) $(CFLAG) tests.o 1.o 2.o --coverage $(LIBS) -o tests
	@./tests
	@gcovr -r . --html --html-details -o report.html
	@$(OPEN) report.html 2>/dev/null

style:
	clang-format -n --style=Google *.cc *.h

clean:
	rm -rf *.a *.o *.gcda *gcno *.html *.css tests
