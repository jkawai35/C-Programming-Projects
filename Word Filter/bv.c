#include "bv.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

struct BitVector {
  uint32_t length;
  uint64_t *vector;
};

BitVector *bv_create(uint32_t length) {
  BitVector *bv = (BitVector *)malloc(sizeof(BitVector));
  if (bv != NULL) {
    uint64_t *vector = (uint64_t *)calloc(length, sizeof(uint64_t));
    bv->length = length;
    bv->vector = vector;
  }
  return bv;
}

void bv_print(BitVector *bv) {
  for (uint32_t i = 0; i < bv->length; i++) {
    printf("%d", bv_get_bit(bv, i));
  }
  printf("\n");
  return;
}

void bv_delete(BitVector **bv) {
  free((*bv)->vector);
  *bv = NULL;
}

uint32_t bv_length(BitVector *bv) { return bv->length; }

void bv_set_bit(BitVector *bv, uint32_t i) {
  uint32_t index, position;
  index = i / 64;
  position = i % 64;
  bv->vector[index] |= (1UL << position);
  return;
}

void bv_clr_bit(BitVector *bv, uint32_t i) {
  uint32_t index, position;
  index = i / 64;
  position = i % 64;
  bv->vector[index] &= ~(1UL << position);
  return;
}

uint8_t bv_get_bit(BitVector *bv, uint32_t i) {
  return bv->vector[(i / 64)] >> (i % 64) & 1UL;
}

// int main()
//{
//	BitVector *vector = bv_create(64);
//	bv_set_bit(vector, 10);
//	bv_print(vector);
// }
