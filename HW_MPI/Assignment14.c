#include <iostream>
#include <mpi.h>

#define VEC_SIZE 1000

using namespace std;


void max_of_pair(void *a, void *b, int *l, MPI_Datatype *type)
{
    int *first_arr = (int*)a;
    int *second_arr = (int*)b;

    for (int i = 0; i < *l; i++)
    {
        first_arr[i] = std::max(first_arr[i], second_arr[i]);
    }
}

int main(int argc, char **argv)
{
    int rank, proc_num, i;
    int a[VEC_SIZE];
    int b[VEC_SIZE];
    int b_sample[VEC_SIZE];

    MPI_Init(&argc, &argv);
    MPI_Op op;
    MPI_Comm_size(MPI_COMM_WORLD, &proc_num);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    for (i = 0; i < VEC_SIZE; i++)
    {
        a[i] = i + rank + 1;
    }

    cout << "Process " << rank << ": a[0] filled with: " << a[0] << endl;

    MPI_Op_create(&max_of_pair, 1, &op);
    MPI_Reduce(a, b, VEC_SIZE, MPI_INT, op , 0, MPI_COMM_WORLD);
    MPI_Op_free(&op);

    MPI_Reduce(a, b_sample, VEC_SIZE, MPI_INT, MPI_MAX, 0, MPI_COMM_WORLD);

    if (rank == 0)
    {
        cout << "b[0] = " << b[0] << "  b[" << i-1 << "] = " << b[i-1] << endl;

        for (i = 0; i < VEC_SIZE and (b[i] == b_sample[i]); i++);

        if (i == VEC_SIZE) // So at least one b[i] was incorrect
        {
            cout << "CORRECT" << endl;
        }
        else // Alll b[i] coincide b_sample[i]
        {
            cout << "FAILURE: b[" << i-1 << "] = " << b[i-1] << " while must be: " << b_sample[i-1]  << endl;
        }
    }

    MPI_Finalize();
}
