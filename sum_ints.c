#include "sum_ints.h"

#include <pthread.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

struct Range {
  long long from;
  long long to;
};

Range *NewRange(long long from, long long to) {
  Range *range = malloc(sizeof(Range));
  *range = (Range){from, to};
  return range;
}

void *SumValues(void *arg) {
  Range *range = (Range *)arg;
  long long *result = malloc(sizeof(long long));
  *result = 0;
  for (long long i = range->from; i <= range->to; i++) {
    *result += i % 10;
  }
  return result;
}

long long SingleThreadSum(Range *range) {
  return *(long long *)SumValues(range);
}

long long MultithreadedSum(Range *range, long long thread_count) {
  pthread_t tids[thread_count];
  Range ranges[thread_count];
  long long start = range->from;
  long long batch_size = (range->to - range->from + 1ll) / thread_count;
  for (int i = 0; i < thread_count; i++) {
    long long end = (i < thread_count - 1) ? start + batch_size - 1 : range->to;
    ranges[i] = (Range){start, end};
    pthread_create(&tids[i], NULL, SumValues, &ranges[i]);
    start = end + 1;
  }

  long long result = 0;
  void *partial_result;
  for (int i = 0; i < thread_count; i++) {
    pthread_join(tids[i], &partial_result);
    result += *(long long *)partial_result;
  }
  return result;
}
