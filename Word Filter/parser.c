#include "parser.h"
#include <ctype.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int strcomp(char *compare1, char *compare2);
char *strdupl(char *str);

struct Parser {
  FILE *f;
  char current_line[MAX_PARSER_LINE_LENGTH + 1];
  uint32_t line_offset;
};

Parser *parser_create(FILE *f) {
  Parser *p = (Parser *)malloc(sizeof(Parser));
  if (p) {
    p->f = f;
    p->line_offset = 0;
    p->current_line[0] = '\n';
    return p;
  }
  return p;
}

void parser_delete(Parser **p) {
  if (*p) {
    fclose((*p)->f);
    free(*p);
    *p = NULL;
  }
}

bool next_word(Parser *p, char *word) {
  uint32_t orig = 0, word_index = 0;
  orig = p->line_offset;

  // check for spaces before word as well as new line
  while (p->current_line[p->line_offset] == '\n') {
    if (fgets(p->current_line, MAX_PARSER_LINE_LENGTH + 1, p->f) == NULL) {
      return false;
    }
    p->line_offset = 0;
    while (isalnum(p->current_line[p->line_offset]) == 0 &&
           p->current_line[p->line_offset] != 39 &&
           p->current_line[p->line_offset] != '-' &&
           p->current_line[p->line_offset] != '\n') {
      p->line_offset += 1;
    }
  }

  // check for valid characters and add to word that is saved
  while (isalnum(p->current_line[p->line_offset]) ||
         p->current_line[p->line_offset] == 39 ||
         p->current_line[p->line_offset] == '-') {
    word[word_index] = tolower(p->current_line[p->line_offset]);
    p->line_offset += 1;
    orig++;
    word_index++;
  }
  word[word_index] = '\0';

  // check for spaces after the word or any invalid characters
  while (isalnum(p->current_line[p->line_offset]) == 0 &&
         p->current_line[p->line_offset] != 39 &&
         p->current_line[p->line_offset] != '-' &&
         p->current_line[p->line_offset] != '\n') {
    p->line_offset += 1;
  }
  return true;
}
