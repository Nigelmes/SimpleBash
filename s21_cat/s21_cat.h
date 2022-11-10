#ifndef SRC_S21_CAT_H_
#define SRC_S21_CAT_H_

#include <stdio.h>
#include <string.h>

typedef struct {
  int flag_b;
  int flag_e;
  int flag_n;
  int flag_s;
  int flag_t;
  int flag_v;
} flagi;

void parser_flagov(int *err, int argc, char *argv[], flagi *ff);
void parser_dlinnih_flagov(int *err, int f, int l, char *argv[], flagi *ff);
void text_editor(int *err, int argc, char *argv[], flagi *ff);
int check_file(int argc, char *argv[]);
#endif  // SRC_S21_CAT_H_
