#include <getopt.h>
#include <stdio.h>
#include <string.h>

typedef struct {
  int b;
  int e;
  int n;
  int s;
  int t;
  int v;
} config;

int parse_params(int argc, char **argv, char *short_options,
                 struct option long_options[], config *conf);
int print_file(char *name, config *conf);
void print_symb(int c, int *prev, config *conf, int *index, int *out_line);
int print_n_files(int argc, char **argv, config *conf);

int main(int argc, char **argv) {
  int error = 0;
  config conf = {0};

  char *short_options = "beEnstTv";
  struct option long_options[] = {{"number-nonblank", no_argument, NULL, 'b'},
                                  {"number", no_argument, NULL, 'n'},
                                  {"squeeze-blank", no_argument, NULL, 's'}};

  error = parse_params(argc, argv, short_options, long_options, &conf);

  if (!error) {
    error = print_n_files(argc, argv, &conf);
  }

  if (error) printf("Что-то пошло нееее таааак");

  return error;
}

int parse_params(int argc, char **argv, char *short_options,
                 struct option long_options[], config *conf) {
  int res;
  int error = 0;
  int idx = 0;

  while ((res = getopt_long(argc, argv, short_options, long_options, &idx)) !=
         -1) {
    switch (res) {
      case 'b':
        conf->b = 1;
        break;
      case 'e':
        conf->e = 1;
        conf->v = 1;
        break;
      case 'E':
        conf->e = 1;
        break;
      case 'n':
        conf->n = 1;
        break;
      case 's':
        conf->s = 1;
        break;
      case 't':
        conf->t = 1;
        conf->v = 1;
        break;
      case 'T':
        conf->t = 1;
        break;
      case 'v':
        conf->v = 1;
        break;
      case '?':
        error = 1;
        break;
      default:
        error = 1;
        break;
    }
  }
  return error;
}

int print_file(char *name, config *conf) {
  int error = 0;
  FILE *f = NULL;
  if (name != NULL) {
    f = fopen(name, "rt");
  } else {
    error = 1;
  }

  if (f != NULL && !error) {
    int index = 0, prev = '\n', c = fgetc(f), out_line = 0;
    while (c != EOF) {
      print_symb(c, &prev, conf, &index, &out_line);
      c = fgetc(f);
    }
    fclose(f);
  } else {
    error = 1;
  }
  return error;
}

void print_symb(int c, int *prev, config *conf, int *index, int *out_line) {
  if (!(conf->s != 0 && *prev == '\n' && c == '\n' && *out_line)) {
    if (*prev == '\n' && c == '\n')
      *out_line = 1;
    else
      *out_line = 0;

    if (((conf->n != 0 && conf->b == 0) || (conf->b != 0 && c != '\n')) &&
        *prev == '\n') {
      *index += 1;
      printf("%6d\t", *index);
    }

    if (conf->e != 0 && c == '\n') printf("$");

    if (conf->t != 0 && c == '\t') {
      printf("^");
      c = '\t' + 64;
    }

    if (conf->v != 0) {
      if (c > 127 && c < 160) printf("M-^");
      if ((c < 32 && c != '\n' && c != '\t') || c == 127) printf("^");
      if ((c < 32 || (c > 126 && c < 160)) && c != '\n' && c != '\t')
        c = c > 126 ? c - 128 + 64 : c + 64;
    }
    fputc(c, stdout);
  }
  *prev = c;
}

int print_n_files(int argc, char **argv, config *conf) {
  int error = 0;
  for (int i = optind; i < argc; i++) {
    if (!error)
      error = print_file(argv[i], conf);
    else
      break;
  }

  return error;
}
