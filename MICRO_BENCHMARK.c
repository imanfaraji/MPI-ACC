/***********************************************************************************
 * This micro-benchmark set allows multiple communication patterns to run concurrently
 * on the CPU and/or the GPU buffer. Current benchmarks in this set includes:
 *
 *  - 2D-5point Stencil
 *  - 3D Torus
 *  - Alltoall on a subcommunicator
 *
 **Use -h with the microbenchmark executable for usage.
 *enable __IMI_DEBUG_ALL__ macro for debugging purpose
 **********************************************************************************/


#define __GLOBAL_VAR__ //used to define external variable in this source code scope
#include "MICRO_BENCHMARK.h"

int main(int argc, char ** argv)
{
	MPI_Init(&argc, &argv);
    int my_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

    //Default Device ID Selection --> DEV_ID = RanK_ID
    int dev_count = -1;
    cudaGetDeviceCount(&dev_count);
	cudaSetDevice(my_rank % dev_count);

	//custom Device Selection
	//TODO Read Device ID from a file  --> DEV_ID = GPU_ID_FILE[RANK_ID]

    if (my_rank == 0) 	//printing out help message
    {
        if (argc == 2 && !strcmp(argv[1],"-h"))
        {
           print_usage();
           return 0;
        }
    }
    
    //Read and initialize general variables
    int num_procs, ITER, SKIP;
    read_init(&num_procs, &ITER, &SKIP, argc, argv);

#ifdef __IMI_DEBUG_ALL__
    if (my_rank == 0) printf("num_procs %d, ITER %d, SKIP %d\n", num_procs, ITER, SKIP);
#endif

    //Read and store all benchmarks from the command line
    int bench_count = 0;
    benchmark bench[__MAX_BENCH__];
    bench_count = read_bench(bench, argc, argv);

//TEST--------------------------------PRINTIING---------
#ifdef __IMI_DEBUG_ALL__
    if (my_rank == 0)
    {
		int c;
		for (c = 0; c != bench_count; c++)
			printf("bench[%d].name = %s -- bench[%d].type = %s -- bench[%d].size = %d -- bench[%d].dim_x = %d -- bench[%d].dim_y = %d -- bench[%d].dim_z = %d\n",
					c, bench[c].name, c, bench[c].type, c, bench[c].size, c, bench[c].dim_x, c, bench[c].dim_y, c, bench[c].dim_z);
    }
#endif

    int iter_c = 0, j;
	double start_time, end_time;
	//nullify all the MPI requests
	req_coll = MPI_REQUEST_NULL;
	for(j = 0; j < req_count; j++) req[j] = MPI_REQUEST_NULL;
//******************************************************MAIN BODY STARTS******************************************************
    while (iter_c != SKIP + ITER)
    {
        if (iter_c == SKIP)
        	start_time = MPI_Wtime();//TIMING------------------------------STARTS
        req_count = 0;

		run_bench(my_rank, bench, bench_count);//run one iteration of all benchmarks

		MPI_Waitall(req_count, req, stat); //wait for completion of Isend/Irecv
		MPI_Wait(&req_coll, &stat_coll);   //wait for completion of the collective

		 //nullify all the MPI requests
		for(j = 0; j < req_count; j++)
		  if(req[j] != MPI_REQUEST_NULL)
			  MPI_Request_free(&req[j]);
		if(req_coll != MPI_REQUEST_NULL)
			 MPI_Request_free(&req_coll);

		iter_c++;
    }
    MPI_Barrier(MPI_COMM_WORLD);
	end_time = MPI_Wtime();

	if(my_rank == 0)
	{
	    printf("Total communication time = %lf us\n", (end_time - start_time)*1e6);
	    printf("Single iteration average communication time = %lf us\n", ((end_time - start_time)/ITER)*1e6);
	}
    //end TIMING------------------------------------------------------ENDS
////******************************************************MAIN BODY ENDS******************************************************

    //cleanup benchmark allocations
    free_bench(bench, bench_count);

    MPI_Finalize();
    return 0;
}


