#include <getopt.h>
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 4096

typedef struct {
  char patterns[10][50];
  char file_names[10][50];
  int count_patterns;
  int count_files;
  int e;
  int i;
  int v;
  int c;
  int l;
  int n;
  int h;
  int f;
  int s;
  int o;
  int pattern;
  int files_index;
  int arg_c;
  int v_match;
  int c_match;
  int l_match;
  int match_count;
} config;

int parse_params(int argc, char **argv, char *short_options, config *conf);
int print_n_files(int argc, char **argv, config *conf, regex_t *reegex);
int print_file(char *name, config *conf, regex_t *reegex);
int processing(config *conf, regex_t *reegex, char *name, int line_number,
               int last_line_number, char *line, int *exit_l, int *match,
               int *exit_c);
int print_files(config *conf, char *name, char *line, int line_number,
                int *last_line_number);
int file_processing(FILE *f, config *conf, regex_t *reegex, char *name,
                    int line_number);
void cat_string(char *line);
int regec(config *conf, char *line, char *line_file, regex_t *reegex,
          int *error);
int processing_flags(config *conf, char *line, int *exit_l, regex_t *reegex,
                     char *name, int *last_line_number, int line_number,
                     int match, int *exit_c);

int main(int argc, char *argv[]) {
  int error = 0;
  regex_t reegex;
  config conf = {{{""}}, {{""}}, 0, 0, 0, 0,    0, 0, 0, 0, 0,
                 0,      0,      0, 0, 0, argc, 0, 0, 0, 0};
  char *short_options = "e:iovclnhsf:";

  if (argc < 4) {
    error = 1;
  }

  if (!error) {
    error = parse_params(argc, argv, short_options, &conf);
  }

  if (!error) {
    error = print_n_files(argc, argv, &conf, &reegex);
  }

  if (error && conf.s == 0) printf("Что-то пошло нееее таааак");

  return error;
}

int parse_params(int argc, char **argv, char *short_options, config *conf) {
  int res;
  int error = 0;
  for (; optind + conf->files_index < argc;) {
    res = getopt(argc, argv, short_options);
    switch (res) {
      case 'e':
        conf->e = 1;
        strcat(conf->patterns[conf->count_patterns], optarg);
        (conf->count_patterns)++;
        break;
      case 'i':
        conf->i = 1;
        break;
      case 'v':
        conf->v = 1;
        break;
      case 'c':
        conf->c = 1;
        break;
      case 'l':
        conf->l = 1;
        break;
      case 'n':
        conf->n = 1;
        break;
      case 'h':
        conf->h = 1;
        break;
      case 's':
        conf->s = 1;
        break;
      case 'o':
        conf->o = 1;
        break;
      case 'f':
        conf->f = 1;
        strcat(conf->file_names[conf->count_files], optarg);
        (conf->count_files)++;
        break;
      case '?':
        error = 1;
        break;
      case -1:
        if (!conf->pattern && !conf->e) {
          strcat(conf->patterns[conf->count_patterns], argv[optind]);
          (conf->count_patterns)++;
          conf->pattern++;
          optind++;
        } else {
          (conf->files_index)++;
        }
        break;
      default:
        error = 1;
        break;
    }
  }

  return error;
}

int print_n_files(int argc, char **argv, config *conf, regex_t *reegex) {
  int error = 0;
  for (int i = optind; i < argc; i++) {
    if (!error)
      error = print_file(argv[i], conf, reegex);
    else
      break;
  }
  return error;
}

int print_file(char *name, config *conf, regex_t *reegex) {
  int error = 0;
  FILE *f = NULL;
  conf->l_match = 0;
  conf->match_count = 0;

  int line_number = 0;
  if (name)
    f = fopen(name, "r");
  else
    error = 1;
  if (f == NULL) error = 1;

  if (f != NULL && error != 1)
    error = file_processing(f, conf, reegex, name, line_number);

  if (f != NULL) fclose(f);
  if (conf->l_match > 0) printf("%s\n", name);
  return error;
}

int processing(config *conf, regex_t *reegex, char *name, int line_number,
               int last_line_number, char *line, int *exit_l, int *match,
               int *exit_c) {
  int error = 0;

  for (int i = 0; i < conf->count_patterns && (!(*exit_l) && !(*exit_c)); i++) {
    if (conf->v) {
      *match = regec(conf, line, conf->patterns[i], reegex, &error);
      if (*match) conf->v_match = 1;
    } else {
      *match = regec(conf, line, conf->patterns[i], reegex, &error);
    }
    error = processing_flags(conf, line, exit_l, reegex, name,
                             &last_line_number, line_number, *match, exit_c);
  }

  return error;
}

