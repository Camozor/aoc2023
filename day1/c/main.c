#include "main.h"

typedef struct {
  char nb;
  char *str;
} Digit;

Digit digits[] = {{'1', "one"},   {'2', "two"},   {'3', "three"},
                  {'4', "four"},  {'5', "five"},  {'6', "six"},
                  {'7', "seven"}, {'8', "eight"}, {'9', "nine"}};

int main() {
  FILE *fp;
  char *line = NULL;
  size_t len = 0;

  fp = fopen("input.txt", "r");
  if (fp == NULL)
    exit(EXIT_FAILURE);

  int sum = 0;
  while (getline(&line, &len, fp) != -1) {
    int found_number = find_line_number(line);
    sum += found_number;
  }

  printf("Result: %d\n", sum);
  fclose(fp);

  return EXIT_SUCCESS;
}

const char NOT_SET = '*';
int find_line_number(char *line) {
  char left_most = NOT_SET;
  char right_most = NOT_SET;
  int len = strlen(line);

  for (int pos = 0; pos < len; ++pos) {
    if (left_most == NOT_SET) {
      left_most = get_number(line, pos);
      if (left_most != NOT_SET && right_most != NOT_SET) {
        break;
      }
    }
    if (right_most == NOT_SET) {
      right_most = get_number(line, len - pos - 1);
      if (left_most != NOT_SET && right_most != NOT_SET) {
        break;
      }
    }
  }

  char *line_number_str = (char *)malloc(3 * sizeof(char));
  line_number_str[0] = left_most;
  line_number_str[1] = right_most;
  line_number_str[2] = '\0';

  return atoi(line_number_str);
}

char get_number(char *line, int pos) {
  char found_number = NOT_SET;

  if (is_digit(line[pos])) {
    found_number = line[pos];
  } else {
    found_number = is_str_digit(line, strlen(line), pos);
  }

  return found_number;
}

bool is_digit(char c) { return c >= '0' && c <= '9'; }

char is_str_digit(char *line, int len, int pos) {
  for (int i = 0; i < 9; ++i) {
    Digit d = digits[i];
    if (pos + strlen(d.str) <= len) {
      int j = 0;
      while (j < strlen(d.str)) {
        if (line[pos + j] != d.str[j]) {
          break;
        }
        j++;
      }
      if (j < strlen(d.str)) {
        continue;
      }

      return d.nb;
    }
  }

  return NOT_SET;
}
