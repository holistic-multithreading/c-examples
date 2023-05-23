#ifndef HOLISTIC_MULTITHREADING_CODE_SAMPLES_C_THREAD_SUM_SUM_INTS_H_
#define HOLISTIC_MULTITHREADING_CODE_SAMPLES_C_THREAD_SUM_SUM_INTS_H_

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

typedef struct Range Range;

Range *NewRange(long long from, long long to);

long long SingleThreadSum(Range *range);

long long MultithreadedSum(Range *range, long long thread_count);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // HOLISTIC_MULTITHREADING_CODE_SAMPLES_C_THREAD_SUM_SUM_INTS_H_
