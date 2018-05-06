#include "stdio.h"
#include "mpi.h"

int main(int argc, char **argv) {
	// Set up MPI varaibels
	int rank, n_procs;

	// Set up message variables
	int send_buf, recv_buf;
	MPI_Status status;

	// Set up MPI
	MPI_Init(&argc, &argv);

	// Get rank, size
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &n_procs);

	send_buf = rank;

	// Send between A and B
	if(rank==0) {		
		MPI_Send(&send_buf, 1, MPI_INT, 1, 1, MPI_COMM_WORLD);
		MPI_Recv(&recv_buf, 1, MPI_INT, 1, 2, MPI_COMM_WORLD, &status);
		
		printf("I am proc %d. I received %d.\n",rank,recv_buf);
	} // if(rank == 0) {
	else if(rank == 1) {
		MPI_Recv(&recv_buf, 1, MPI_INT, 0, 1, MPI_COMM_WORLD, &status);
		MPI_Send(&send_buf, 1, MPI_INT, 0, 2, MPI_COMM_WORLD);
	
		printf("I am proc %d, I received %d.\n",rank,recv_buf);
	} // else  if(rank == 1) {
	
	MPI_Finalize();
}	
