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
	MPI_Request* Send_req;
	MPI_Request* Recv_req;

	Send_req = (MPI_Request*)malloc(n_procs*sizeof(MPI_Request));
	Recv_req = (MPI_Request*)malloc(n_procs*sizeof(MPI_Request));

	// Send to all messages using non-blocking communication
	for(int i = 0; i < n_procs; i++) {
		if(i != rank) {
			MPI_Isend(&rank, 1, MPI_INT, i, 2, MPI_COMM_WORLD, &Send_req[i]);
			MPI_Irecv(&message[i], 1, MPI_INT, i, 2, MPI_COMM_WORLD, &Recv_req[i]);
		}
	} // for(int i = 0; i < n_procs; i++) {
	
	// Now wait until all messages are sent, received
	for(int i = 1; i < n_procs; i++) {
		if(i != rank) {
			MPI_Wait(&Send_req[i], &status);
			MPI_Wait(&Recv_req[i], &status);
		} // if(i != rank) {
	}
 
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
