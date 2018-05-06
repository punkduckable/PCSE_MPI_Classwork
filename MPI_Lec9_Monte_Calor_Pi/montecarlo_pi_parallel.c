#include "stdio.h"
#include "stdlib.h"
#include "time.h"
#include "mpi.h"
#include "math.h"

#define N 100000000

int main(int argc, char **argv) {
	int rank, n_procs;
	int i; 
	double x,y,r;
	int local_count = 0;
	int count;
	double pi;
	
	// Variables for sending stuff
	int root = 0;

	// timing variables
	clock_t timer = clock();	
	double time_to_calculate;

	// Initialize MPI
	MPI_Init(&argc, &argv);

	// Get rank, size
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &n_procs);

	// Seed random function
	srand(time(0));

	// This make it so that the procs jump with step size equal to the
	// number of procs. Each process starts at its rank. This ensures 
	// that each process gets a balanced work load and does each 
	// iteration once!   
	for(i = rank; i < N; i += n_procs) {	
		// Find x, y coordinates
		x = ((double)rand())/((double)RAND_MAX);
		y = ((double)rand())/((double)RAND_MAX);

		// Calculate distance from origin of point
		r = sqrt(x*x + y*y);

		// Check if point is in unit circle
		if(r < 1.) {
			local_count++;
		} // if(r < 1.) {
	} // for(i = rank; i < N; i+= n_proc) {

	// Now reduce data to the root
	MPI_Reduce(&local_count, &count, 1,MPI_INT, MPI_SUM, root, MPI_COMM_WORLD);

	
	// Now calculate, print results on root process
	if(rank == root) {
		// Find time of calculation
		timer = clock() - timer;
		time_to_calculate = ((double)timer)/((double)CLOCKS_PER_SEC);
	
		pi = 4.0*((double)count)/((double)N);
		printf("Pi = %f\n time to calculate pi on %d processors: %f (s)\n",pi,n_procs,time_to_calculate);
	} // if(rank == root)
		
	// Finalize MPI
	MPI_Finalize();	

	return 0;
}	// int main(inat arbc, char **argv)
