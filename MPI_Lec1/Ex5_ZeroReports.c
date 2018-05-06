#include "stdio.h"
#include "mpi.h"

int main(int argc, char **argv) {
	// Set up variables
	int rank;
	int n_procs;

	// Set up MPI
	MPI_Init(&argc, &argv);

	// Get rank.
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);

	// If zero, get size and print it
	if(rank == 0) {
		MPI_Comm_size(MPI_COMM_WORLD, &n_procs);
		printf("There are %d processes running.\n",n_procs);
	} // if(rank == 0) {	

	// End MPI
	MPI_Finalize();

	return 0;
} // int main(int argc, char **argv) {
