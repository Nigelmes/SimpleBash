CC = gcc
FLAGS = -Wextra -Werror -Wall -std=c11 -D_GNU_SOURCE
MM = s21_cat.c
ZZ = -o s21_cat
GTEST = s21_cat_test.sh

all: s21_cat

s21_cat:
	$(CC) $(FLAGS) $(MM) $(ZZ)

test: s21_cat
	chmod -x $(GTEST)
	bash $(GTEST)

sstest:
	cp ../../materials/linters/CPPLINT.cfg ./
	python3 ../../materials/linters/cpplint.py --extensions=c *.c
	cppcheck --enable=all --suppress=missingIncludeSystem *.c *.h
clean:
	rm -rf s21_cat
