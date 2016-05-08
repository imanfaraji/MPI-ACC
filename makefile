#CC=/home/farajii/builds/19-ompi-1.8.8/bin/mpicc
CC=/home/farajii/builds/23-ompi-1.10.2/bin/mpicc
CUDA_LIB=-L/usr/local/cuda/lib64/ -lcudart -lcuda
CUDA_INCLUDE=-I/usr/local/cuda/include/
APP_INCLUDE=-I./
MPI_INCLUDE=-I/home/farajii/builds/23-ompi-1.10.2/include/
#MPI_INCLUDE=-I/home/farajii/builds/19-ompi-1.8.8/include/
MPI_LIB=-L/home/farajii/builds/23-ompi-1.10.2/lib/ -lmpi 
#MPI_LIB=-L/home/farajii/builds/19-ompi-1.8.8/lib/ -lmpi 


all:
	$(CC) -c $(CUDA_INCLUDE) $(CUDA_LIB) $(MPI_INCLUDE) $(MPI_LIB) $(APP_INCLUDE) misc.c -o misc.o
	$(CC) -c $(CUDA_INCLUDE) $(CUDA_LIB) $(MPI_INCLUDE) $(MPI_LIB) $(APP_INCLUDE) read_bench.c -o ./read_bench.o
	$(CC) -c $(CUDA_INCLUDE) $(CUDA_LIB) $(MPI_INCLUDE) $(MPI_LIB) $(APP_INCLUDE) 2DSTENCIL_func.c -o ./2DSTENCIL_func.o
	$(CC) -c $(CUDA_INCLUDE) $(CUDA_LIB) $(MPI_INCLUDE) $(MPI_LIB) $(APP_INCLUDE) 3DTORUS_func.c -o ./3DTORUS_func.o
	$(CC) -c $(CUDA_INCLUDE) $(CUDA_LIB) $(MPI_INCLUDE) $(MPI_LIB) $(APP_INCLUDE) COLLSUBCOMM_func.c -o ./COLLSUBCOMM_func.o
	$(CC) -c $(CUDA_INCLUDE) $(CUDA_LIB) $(MPI_INCLUDE) $(MPI_LIB) $(APP_INCLUDE) run_bench.c -o ./run_bench.o
	$(CC) -c $(CUDA_INCLUDE) $(CUDA_LIB) $(MPI_INCLUDE) $(MPI_LIB) $(APP_INCLUDE) free_bench.c -o ./free_bench.o
	$(CC) -c $(CUDA_INCLUDE) $(CUDA_LIB) $(APP_INCLUDE) $(MPI_LIB) $(APP_INCLUDE) MICRO_BENCHMARK.c -o ./MICRO_BENCHMARK.o
	$(CC)  misc.o read_bench.o 2DSTENCIL_func.o 3DTORUS_func.o COLLSUBCOMM_func.o run_bench.o free_bench.o MICRO_BENCHMARK.o -o ./MICRO_BENCHMARK $(CUDA_INCLUDE) $(CUDA_LIB) $(APP_INCLUDE) $(MPI_LIB) $(APP_INCLUDE) 
clean:	
	rm -rf ./MICRO_BENCHMARK
