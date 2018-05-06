#include "stdio.h"
#include "mpi.h"

int main(int argc, char **argv) {
	// Print before MPI
	printf("Hello, this is before MPI_Init\n");

	// Set up MPI
	MPI_Init(&argc, &argv);

	printf("Hello from after Init\n");

	// End MPI
	MPI_Finalize();

	printf("Hello from after MPI_Finalize\n");

	return 0;
} // int main(int argc, char **argv) {
