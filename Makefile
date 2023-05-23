sum_ints_lib = libsum_ints.a
benchmark = sum_ints_benchmark
c_standard = c17
cpp_standard = c++17

run_main: sum_ints_main
	./sum_ints_main

sum_ints_main: sum_ints_main.c $(sum_ints_lib)
	$(CC) sum_ints_main.c -std=$(c_standard) -L. -lsum_ints -lpthread -O3 -o sum_ints_main

$(sum_ints_lib): sum_ints.h sum_ints.c
	$(CC) -c -O3 -std=$(c_standard) sum_ints.c
	ar rcs $(sum_ints_lib) sum_ints.o

$(benchmark): sum_ints_benchmark.cc $(sum_ints_lib)
	$(CXX) sum_ints_benchmark.cc -std=$(cpp_standard) -lbenchmark -L. -lsum_ints -lpthread -O3 -o $(benchmark)

run_benchmark: $(benchmark)
	./sum_ints_benchmark --benchmark_time_unit=ms

static: sum_ints_main.c $(sum_ints_lib)
	$(CC) sum_ints_main.c -std=$(c_standard) -L. -lsum_ints -lpthread -O3 -o sum_ints_main_static

asm: sum_ints.cc
	$(CC) sum_ints.c -std=$(c_standard) -S

clean:
	rm -f *.a *.o *.s sum_ints_main sum_ints_main_static sum_ints_benchmark