int file_processing(FILE *f, config *conf, regex_t *reegex, char *name,
                    int line_number) {
  int error = 0;
  FILE *pater = NULL;
  int last_line_number = 0;
  char line[MAX_LINE_LENGTH];
  int exit_l = 0;

  while (fgets(line, sizeof(line), f) && !exit_l) {
    int match = 0;
    char line_file[MAX_LINE_LENGTH];
    conf->c_match = 0;
    conf->v_match = 0;
    line_number++;
    int exit_c = 0;
    cat_string(line);

    for (int i = 0; i < conf->count_files && (!exit_l && !exit_c); i++) {
      pater = fopen(conf->file_names[i], "r");
      while (fgets(line_file, sizeof(line_file), pater) &&
             (!exit_l || !exit_c)) {
        cat_string(line_file);
        if (conf->v) {
          match = regec(conf, line, line_file, reegex, &error);
          if (match) conf->v_match = 1;
        } else {
          match = regec(conf, line, line_file, reegex, &error);
        }

        error =
            processing_flags(conf, line, &exit_l, reegex, name,
                             &last_line_number, line_number, match, &exit_c);
      }
      fclose(pater);
    }

    processing(conf, reegex, name, line_number, last_line_number, line, &exit_l,
               &match, &exit_c);

    if (conf->c && !conf->v_match && conf->v && !conf->l && !exit_c) {
      conf->match_count++;
      exit_c = 1;
    }
    if (conf->v && !conf->v_match && !conf->c && !conf->l) {
      conf->match_count =
          print_files(conf, name, line, line_number, &last_line_number);
    }
  }

  if (conf->c) print_files(conf, name, line, line_number, &last_line_number);
  if (conf->l && conf->match_count > 0) conf->l_match = 1;
  return error;
}

int print_files(config *conf, char *name, char *line, int line_number,
                int *last_line_number) {
  if (!conf->c) conf->match_count++;
  char name_p[50] = "";
  if (conf->files_index > 1 && conf->h != 1) {
    strcpy(name_p, name);
    strcat(name_p, ":");
  }

  if (conf->c) {
    printf("%s%d\n", name_p, conf->match_count);
  } else if (conf->n) {
    *last_line_number = line_number;
    printf("%s%d:%s\n", name_p, line_number, line);
  } else if (*last_line_number != line_number && !conf->c) {
    *last_line_number = line_number;
    printf("%s%s\n", name_p, line);
  }

  return conf->match_count;
}

int regec(config *conf, char *line, char *line_file, regex_t *reegex,
          int *error) {
  int match = 0;
  if (conf->i) {
    *error = regcomp(reegex, line_file, REG_ICASE);
    match = !(regexec(reegex, line, 0, NULL, REG_ICASE));
  } else {
    *error = regcomp(reegex, line_file, 0);
    match = !(regexec(reegex, line, 0, NULL, 0));
  }
  return match;
}

void cat_string(char *line) {
  size_t line_length = strlen(line);

  if (line[line_length - 1] == '\n') {
    line[line_length - 1] = '\0';
  }
}

int processing_flags(config *conf, char *line, int *exit_l, regex_t *reegex,
                     char *name, int *last_line_number, int line_number,
                     int match, int *exit_c) {
  int error = 0;

  if (match && conf->l && !conf->v) {
    conf->match_count++;
    *exit_l = 1;
  }

  if (conf->c && match && !conf->l && !conf->v) {
    conf->match_count++;
    *exit_c = 1;
  }
  if (!match && conf->l && conf->v && !(*exit_l)) {
    *exit_l = 1;
    conf->match_count++;
  }

  if (match && !conf->v && (!(*exit_l) && !(*exit_c) && !conf->n)) {
    conf->match_count =
        print_files(conf, name, line, line_number, last_line_number);
  }

  if (conf->n && match && !(*exit_c) && !conf->l && !conf->v) {
    conf->match_count =
        print_files(conf, name, line, line_number, last_line_number);
    *exit_c = 1;
  }

  regfree(reegex);
  return error;
}
