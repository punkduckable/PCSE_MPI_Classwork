#include "stdio.h"
#include "mpi.h"

int main(int argc, char **argv) {
	// Set up variables
	int rank;
	int n_procs;

	// Set up MPI
	MPI_Init(&argc, &argv);

	// Get process rank, size	
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &n_procs);
	printf("Hello from process %d.\t There are %d processes running\n",rank,n_procs);	

	// End MPI
	MPI_Finalize();

	return 0;
} // int main(int argc, char **argv) {
