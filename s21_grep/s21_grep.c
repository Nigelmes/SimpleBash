#include "s21_grep.h"

int main(int argc, char** argv) {
    flagi ff = {0};
    countArgvAfterFlags(argc, argv, &ff);
    int i = ff.args;
    if (!pars(argc, argv, &ff)) {
        while (i < argc) {
            if (ff.flag_f) {
                if (argv[i][0] != '-' && check_file(argv[i])) read_print(argv[i], &ff);
            } else if (argv[i][0] != '-') {
                read_print(argv[i], &ff);
            }
            i++;
        }
    }
    return 0;
}
int check_file(char* file) {
    FILE* file_ptr;
    file_ptr = fopen(file, "r");
    if (file_ptr == NULL) {
        return 0;
    }
    fclose(file_ptr);
    return 1;
}

int pars(int argc, char** argv, flagi* ff) {
    char ch;
    while ((ch = getopt(argc, argv, "e:ivclonhsf:")) != -1) {
        switch (ch) {
            case 'e':
                ff->flag_e = 1;
                strcpy(ff->pattxt[ff->_count++], optarg);
                break;
            case 'i':
                ff->flag_i = 1;
                break;
            case 'v':
                ff->flag_v = 1;
                break;
            case 'c':
                ff->flag_c = 1;
                break;
            case 'l':
                ff->flag_l = 1;
                break;
            case 'n':
                ff->flag_n = 1;
                break;
            case 'h':
                ff->flag_h = 1;
                ff->count_file = 0;
                break;
            case 's':
                ff->flag_s = 1;
                break;
            case 'f':
                ff->flag_f = 1;
                read_f_file(ff);
                break;
            case 'o':
                ff->flag_o = 1;
                break;
            case '?':
                fprintf(stderr,
                        "usage: grep [-abcDEFGHhIiJLlmnOoqRSsUVvwxZ] [-A num] [-B num] "
                        "[-C[num]]");
                return 1;
            default:
                break;
        }
    }
    for (int i = 1; i < argc; i++) {
        if (argv[i][0] != '-' && !ff->flag_f && !ff->flag_e) {
            strcpy(ff->pattxt[ff->_count++], argv[i]);
            break;
        }
    }
    return 0;
}

void no_flags(char* file) {
    FILE* file_tmp;
    file_tmp = fopen(file, "r");
    if (file_tmp != NULL) {
        int c;
        while ((c = fgetc(file_tmp)) != EOF) printf("%c", c);
        fclose(file_tmp);
    }
}

int read_f_file(flagi* ff) {
    FILE* file_tmp;
    size_t len;
    char* line = NULL;
    file_tmp = fopen(optarg, "r");
    if (file_tmp != NULL) {
        while ((getline(&line, &len, file_tmp)) != EOF) {
            if (line[0] == '\n') ff->eol = 1;
            if (line[strlen(line) - 1] == '\n') line[strlen(line) - 1] = '\0';
            strcpy(ff->pattxt[ff->_count++], line);
        }
        if (line) free(line);
        fclose(file_tmp);
    } else {
        return 0;
    }
    return 1;
}

void countArgvAfterFlags(int argc, char** argv, flagi* ff) {
    int sch = 0, i = 0;
    if (argv[1][0] != '-')
        ff->args = i = 2;
    else
        ff->args = i = 3;
    while (i < argc) {
        sch++;
        i++;
    }
    ff->count_file = sch;
}

int read_print(char* file, flagi* ff) {
    if (ff->eol) {
        no_flags(file);
        return 1;
    }
    int dot = ff->count_file;
    if (ff->flag_l) {
        ff->flag_n = 0;
        ff->flag_o = 0;
    }
    if (ff->flag_c) {
        ff->flag_n = 0;
        ff->flag_o = 0;
    }
    if (ff->flag_v) ff->flag_o = 0;
    FILE* file_ptr;
    file_ptr = fopen(file, "r");
    size_t len = 0;
    regex_t regex;
    regmatch_t math[1];
    char* line = NULL;
    if (file_ptr != NULL) {
        int count_n = 0, count_c = 0;
        while ((getline(&line, &len, file_ptr)) != -1) {
            count_n++;
            int contex = 0;
            for (int k = 0; k < ff->_count; k++) {
                int err;
                int rite = regcomp(&regex, ff->pattxt[k], (ff->flag_i) ? REG_ICASE : 0);
                ff->rite = rite;
                if ((err = regexec(&regex, line, 0, NULL, 0)) == ff->flag_v) {
                    if (line[strlen(line) - 1] == '\n') line[strlen(line) - 1] = '\0';
                    count_c++;
                    contex = 1;
                }
                regfree(&regex);
            }
            if ((!ff->flag_c && !ff->flag_l) && contex) {
                if (dot > 1) printf("%s:", file);
                if (ff->flag_n) printf("%d:", count_n);
                if (ff->flag_o) {
                    char* buff = line;
                    for (int l = 0; l < ff->_count; l++) {
                        regcomp(&regex, ff->pattxt[l], (ff->flag_i) ? REG_ICASE : 0);
                        while ((regexec(&regex, buff, 1, math, 0)) == 0) {
                            for (int x = (int)math[0].rm_so; x < (int)math[0].rm_eo; x++) {
                                printf("%c", buff[x]);
                            }
                            buff += (int)math[0].rm_eo;
                            printf("\n");
                            regfree(&regex);
                        }
                    }
                } else {
                    printf("%s\n", line);
                }
            }
        }
        if (ff->flag_l && count_c) printf("%s\n", file);
        if (ff->flag_c && dot > 1)
            printf("%s:%d\n", file, count_c);
        else if (ff->flag_c && dot < 2)
            printf("%d\n", count_c);
        fclose(file_ptr);
        free(line);
    } else {
        if (!ff->flag_s) {
            fprintf(stderr, "s21_grep: %s: No such file or directory\n", file);
        }
    }
    return 0;
}
