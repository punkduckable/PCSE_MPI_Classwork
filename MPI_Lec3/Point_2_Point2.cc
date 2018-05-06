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

	// Send and recieve different data types 
	if(rank == 0) {	
		int x = 3;
		ierr = MPI_Send(&x, 1, MPI_INT,1,9,comm);
	}
	else if(rank == 1){
		double rec;
		ierr = MPI_Recv(&rec, 1,MPI_DOUBLE,0,9,comm,&status);
		printf("iam = %d \trecieved: %d\n",rank,rec);	
	}	
	
	// Send and recieve different count size
	else if(rank == 2) {
		int x[3] = {1,2,3};
		ierr = MPI_Send(&x, 3, MPI_INT, 3, 10, comm);
	}
	else if(rank == 3) {
		int rec[2];
		ierr = MPI_Recv(&rec,2,MPI_INT,2,10,comm,&status);
		printf("iam = %d \trecieved: %d\n",rank,rec);
	}

	// Try sending and recieving messages with different tags
	else if(rank == 4) {
		int x = 3;
		ierr = MPI_Send(&x, 1, MPI_INT, 5, 11, comm);
	}
	else if(rank == 5) {
		int rec;
		ierr = MPI_Recv(&rec, 1, MPI_INT,4,12,comm,&status);
		printf("iam = %d \trecieved: %d\n",rank,rec);
	}
	
	MPI_Finalize();
	return 0;
} 
