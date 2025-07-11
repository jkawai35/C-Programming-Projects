#include "bf.h"
#include "bv.h"
#include "city.h"
#include <stdio.h>
#include <stdlib.h>
#define N_HASHES 5

struct BloomFilter {
  uint64_t salts[N_HASHES];
  uint32_t n_keys;
  uint32_t n_hits;
  uint32_t n_misses;
  uint32_t n_bits_examined;
  BitVector *filter;
};

static uint64_t default_salts[] = {0x5adf08ae86d36f21, 0x419d292ea2ffd49e,
                                   0x50d8bb08de3818df, 0x272347aea4045dd5,
                                   0x7c8e16f768811a21};

BloomFilter *bf_create(uint32_t size) {
  // create bloom filter and set fields
  BloomFilter *bf = (BloomFilter *)malloc(sizeof(BloomFilter));
  if (bf) {
    bf->n_keys = bf->n_hits = 0;
    bf->n_misses = bf->n_bits_examined = 0;
    for (uint32_t i = 0; i < N_HASHES; i++) {
      bf->salts[i] = default_salts[i];
    }
    bf->filter = bv_create(size);
    if (bf->filter == NULL) {
      free(bf);
      bf = NULL;
    }
  }
  return bf;
}

void bf_delete(BloomFilter **bf) {
  // delete bit vector and free pointer
  if (*bf) {
    bv_delete(&(*bf)->filter);
  }
  free(*bf);
  *bf = NULL;
}

uint32_t bf_size(BloomFilter *bf) { return bv_length(bf->filter); }

void bf_insert(BloomFilter *bf, char *oldspeak) {
  // hash oldspeak with each salt and set bit
  for (int i = 0; i < 5; i++) {
    uint32_t index = (hash(bf->salts[i], oldspeak)) % bv_length(bf->filter);
    bv_set_bit(bf->filter, index);
  }
  bf->n_keys += 1;
  return;
}

bool bf_probe(BloomFilter *bf, char *oldspeak) {
  // hash oldspeak for each salt and check if bit is set at index
  for (int i = 0; i < 5; i++) {
    uint32_t index = (hash(bf->salts[i], oldspeak)) % bv_length(bf->filter);
    if (bv_get_bit(bf->filter, index) == 0) {
      bf->n_bits_examined += 1;
      bf->n_misses += 1;
      return false;
    }
    bf->n_bits_examined += 1;
  }
  bf->n_hits += 1;
  return true;
}

uint32_t bf_count(BloomFilter *bf) {
  uint32_t count = 0;
  for (uint32_t i = 0; i < bv_length(bf->filter); i++) {
    if (bv_get_bit(bf->filter, i) == 1) {
      count++;
      bf->n_keys += 1;
    }
  }
  return count;
}

void bf_print(BloomFilter *bf) { bv_print(bf->filter); }

void bf_stats(BloomFilter *bf, uint32_t *nk, uint32_t *nh, uint32_t *nm,
              uint32_t *ne) {
  *nk = bf->n_keys;
  *nh = bf->n_hits;
  *nm = bf->n_misses;
  *ne = bf->n_bits_examined;
  return;
}
