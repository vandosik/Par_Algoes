#include <stdio.h>
#include <stdint.h>
#include "mpi.h"

#define FILENAME        "task_21_file.txt"

int main(int argc, char **argv)
{
    int rank, comm_size, file_part_size;
    uint64_t file_size;
    MPI_Init(&argc, &argv);
    MPI_File fh;
    char *read_buf;

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &comm_size);

    MPI_File_open(MPI_COMM_WORLD, FILENAME, MPI_MODE_RDONLY, MPI_INFO_NULL, &fh);
    MPI_File_get_size(fh, (MPI_Offset*)&file_size);

    // Devide file into parts
    file_part_size = file_size / comm_size;

    if (not(file_size % comm_size))
    { // Take part size a little bigger than need
        file_part_size++;
    }
    read_buf = new char [file_part_size];

    MPI_File_set_view(fh, rank * file_part_size, MPI_CHAR, MPI_CHAR, "native", MPI_INFO_NULL);

    MPI_File_read_all(fh, read_buf, file_part_size, MPI_CHAR, MPI_STATUS_IGNORE);
    printf("Proc %d read:  '%s'\n", rank, read_buf);
    MPI_File_close(&fh);
    MPI_Finalize();

    delete [] read_buf;
    return 0;
}
