#include "bf.h"
#include "bv.h"
#include "city.h"
#include "ht.h"
#include "ll.h"
#include "messages.h"
#include "node.h"
#include "parser.h"
#include <getopt.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define SETTINGS "ht:f:ms"

int strcomp(char *compare1, char *compare2);
char *strdupl(char *str);

int main(int argc, char **argv) {
  int opt = 0, stats_print = 0;
  bool mtf = false;
  uint32_t ht_size = 10000, bfr_size = 524288;
  uint32_t bf_keys, bf_hits, bf_misses, bf_examined, ht_keys, ht_hits,
      ht_misses, ht_examined;
  float bpm = 0.0, fp = 0.0, asl = 0.0, load = 0.0;

  while ((opt = getopt(argc, argv, SETTINGS)) != -1) {
    switch (opt) {
    case 'h': {
      // print program usage
      fprintf(stderr,
              "Usage: ./banhammer [options]\n"
              "  ./banhammer will read in words from stdin, identify any "
              "badspeak or old speak and output an\n"
              "  appropriate punishment message. The badspeak and oldspeak "
              "(with the newspeak translation)\n"
              "  that caused the punishment will be printed after the message. "
              "If statistics are enabled\n"
              "  punishment messages are suppressed and only statistics will "
              "be printed.\n"
              "    -t <ht_size>: Hash table size set to <ht_size>. (default: "
              "10000)\n"
              "    -f <bf_size>: Bloom filter size set to <bf_size>. (default "
              "2^19)\n"
              "    -s          : Enables the printing of statistics.\n"
              "    -m          : Enables move-to-front rule.\n"
              "    -h          : Display program synopsis and usage.\n");
      return 0;
      break;
    }
    case 't': {
      // size of hash table
      // check atoi
      ht_size = atoi(optarg);
      break;
    }
    case 'f': {
      // size of bloom filter
      bfr_size = atoi(optarg);
      break;
    }
    case 'm': {
      // move to front rule
      mtf = true;
      break;
    }
    case 's': {
      // print stats to stdout
      stats_print = 1;
      break;
    }
    default: {
      fprintf(stderr,
              "Usage: ./banhammer [options]\n"
              "  ./banhammer will read in words from stdin, identify any "
              "badspeak or old speak and output an\n"
              "  appropriate punishment message. The badspeak and oldspeak "
              "(with the newspeak translation)\n"
              "  that caused the punishment will be printed after the message. "
              "If statistics are enabled\n"
              "  punishment messages are suppressed and only statistics will "
              "be printed.\n"
              "    -t <ht_size>: Hash table size set to <ht_size>. (default: "
              "10000)\n"
              "    -f <bf_size>: Bloom filter size set to <bf_size>. (default "
              "2^19)\n"
              "    -s          : Enables the printing of statistics.\n"
              "    -m          : Enables move-to-front rule.\n"
              "    -h          : Display program synopsis and usage.\n");
      exit(1);
    }
    }
  }

  bool thoughtcrime = false, rightspeak = false;

  // create bloom filter and hash table
  BloomFilter *bf = bf_create(bfr_size);
  HashTable *ht = ht_create(ht_size, mtf);

  // create files and parser for badspeak and newspeak
  FILE *bad = fopen("badspeak.txt", "r");
  FILE *translation = fopen("newspeak.txt", "r");

  // create parser for bad speak and linked lists for
  // thoughtcrime words and goodspeak words
  Parser *bp = parser_create(bad);
  LinkedList *thoughtcrimel = ll_create(mtf);
  LinkedList *goodspeakl = ll_create(mtf);
  char *badword = (char *)malloc(sizeof(char) * 128);
  while (next_word(bp, badword)) {
    bf_insert(bf, badword);
    ht_insert(ht, badword, NULL);
  }

  free(badword);

  // read in oldspeak with translations
  char os[100], ns[100];
  while (fscanf(translation, "%s %s\n", os, ns) == 2) {
    bf_insert(bf, os);
    ht_insert(ht, os, ns);
  }

  Parser *p = parser_create(stdin);
  char *evidence = (char *)malloc(128 * sizeof(char));
  while (next_word(p, evidence)) {
    // if word is not in bloom filter, no other action
    // otherwise create test node and insert
    if (!bf_probe(bf, evidence)) {
      continue;
    }
    Node *test = ht_lookup(ht, evidence);
    if (test->newspeak == NULL) {
      thoughtcrime = true;
      ll_insert(thoughtcrimel, evidence, NULL);
    }
    if (test != NULL) {
      if (test->newspeak != NULL && test->newspeak != NULL) {
        rightspeak = true;
        ll_insert(goodspeakl, evidence, test->newspeak);
      }
    }
  }
  free(evidence);

  // print stats here
  // messages are not printed if stats are printed
  if (stats_print == 1) {
    bf_stats(bf, &bf_keys, &bf_hits, &bf_misses, &bf_examined);
    ht_stats(ht, &ht_keys, &ht_hits, &ht_misses, &ht_examined);

    load = (float)bf_count(bf) / bfr_size;

    if (ht_hits == 0) {
      fp = 0;
    } else {
      fp = (float)ht_misses / bf_hits;
    }

    if (ht_misses == 0 && ht_hits == 0) {
      asl = 0;
    } else {
      asl = (float)ht_examined / (ht_hits + ht_misses);
    }
    if (bf_misses == 0) {
      bpm = 0;
    } else {
      bpm = ((float)bf_examined - (5 * bf_hits)) / bf_misses;
    }

    // print stats
    printf("ht keys: %d\n", ht_keys);
    printf("ht hits: %d\n", ht_hits);
    printf("ht misses: %d\n", ht_misses);
    printf("ht probes: %d\n", ht_examined);
    printf("bf keys: %d\n", bf_keys);
    printf("bf hits: %d\n", bf_hits);
    printf("bf misses: %d\n", bf_misses);
    printf("bf bits examined: %d\n", bf_examined);
    printf("Bits examined per miss: %.6f\n", bpm);
    printf("False positives: %.6f\n", fp);
    printf("Average seek length: %.6f\n", asl);
    printf("Bloom filter load: %.6f\n", load);
    return 0;
  }

  // display message depending on user's words
  // messages for thoughtcrime, thoughtcrime and rightspeak, and rightspeak
  if (thoughtcrime && rightspeak) {
    printf("%s", mixspeak_message);
    // print good and bad words
    ll_print(thoughtcrimel);
    ll_print(goodspeakl);

    // delete objects
    ll_delete(&thoughtcrimel);
    ll_delete(&goodspeakl);
    ht_delete(&ht);
    bf_delete(&bf);
    parser_delete(&bp);
    parser_delete(&p);
    fclose(translation);
    return 0;
  }
  if (thoughtcrime && !rightspeak) {
    printf("%s", badspeak_message);
    // print transgressions
    ll_print(thoughtcrimel);

    ll_delete(&thoughtcrimel);
    ll_delete(&goodspeakl);
    ht_delete(&ht);
    bf_delete(&bf);
    parser_delete(&bp);
    parser_delete(&p);
    fclose(translation);
    return 0;
  }
  if (!thoughtcrime && rightspeak) {
    printf("%s", goodspeak_message);
    // print good words
    ll_print(goodspeakl);

    ll_delete(&thoughtcrimel);
    ll_delete(&goodspeakl);
    ht_delete(&ht);
    bf_delete(&bf);
    parser_delete(&bp);
    parser_delete(&p);
    fclose(translation);
    return 0;
  }
  ll_delete(&thoughtcrimel);
  ll_delete(&goodspeakl);
  ht_delete(&ht);
  bf_delete(&bf);
  parser_delete(&bp);
  parser_delete(&p);
  fclose(translation);
  return 0;
}
