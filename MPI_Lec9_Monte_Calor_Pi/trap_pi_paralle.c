#include "time.h"
#include "stdlib.h"
#include "stdio.h"
#include "math.h"
#include "mpi.h"

#define N 1000000

int main (int argc, char **argv) {
	long double dx = 1./((long double)N);
	long double x;
	double f_x;
	double Local_Area, Area;
	int i;
	double pi;
	
	// MPI variables
	int rank, n_procs;
	int root = 0;

	// Set up timer variables
	clock_t timer = clock();
	float time_to_calculate;
	
	// Set up MPI
	MPI_Init(&argc, &argv);	
	
	// Get rank, size
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	MPI_Comm_size(MPI_COMM_WORLD,&n_procs);

	// Now run for loop (this uses the same scheme that was used in the 
	// monte carlo method to distribuite itterations over processes
	for(int i = rank; i < N; i += n_procs) {
		// Calculate x	
		x = dx*i;
		
		// Use this to find y = (1-x^2)^(1/2)
		f_x = sqrt(1-x*x);

		// Add to area (note, we don't multiply by dx here)
		Local_Area += f_x;
	} // for(int i = 0; i < N; i++) {

	// Multiply Area by dx
	Local_Area = Local_Area*dx;

	// Now reduce results to root
	MPI_Reduce(&Local_Area, &Area, 1, MPI_DOUBLE, MPI_SUM, root, MPI_COMM_WORLD);
	
	// have root calculate pi, print results
	if(rank == root) {
		// Stop timer, calculate time
		timer = clock() - timer;
		time_to_calculate = ((float)timer)/((float)CLOCKS_PER_SEC);

		// Find PI, print results
		pi = 4*Area;
		printf("PI = %f\n",pi);
		printf("Time to calculate pi with %d processes: %f (s)\n",n_procs,time_to_calculate);
	} // if(rank == root) {

	MPI_Finalize();

	return 0;
}
