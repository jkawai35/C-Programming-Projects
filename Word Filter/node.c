#include "node.h"
#include <stdio.h>
#include <stdlib.h>

// derived from stack overflow referenced in readme file
char *strdupl(char *str) {
  char *copy, *orig;
  int len = 0;
  while (str[len]) {
    len++;
  }
  copy = malloc(len + 1);
  orig = copy;
  while (*str) {
    *orig++ = *str++;
  }
  *orig = '\0';
  return copy;
}

Node *node_create(char *oldspeak, char *newspeak) {
  // create node and fill in fields
  Node *w = (Node *)malloc(sizeof(Node));
  if (w) {
    if (oldspeak == NULL && newspeak == NULL) {
      return w;
    }
    if (oldspeak != NULL && newspeak == NULL) {
      w->oldspeak = strdupl(oldspeak);
      w->newspeak = NULL;
      return w;
    }
    w->oldspeak = strdupl(oldspeak);
    w->newspeak = strdupl(newspeak);
    w->next = NULL;
  }
  return w;
}

void node_delete(Node **n) {
  // free oldspeak and newspeak
  // then free pointer
  if (*n) {
    free((*n)->newspeak);
    (*n)->newspeak = NULL;
    free((*n)->oldspeak);
    (*n)->oldspeak = NULL;
    free(*n);
    *n = NULL;
  }
  return;
}

void node_print(Node *n) {
  if (n->oldspeak != NULL && n->newspeak != NULL) {
    printf("%s -> %s\n", n->oldspeak, n->newspeak);
  }
  if (n->newspeak == NULL) {
    printf("%s\n", n->oldspeak);
  }
  return;
}
