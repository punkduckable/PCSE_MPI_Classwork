#include <iostream>
#include <mpi.h>

using std::cout;
using std::endl;

int main(int argv, char*** argc) {	

	MPI_Init(&argv, argc);

	char name[MPI_MAX_PROCESSOR_NAME];
	int len = 10;
	
	MPI_Comm comm = MPI_COMM_WORLD;
	MPI_Status status;
	int nranks, rank = -1., ierr, irec = -1;

	MPI_Get_processor_name(name,&len);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &nranks);

	//cout << "Hello world! name:" << name << " rank:" << rank << " size:" << nranks << endl;
	
	if(rank >= (int)(((float)nranks+1)/2.)) {
		ierr = MPI_Send(&rank, 1, MPI_INT,(rank)-(int)((nranks+1)*.5),9,comm);
	}
	else {
		ierr = MPI_Recv(&irec, 1,MPI_INT,(rank)+(int)((nranks+1)*.5),9,comm,&status);
	}
	

	printf("iam = %d \trecieved: %d\n",rank,irec);	
	MPI_Finalize();
	return 0;
} 
