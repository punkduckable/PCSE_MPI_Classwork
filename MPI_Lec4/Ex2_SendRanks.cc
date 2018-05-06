#include "stdio.h"
#include "mpi.h"

int main(int argc, char **argv) {
	// First, set up MPI
	MPI_Init(&argc, &argv);
	
	////////////////////////////////////////////////
	// Set up local variables
	
	// send/recv variables
	int Proc_ID, n_ranks, tag;
	MPI_Status status;
	MPI_Comm comm = MPI_COMM_WORLD;
		
	// message variables
	const int N = 8;
	int rank[8];
	int rank_array[N][N];
	int message;
	MPI_Request send_request;

	///////////////////////////////////////////////	
	// Get rank and size
	MPI_Comm_rank(comm, &Proc_ID);
	MPI_Comm_size(comm, &n_ranks);

	////////////////////////////////////////////////
	// send message

	// set up rank variable
	message = Proc_ID;
	tag = 1;
	
	// populate rank variable
	for(int i = 0; i < N; i++) {
		rank[i] = -1;
	}

	// Send out messages
	if(Proc_ID < 8) {
		for(int i = 0; i < N; i++) {
			if(i != Proc_ID) {
				MPI_Isend(&message, 1, MPI_INT, i,tag, comm, &send_request);
			}	// if(i!=rank) {
		}

		// recieve messages
		for(int i = 0; i < N; i++) {
			if(i != Proc_ID) {
				MPI_Recv(&rank[i],1,MPI_INT,i,tag,comm,&status);
			}
			else { 
				rank[i] = Proc_ID;
			}
		}
	

		MPI_Wait(&send_request, &status);
	}
	
	////////////////////////////////////////////////
	// Now, collect data in processor 0
	if(Proc_ID < 8) { 
		if(Proc_ID != 0) {
			// send rank data to processor 0
			MPI_Isend(&rank, N, MPI_INT, 0, tag, comm, &send_request);
		}
		else {	
			// Populate first row of rank array
			for(int i = 0; i < N; i++) {
				rank_array[0][i] = rank[i];
			}

			// Now, receive the data from each processor
			for(int i = 1; i < N; i++) {
				MPI_Recv(rank_array[i],N,MPI_INT,i,tag,comm,&status);
			}
		}
	}
	////////////////////////////////////////////////
	// Print results

	if(Proc_ID == 0) {
		// Print out matrix		
		printf("\n");
		for(int i = 0; i < N; i++) {
			printf("%i: ",i);
			for(int j = 0; j < N; j++) {
				printf("%i ",rank_array[i][j]);
			}
			printf("\n"); 
		}
	}

	MPI_Finalize();
	return 0;
}
