#include <iostream>
#include "mpi.h"

using namespace std;

int main(int argc, char* argv[])
{
	MPI_Init(&argc, &argv);
	int rank, n, i, message;
    double time_start, time_finish;
	MPI_Status status;
	MPI_Comm_size(MPI_COMM_WORLD, &n);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    int src = rank - 1;
    int dst = rank + 1;

    time_start = MPI_Wtime();

    if (not(rank == 0))
    {
        // Recv msg from prev proc
        MPI_Recv(&message, 1, MPI_INT, src, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
        cout << "Hello from process " << message << endl;
    }
    if (not(rank == n-1))
    {
        // Send msg to next proc
        message = rank;
        MPI_Send(&message, 1, MPI_INT, dst , 1, MPI_COMM_WORLD);
    }

    time_finish = MPI_Wtime();

    cout << "Process: " << rank << "  time: " << (time_finish - time_start) << endl;

	MPI_Finalize();
	return 0;
}
