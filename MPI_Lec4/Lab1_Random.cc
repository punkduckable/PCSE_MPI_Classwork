#include "time.h"
#include "stdlib.h"
#include "mpi.h"
#include "stdio.h"

#define N 100000

int main(int argc, char **argv) {
	MPI_Init(&argc, &argv);

	// Get rank, n_procs
	int rank, n_procs;
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &n_procs);

	// Set up local variables
	double rand_number;
	double max_rand;

	// Seed random. Put a lot of spacing between seeds on diff processes (N is large)
	srand(time(0) + N*rank); 

	// Make a random number
	rand_number =((double)rand())/((double)RAND_MAX);

	// Report random number
	printf("I am %d. My random number is: \t%f\n",rank,rand_number);

	// Reduce back to root process (process 0 is root)
	MPI_Reduce(&rand_number, &max_rand, 1, MPI_DOUBLE, MPI_MAX, 0, MPI_COMM_WORLD); 
	
	// Have root print max random number
	if(rank == 0) { 
		printf("I am %d. Maximum random number is: \t%f\n",rank, max_rand);
	} // if(rank == 0) {

	MPI_Finalize();
	return 0;	
} // int main(int argc, char **argv) {
