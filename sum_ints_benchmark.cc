#include "sum_ints.h"

#include <benchmark/benchmark.h>
#include <cstdint>
#include <thread>
#include <vector>

namespace holistic_multithreading_c {
namespace {

constexpr int64_t kStart = 1'000;
constexpr int64_t kEnd = 1'000'000'000;
constexpr int64_t kMultiplier = 1'000;

extern "C" {
Range *NewRange(long long from, long long to);
long long SingleThreadSum(Range *range);
long long MultithreadedSum(Range *range, long long thread_count);
}

void DoSomething() {}

std::vector<int64_t> CreateThreadCountRange() {
  int64_t max_thread_count = std::thread::hardware_concurrency();
  std::vector<int64_t> range;
  for (int64_t i = 2; i < max_thread_count; i = i * 2) {
    range.push_back(i);
  }
  range.push_back(max_thread_count);
  return range;
}

static void BM_SingleThreadSum(benchmark::State &state) {
  for (auto _ : state) {
    Range *range = NewRange(1, state.range(0));
    SingleThreadSum(range);
  }
}
// Register the function as a benchmark
BENCHMARK(BM_SingleThreadSum)
    ->RangeMultiplier(kMultiplier)
    ->Range(kStart, kEnd)
    ->UseRealTime();

static void BM_MultithreadedSum(benchmark::State &state) {
  for (auto _ : state) {
    Range *range = NewRange(1, state.range(0));
    MultithreadedSum(range, state.range(1));
  }
}
// Register the function as a benchmark
BENCHMARK(BM_MultithreadedSum)
    ->RangeMultiplier(kMultiplier)
    ->ArgsProduct({benchmark::CreateRange(kStart, kEnd, kMultiplier),
                   CreateThreadCountRange()})
    ->UseRealTime();

} // namespace
} // namespace holistic_multithreading_c

BENCHMARK_MAIN();
