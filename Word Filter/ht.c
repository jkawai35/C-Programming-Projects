#include "ht.h"
#include "city.h"
#include "ll.h"
#include "node.h"
#include <stdio.h>
#include <stdlib.h>

struct HashTable {
  uint64_t salt;
  uint32_t size;
  uint32_t n_keys;
  uint32_t n_hits;
  uint32_t n_misses;
  uint32_t n_examined;
  bool mtf;
  LinkedList **lists;
};

HashTable *ht_create(uint32_t size, bool mtf) {
  // create hash table and set fields
  HashTable *ht = (HashTable *)malloc(sizeof(HashTable));
  if (ht) {
    ht->mtf = mtf;
    ht->salt = 0x9846e4f157fe8840;
    ht->n_hits = ht->n_misses = ht->n_examined = 0;
    ht->n_keys = 0;
    ht->size = size;
    ht->lists = (LinkedList **)calloc(size, sizeof(LinkedList *));
    if (!ht->lists) {
      free(ht);
      ht = NULL;
    }
  }
  return ht;
}

void ht_delete(HashTable **ht) {
  // delete all linked lists and free pointer
  if (*ht) {
    uint32_t index = 0;
    while (index < ht_size(*ht)) {
      ll_delete(&(*ht)->lists[index]);
      index++;
    }
  }
  free((*ht)->lists);
  (*ht)->lists = NULL;
  free(*ht);
  *ht = NULL;
}
uint32_t ht_size(HashTable *ht) { return ht->size; }

Node *ht_lookup(HashTable *ht, char *oldspeak) {
  // check stats before accessing ll elements
  uint32_t ll_links, ll_seeks, ll_diff;
  ll_stats(&ll_seeks, &ll_links);

  // find index in hash table
  uint32_t index = hash(ht->salt, oldspeak) % ht->size;

  // check if oldspeak is in list at index
  Node *temp = ll_lookup(ht->lists[index], oldspeak);

  // if found node update stats and return node
  if (temp != NULL) {
    ht->n_hits += 1;
    ll_stats(&ll_seeks, &ll_diff);
    ht->n_examined += (ll_diff - ll_links);
    return temp;
  }

  // if not found update stats and return null node
  ht->n_misses += 1;
  ll_stats(&ll_diff, &ll_seeks);
  ht->n_examined += (ll_diff - ll_links);
  return temp;
}

void ht_insert(HashTable *ht, char *oldspeak, char *newspeak) {
  // find index
  uint32_t index = hash(ht->salt, oldspeak) % ht->size;

  // check if a linked list was already created at index
  // otherwise, create new ll and insert
  if (ht->lists[index] == NULL) {
    ht->lists[index] = ll_create(ht->mtf);
    ll_insert(ht->lists[index], oldspeak, newspeak);
    ht->n_keys += 1;
    return;
  }
  if (ll_lookup(ht->lists[index], oldspeak) == NULL) {
    ht->n_keys += 1;
    ll_insert(ht->lists[index], oldspeak, newspeak);
    return;
  }
  return;
}

uint32_t ht_count(HashTable *ht) {
  // loop over ht and add to count for every linked list found
  uint32_t count = 0;
  for (uint32_t i = 0; i < ht->size; i++) {
    if (ht->lists[i] != NULL) {
      count++;
    }
  }
  return count;
}

void ht_print(HashTable *ht) {
  if (ht) {
    for (uint32_t i = 0; i < ht->size; i++) {
      if (ht->lists[i] != NULL) {
        ll_print(ht->lists[i]);
      }
    }
    return;
  }
  return;
}

void ht_stats(HashTable *ht, uint32_t *nk, uint32_t *nh, uint32_t *nm,
              uint32_t *ne) {
  *nk = ht->n_keys;
  *nh = ht->n_hits;
  *nm = ht->n_misses;
  *ne = ht->n_examined;
  return;
}
