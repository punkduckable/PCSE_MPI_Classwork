#include "stdio.h"
#include "mpi.h"
#include "stdlib.h"

int main(int argc, char **argv) {
	MPI_Init(&argc, &argv);

	// Set up rank, size
	int rank, n_procs;
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &n_procs);

	// Set up message array
	int* message;
	message = (int *)malloc(n_procs*sizeof(int));
	for(int i = 0; i < n_procs; i++) {
		message[i] = rank;
	}// for(int i = 0; i < n_procs; i++) {
	
	// Set up message variables
	MPI_Status status;
	
	// Send to all messages
	for(int i = 0; i < n_procs; i++) {
		if(rank == i) {
			// Have proc i receive messages from the other processes
			for(int j = 0; j < n_procs; j++) {
				// Only receive messages from other procs (skip j = rank)
				if(j != rank) {
					MPI_Recv(&message[j], 1, MPI_INT, j, 1, MPI_COMM_WORLD, &status);
				} // if(j != rank) {
			} // for(int j = 0; j < n_procs; j++) {
		} // if(rank == i) {
		else {
			// Send rank to ith proc. 
			MPI_Send(&rank, 1, MPI_INT, i, 1, MPI_COMM_WORLD);
		} // else {			
	} // for(int i = 0; i < n_procs; i++) {

	// Print results (but only from 0 proc, prevents clutter)
	if(rank == 0) {
		printf("I am %d. My array is: \n{",rank);
		for(int i = 0; i < n_procs; i++) {	
			printf("%d ",message[i]);
		} // for(int i = 0; i < n_procs; i++) {
		printf("}\n");
	} // if(rank == 0) {

	MPI_Finalize();
	return 0;
}
