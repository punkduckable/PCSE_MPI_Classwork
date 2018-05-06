#include <iostream>
#include <mpi.h>

using std::cout;
using std::endl;

int main(int argc, char** argv) {	

	// Set up MPI
	MPI_Init(&argc, &argv);

	// Set up local variables
	char name[MPI_MAX_PROCESSOR_NAME];
	int len = 10;
	MPI_Comm comm = MPI_COMM_WORLD;
	MPI_Status status;
	int nranks, rank = -1., ierr, irec = -1;

	// Get processor name, rank, size
	MPI_Get_processor_name(name,&len);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &nranks);

	// Send from 0 to 1	
	if(rank == 0) {
		// First, try sending with a different type
		printf("I am %d. Sending %d as an integer\n",rank,rank);	
		ierr = MPI_Send(&rank, 1, MPI_INT,1,9,comm);
	
		// Now try sending with different count sizes (send_count < recv_count)
		// if send_count > recv_count, program crashes
		printf("I am %d. Sending %d as a single element int array.\n",rank,rank);
		ierr = MPI_Send(&rank, 1, MPI_INT, 1, 9, comm);
	
		// Send with tag 1
		printf("I am %d. Sending %d with a tag of 1",rank,rank);
		ierr = MPI_Send(&rank, 1, MPI_INT, 1, 1, comm);
	}
	else if(rank == 1) {
		// Receive an int as a double
		ierr = MPI_Recv(&irec, 1,MPI_DOUBLE,0,9,comm,&status);
		printf("I am %d. Recieved recieved %d as a double\n",rank, irec);
	
		int rec[10];
	
		// Receive a 1 element array as a 10 element array.
		MPI_Recv(&rec, 10, MPI_INT, 0, 9, comm, &status);
		printf("I am %d. Received a 10 element array: {",rank);
		for(int i = 0; i < 9; i++) {
			printf("%d, ", rec[i]);
		} // for(int i = 0; i < 9; i++) {
		printf("%d}\n",rec[9]);

		// Receive with tag 2	
		MPI_Recv(&irec, 1, MPI_INT, 0, 2, comm, &status);
		printf("I am %d. Received %d with a tag of 2",rank,irec);
	} // else if(rank == 1) {
	
	MPI_Finalize();
	return 0;
} 
