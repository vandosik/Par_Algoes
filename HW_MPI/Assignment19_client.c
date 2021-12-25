#include <stdio.h>
#include "mpi.h"
#include <string.h>
#define MSG_MAX_SIZE    15

int main(int argc, char **argv)
{
    char recv_message[MSG_MAX_SIZE];
    char send_message[MSG_MAX_SIZE] = "Hello Server";
    int rank;
    MPI_Init(&argc, &argv);
    char port_name[MPI_MAX_PORT_NAME];
    MPI_Comm intercomm;
    MPI_Status status;
    strcpy(port_name, argv[1]);
    printf("Attempt to connect\n");
    MPI_Comm_connect(port_name, MPI_INFO_NULL, 0, MPI_COMM_SELF, &intercomm);
    printf("Connected to server\n");
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    printf("Send to server: %s\n", send_message);
    MPI_Send(send_message, MSG_MAX_SIZE, MPI_CHAR, 0, 0, intercomm);
    MPI_Recv(recv_message, MSG_MAX_SIZE, MPI_CHAR, 0, 0, intercomm, &status);
    printf("Received from server: %s\n", recv_message);
    MPI_Finalize();

    return 0;
}
