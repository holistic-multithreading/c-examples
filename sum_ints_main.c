#include "sum_ints.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char *argv[]) {
  Range *range = NewRange(1, 1000000000);
  printf("Simgle Thread Sum: %lld\n", SingleThreadSum(range));

  struct timespec start_time;
  struct timespec end_time;
  timespec_get(&start_time, TIME_UTC);
  long long result = MultithreadedSum(range, 10ll);
  timespec_get(&end_time, TIME_UTC);
  printf("Multithreaded Sum: %lld\n", result);
  printf("Time taken: %ld ns or %f ms\n",
         (end_time.tv_nsec - start_time.tv_nsec),
         (end_time.tv_nsec - start_time.tv_nsec) / 1000000.0);
  return EXIT_SUCCESS;
}
