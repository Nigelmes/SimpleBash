CC = gcc
FLAGS = -Wextra -Werror -Wall -std=c11 -D_GNU_SOURCE
MM = s21_grep.c
ZZ = -o s21_grep
GTEST = s21_grep_test.sh

all: s21_grep

s21_grep:
	$(CC) $(FLAGS) $(MM) $(ZZ)

test: s21_grep
	chmod -x $(GTEST)
	bash $(GTEST)

sstest:
	cp ../../materials/linters/CPPLINT.cfg ./
	python3 ../../materials/linters/cpplint.py --extensions=c *.c
	cppcheck --enable=all --suppress=missingIncludeSystem *.c *.h
clean:
	rm -rf s21_grep *.cfg *.o
