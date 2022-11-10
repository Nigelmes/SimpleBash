#include "s21_cat.h"

int main(int argc, char *argv[]) {
    flagi ff = {0};
    int err = 0;
    if (argc > 1) {
        parser_flagov(&err, argc, argv, &ff);
        if (err == 0) text_editor(&err, argc, argv, &ff);
    }
    return err;
}

void parser_flagov(int *err, int argc, char *argv[], flagi *ff) {
    int i;
    for (i = 1; i < argc; i++) {
        int j = 1;
        if (argv[i][0] == '-' && argv[i][1] != '-' && (i < check_file(argc, argv))) {
            while (argv[i][j] != '\0') {
                switch (argv[i][j]) {
                    case 'b':
                        ff->flag_b = 1;
                        break;
                    case 'e':
                        ff->flag_v = 1;
                        ff->flag_e = 1;
                        break;
                    case 'E':
                        ff->flag_e = 1;
                        break;
                    case 'n':
                        ff->flag_n = 1;
                        break;
                    case 's':
                        ff->flag_s = 1;
                        break;
                    case 'T':
                        ff->flag_t = 1;
                        break;
                    case 't':
                        ff->flag_v = 1;
                        ff->flag_t = 1;
                        break;
                    case 'v':
                        ff->flag_v = 1;
                        break;
                    default:
                        fprintf(stderr,
                                "s21_cat: illegal option -- %c\nusage: cat [-benstuv] [file "
                                "...]\n",
                                argv[i][j]);
                        *err = 1;
                }
                j++;
            }
        } else if (argv[i][0] == '-' && argv[i][1] == '-') {
            parser_dlinnih_flagov(err, i, j, argv, ff);
        }
    }
    if (ff->flag_b && ff->flag_n) ff->flag_n = 0;
}
void parser_dlinnih_flagov(int *err, int f, int l, char *argv[], flagi *ff) {
    if (strcmp("--number-nonblank", argv[f]) == 0) {
        ff->flag_b = 1;
    } else if (strcmp("--number", argv[f]) == 0) {
        ff->flag_n = 1;
    } else if (strcmp("--squeeze-blank", argv[f]) == 0) {
        ff->flag_s = 1;
    } else {
        fprintf(stderr, "s21_cat: illegal option -- %c\nusage: cat [-benstuv] [file ...]\n", argv[f][l]);
        *err = 1;
    }
}

void text_editor(int *err, int argc, char *argv[], flagi *ff) {
    FILE *file;
    for (int i = 1; i < argc; i++) {
        if ((argv[i][0] != '-')) {
            file = fopen(argv[i], "r");
            if (file == NULL) {
                fprintf(stderr, "s21_cat: %s: No such file or directory\n", argv[i]);
                *err = 1;
            } else {
                int a = '\n', empty = 0;
                int kb, count = 1;
                while ((kb = fgetc(file)) != EOF) {
                    if (ff->flag_b && kb != '\n' && a == '\n') printf("%6d\t", count++);
                    if (ff->flag_n && a == '\n') printf("%6d\t", count++);
                    if (ff->flag_e && kb == '\n') printf("$");
                    if (ff->flag_t && kb == '\t') {
                        kb = '^';
                        putchar(kb);
                        kb = 'I';
                    }
                    if (ff->flag_s && kb == '\n' && a == '\n') {
                        empty++;
                        if (empty > 1) continue;
                    } else {
                        empty = 0;
                    }
                    if (ff->flag_v && kb != '\n') {
                        if ((kb >= 0 && kb < 9) || (kb > 10 && kb <= 31)) {
                            kb += 64;
                            printf("^");
                        } else if (kb == 127) {
                            kb -= 64;
                            printf("^");
                        }
                    }
                    putchar(kb);
                    a = kb;
                }
                fclose(file);
            }
        }
    }
}
int check_file(int argc, char *argv[]) {
    FILE *kk;
    for (int i = 1; i < argc; i++) {
        if ((argv[i][0] != '-')) {
            if ((kk = fopen(argv[i], "r"))) {
                fclose(kk);
                return i;
            }
        }
    }
    return 1;
}
