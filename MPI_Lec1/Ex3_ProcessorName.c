#include "stdio.h"
#include "mpi.h"

int main(int argc, char **argv) {
	// Set up variables
	char name[MPI_MAX_PROCESSOR_NAME];
	int len = 10;	

	// Set up MPI
	MPI_Init(&argc, &argv);

	// Get process name, print it out
	MPI_Get_processor_name(name,&len);
	printf("Hello from node %s\n",name);

	// End MPI
	MPI_Finalize();

	return 0;
} // int main(int argc, char **argv) {
