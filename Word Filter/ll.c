#include "ll.h"
#include "city.h"
#include "node.h"
#include <stdio.h>
#include <stdlib.h>

int strcomp(char *compare1, char *compare2);
uint64_t links = 0, seeks = 0;
struct LinkedList {
  uint32_t length;
  Node *head;
  Node *tail;
  bool mtf;
};

LinkedList *ll_create(bool mtf) {
  LinkedList *ll = (LinkedList *)malloc(sizeof(LinkedList));
  if (ll) {
    ll->head = node_create(NULL, NULL);
    ll->tail = node_create(NULL, NULL);
    ll->head->next = ll->tail;
    ll->tail->prev = ll->head;
    ll->head->prev = NULL;
    ll->tail->next = NULL;
    ll->mtf = mtf;
    ll->length = 0;
  }
  return ll;
}

void ll_delete(LinkedList **ll) {
  // delete all nodes in linked list
  if (*ll) {
    while ((*ll)->head != NULL) {
      Node *next = NULL;
      next = ((*ll)->head->next);
      node_delete(&(*ll)->head);
      (*ll)->head = next;
    }
  }
  free(*ll);
  *ll = NULL;
  return;
}

uint32_t ll_length(LinkedList *ll) { return ll->length; }

Node *ll_lookup(LinkedList *ll, char *oldspeak) {
  seeks++;
  for (Node *curr = ll->head->next; curr != ll->tail; curr = curr->next) {
    links++;

    // check if oldspeak at curr is equal to oldspeak in question
    if (strcomp(curr->oldspeak, oldspeak) == 0) {
      if (curr->prev != ll->head) {
        if (ll->mtf) {
          curr->prev->next = curr->next;
          curr->next->prev = curr->prev;

          curr->next = ll->head->next;
          curr->prev = ll->head;

          ll->head->next->prev = curr;
          ll->head->next = curr;
          return curr;
        }
      }
      return curr;
    }
  }
  return NULL;
}

// strcomp derived from reference mentioned in README
int strcomp(char *compare1, char *compare2) {
  while (*compare1 != '\0' && *compare2 != '\0') {
    if (*compare1 != *compare2) {
      return 1;
    }
    compare1++;
    compare2++;
  }
  if (*compare1 != '\0' || *compare2 != '\0') {
    return 1;
  }
  return 0;
}

void ll_insert(LinkedList *ll, char *oldspeak, char *newspeak) {
  // check if oldspeak is already in linked list
  if (ll_lookup(ll, oldspeak) == NULL) {
    // make new node and add
    Node *addnode = node_create(oldspeak, newspeak);
    addnode->next = ll->head->next;
    addnode->prev = ll->head;
    ll->head->next->prev = addnode;
    ll->head->next = addnode;
    ll->length += 1;
  }
  return;
}

void ll_print(LinkedList *ll) {
  if (ll) {
    for (Node *curr = ll->head->next; curr != ll->tail; curr = curr->next) {
      node_print(curr);
    }
  }
  return;
}

void ll_stats(uint32_t *n_seeks, uint32_t *n_links) {
  *n_seeks = seeks;
  *n_links = links;
  return;
}
