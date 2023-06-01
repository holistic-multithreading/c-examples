sum_ints_lib = libsum_ints.a
main_binary = sum_ints_main.out
benchmark = sum_ints_benchmark.out
c_standard = c17
cpp_standard = c++17
benchmark_stats_base_name=c_benchmark_stats_$(shell date +"%Y%m%d_%H%M%S")
benchmark_stats=$(benchmark_stats_base_name).csv
benchmark_aggregates=$(benchmark_stats_base_name)_aggregates.dat
CC = clang
CXX = clang++

run_benchmark: $(benchmark)
	./$(benchmark) --benchmark_time_unit=us

stats: $(benchmark)
	echo "Running benchmarks to get statistics. This might take more than 30 minutes..."
	./$(benchmark) --benchmark_time_unit=us \
		--benchmark_repetitions=100 \
		--benchmark_enable_random_interleaving \
		--benchmark_display_aggregates_only \
		--benchmark_out_format=csv \
		--benchmark_out=./$(benchmark_stats) &> $(benchmark_aggregates) &
	tail -f $(benchmark_aggregates)

run_main: $(main_binary)
	./$(main_binary)

$(main_binary): sum_ints_main.c $(sum_ints_lib)
	$(CC) sum_ints_main.c -std=$(c_standard) -L. -lsum_ints -pthread -O3 -o $(main_binary)

$(sum_ints_lib): sum_ints.h sum_ints.c
	$(CC) -c -O3 -std=$(c_standard) sum_ints.c
	ar rcs $(sum_ints_lib) sum_ints.o

$(benchmark): sum_ints_benchmark.cc $(sum_ints_lib)
	$(CXX) sum_ints_benchmark.cc -std=$(cpp_standard) -lbenchmark -L. -lsum_ints -pthread -O3 -o $(benchmark)

clean:
	rm -f *.a *.o *.s *.out
