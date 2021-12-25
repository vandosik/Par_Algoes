#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <mpi.h>

#define BUFSIZE         100
#define FILENAME        "task_20_file.txt"
#define TARGET_STRING   "Bla Bla Bla..."

void create_write_file(const char *filename, const char *content, int content_length)
{
    MPI_File fd;
    MPI_Status status;
    printf("Create/Open file: %s\n", FILENAME);
    MPI_File_open(MPI_COMM_WORLD, filename, MPI_MODE_CREATE | MPI_MODE_WRONLY, MPI_INFO_NULL, &fd);
    MPI_File_write(fd, content, content_length, MPI_CHAR, &status);
    MPI_File_close(&fd);
}

int main(int argc, char **argv)
{
    int bufsize, num, sum;
    int c;
    MPI_Init(&argc, &argv);

    // creating and writing content in file
    create_write_file(FILENAME, TARGET_STRING, sizeof(TARGET_STRING));

    MPI_Status status;
    MPI_File fd;
    char buf[BUFSIZE];
    MPI_File_open(MPI_COMM_WORLD, FILENAME, MPI_MODE_RDONLY, MPI_INFO_NULL, &fd);
    MPI_File_set_view(fd, 0, MPI_CHAR, MPI_CHAR, "native", MPI_INFO_NULL);
    sum = 0;
    do {
        MPI_File_read(fd, buf, BUFSIZE, MPI_CHAR, &status);
        MPI_Get_count(&status, MPI_CHAR, &num);
        printf("Read: '%s'\n", buf);
        sum += num;
    } while (num >= BUFSIZE);
    MPI_File_close(&fd);
    //print the number of read symbols sum from the file
    printf("Symbols received %d\n", sum);

    //Deleting file if we pass option '-d';
    c = getopt(argc, argv, "d");
    if (c != -1)
    {
        printf("Delete file: %s\n", FILENAME);
        MPI_File_delete(FILENAME, MPI_INFO_NULL);
    }

    MPI_Finalize();

    return 0;
}
