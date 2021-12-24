#include <mpi.h>
#include <stdio.h>
#include <unistd.h>

int main(int argc, char **argv)
{
    int proc_rank, size, rank1, rank2, rank3;
    MPI_Init(&argc, &argv);
    MPI_Comm comm_revs;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &proc_rank);
    int root_rank = 0;


    if (root_rank == proc_rank)
    {
        printf("Setting color to (1)\n");
    }
    MPI_Comm_split(MPI_COMM_WORLD, 1, size - proc_rank, &comm_revs);
    MPI_Comm_rank(comm_revs, &rank1);
    //Display rank and rank1
    printf("proc_rank = %d, rank1 = %d\n", proc_rank, rank1);
    MPI_Comm_free(&comm_revs);

    sleep(1); // Sleep for one second in case printf takes time
    if (root_rank == proc_rank)
    {
        printf("Setting color to (proc_rank %% 2)\n");
    }
    MPI_Barrier(MPI_COMM_WORLD);
    MPI_Comm_split(MPI_COMM_WORLD, proc_rank % 2, size - proc_rank, &comm_revs);
    MPI_Comm_rank(comm_revs, &rank2);
    //Display rank and rank2
    printf("proc_rank = %d, rank2 = %d\n", proc_rank, rank2);
    MPI_Comm_free(&comm_revs);

    sleep(1); // Sleep for one second in case printf takes time
    if (root_rank == proc_rank)
    {
        printf("Setting color to (proc_rank %% 3)\n");
    }
    MPI_Barrier(MPI_COMM_WORLD);
    MPI_Comm_split(MPI_COMM_WORLD, proc_rank % 3, size - proc_rank, &comm_revs);
    MPI_Comm_rank(comm_revs, &rank3);
    //Display rank and rank3
    printf("proc_rank = %d, rank3 = %d\n", proc_rank, rank3);
    MPI_Comm_free(&comm_revs);

    MPI_Finalize();
}
