#include "stdio.h"
#include "math.h"
#include "mpi.h"

// Prototypes
int IsFactor(int n);

// Global vairables
#define N 2000000111

int main(int argc, char **argv) {
	// Set up MPI variables
	int rank, n_procs;
	int i;
	MPI_Status status;

	// Set up root finding variables
	long RootN;
	int Local_Factor;

	MPI_Init(&argc, &argv);

	// Get rank, size
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &n_procs);

	// Create an array to store results from various procs. This will be used when we send
	// data back to process 0 at the end
	int Factors[n_procs];
	
	// find sqrt of n
	RootN = (long)ceil(sqrt(N));

	// Now, cycle through integers from 2 to RootN. Test if each one is a factor of N
	// We do this by starting at 2+Rank and then incrementing with a step size of n_procs
	// This way, each itteration is handled by just one proc and each proc gets the same
	// work (or very close to the same work)
	for(i = 2+rank; i < RootN; i += n_procs) {
		if(IsFactor(i)) {
			// If it's not prime, we set the local factor variable to the factor
			Local_Factor = i;
		}	// if(IsFactor(i)) {
	}	// for(i = 2+rank; i < RootN; i+=n_procs) {

	// Now send results back to 0 proc
	if(rank !=0) {
		MPI_Send(&Local_Factor, 1, MPI_INT, 0, 1, MPI_COMM_WORLD);	
	} // if(rank != 0) {
	else {
		Factors[0] = Local_Factor;
		
		// Recieve results
		for(i = 1; i < n_procs; i++ ) {
			// Note: Factors+i is simply the address of Local_Factor[i]
			MPI_Recv((Factors+i),1,MPI_INT,i,1, MPI_COMM_WORLD, &status);	
		} // for(i = 1; i < n_procs; i++) {

		// Print if prime
		for(i = 0; i < n_procs; i++) {
			if(Factors[i] != 0) {
				printf("%d is not prime, process %i found that %d is one of its factors!\n",N,i,Factors[i]); 
			}	// if(Local_Factor[i] != 0) {	
		} // for(i = 0; i < n_proc; i++) {
	}// else {

	MPI_Finalize();
}

int IsFactor(int n) { 
	if(N%n == 0) {
		return 1;
	} // if (N%n == 0) {
	else {
		return 0;
	} // else {
} // int IsPrime
