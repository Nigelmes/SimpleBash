#ifndef SRC_S21_GREP_H_
#define SRC_S21_GREP_H_

#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

typedef struct {
  int flag_e;
  int flag_v;
  int flag_i;
  int flag_n;
  int flag_c;
  int flag_l;
  int flag_h;
  int flag_s;
  int flag_o;
  int flag_f;
  int eol;
  int rite;
  int args;
  int _count;
  int count_file;
  char pattxt[1024][1024];
} flagi;

int read_print(char* file, flagi* ff);
int pars(int argc, char** argv, flagi* ff);
void countArgvAfterFlags(int argc, char** argv, flagi* ff);
int read_f_file(flagi* ff);
void no_flags(char* file);
int check_file(char* file);

#endif  // SRC_S21_GREP_H_
