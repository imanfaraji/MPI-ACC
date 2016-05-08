#include "MICRO_BENCHMARK.h"
void _COLLSUBCOMM_func(void *src, void *dst, int msg_size, int dim_wght, MPI_Comm comm)
{
	MPI_Ialltoall(src, msg_size * dim_wght, MPI_CHAR, dst, msg_size * dim_wght , MPI_CHAR, comm, &req_coll);

#ifdef __IMI_DEBUG_ALL__
	int my_size = -1;
	MPI_Comm_size(comm, &my_size);
	printf("MPI_Ialltoall(%p, %d, MPI_CHAR, %p, %d, MPI_CHAR, %d)\n", src, msg_size * dim_wght, dst, msg_size * dim_wght, my_size);
#endif
}
