#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <mpi.h>

#define MATRIX_SIZE 500

using namespace std;

int main(int argc, char **argv)
{
    int proc_rank, comm_size;
    //matrix initialization by each process
    int matrix_a[MATRIX_SIZE][MATRIX_SIZE], matrix_b[MATRIX_SIZE][MATRIX_SIZE], matrix_c[MATRIX_SIZE][MATRIX_SIZE];
    double time_start, time_stop;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &comm_size);
    MPI_Comm_rank(MPI_COMM_WORLD, &proc_rank);

    for (int i = 0; i < MATRIX_SIZE; i++)
    {
        for (int j = 0; j < MATRIX_SIZE; j++)
        {
            matrix_a[i][j] = rand() % 100;
            matrix_b[i][j] = rand() % 100;
            matrix_c[i][j] = 0;
        }
    }
    // Wait for all procs here
    MPI_Barrier(MPI_COMM_WORLD);
    // start timing for each process
    time_start = MPI_Wtime();
    // matrix multiplication
    for (int i = 0; i < MATRIX_SIZE; i++)
    {
        for (int j = 0; j < MATRIX_SIZE; j++)
        {
            for (int k = 0; k < MATRIX_SIZE; k++)
            {
                matrix_c[i][j] += matrix_a[i][k] * matrix_b[k][j];
            }
        }
    }
    // end of timing
    time_stop = MPI_Wtime();
    // output the execution time of matrix multiplication at each process
    cout << "Process: " << proc_rank << " counted for " << setw(8) << (time_stop - time_start) * 1000000 << " usec" << endl;

    MPI_Finalize();
}
