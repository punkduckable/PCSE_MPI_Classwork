#include "stdio.h"
#include "mpi.h"
#include "stdlib.h"

int main(int argc, char **argv) {
	// First, set up MPI
	MPI_Init(&argc, &argv);
	
	////////////////////////////////////////////////
	// Set up local variables
	int i,j;
	
	// send/recv variables
	int Proc_ID, n_procs, tag;
	MPI_Status status;
	MPI_Comm comm = MPI_COMM_WORLD;
		
	// message variables
	int *rank;
	int *rank_array;
	int message;
	MPI_Request *send_req;
	MPI_Request *recv_req;

	///////////////////////////////////////////////	
	// Get rank and size
	MPI_Comm_rank(comm, &Proc_ID);
	MPI_Comm_size(comm, &n_procs);

	////////////////////////////////////////////////
	// Set up rank, rank_array, send_req, recv_req;
	rank = (int*)malloc(n_procs*sizeof(int));
	rank_array = (int*)malloc(n_procs*n_procs*sizeof(int));
	send_req = (MPI_Request*)malloc(n_procs*sizeof(MPI_Request));
	recv_req = (MPI_Request*)malloc(n_procs*sizeof(MPI_Request));
	
	////////////////////////////////////////////////
	// send message

	// set up rank variable
	message = Proc_ID;
	tag = 1;
	
	// populate rank variable
	for(i = 0; i < n_procs; i++) {
		rank[i] = -1;
	}

	// Send out messages
	for(i = 0; i < n_procs; i++) {		
		if(i != Proc_ID) {
			MPI_Isend(&message, 1, MPI_INT, i, tag, comm, &send_req[i]);
			MPI_Irecv(&rank[i], 1, MPI_INT, i, tag, comm, &recv_req[i]);
		} // if(i != Proc_ID) {
	} // for(i = 0; i < N; i++) {


	// Wait for messages to send
	for(i = 0; i < n_procs; i++) {
		if(i != Proc_ID) {
			MPI_Wait(&send_req[i], &status);
			MPI_Wait(&recv_req[i], &status);
		} // if(i != Proc_ID) {
	} // for(i = 0; i < n_procs; i++) {


	////////////////////////////////////////////////
	// Now, collect data in processor 0 
	if(Proc_ID != 0) {
		// send rank data to processor 0. Note, the name rank is a pointer!
		MPI_Send(rank, n_procs, MPI_INT, 0, tag, comm);
	}
	else {
		// Populate first row of rank array
		for(i = 0; i < n_procs; i++) {
			rank_array[i] = rank[i];
		}

		// Now, receive the data from each processor
		for(i = 1; i < n_procs; i++) {
			MPI_Recv(&rank_array[i*n_procs],n_procs, MPI_INT, i, tag, comm, &status);
		}
	}
	////////////////////////////////////////////////
	// Print results

	if(Proc_ID == 0) {
		// Print out matrix		
		printf("\n");
		for(i = 0; i < n_procs; i++) {
			printf("%i: ",i);
			for(j = 0; j < n_procs; j++) {
				printf("%i ",rank_array[i*n_procs+j]);
			}
			printf("\n"); 
		}
	}

	MPI_Finalize();
	return 0;
}
