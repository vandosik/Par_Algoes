#include <stdio.h>
#include "mpi.h"

#define MSG_MAX_SIZE    15

int main(int argc, char **argv)
{
    char recv_message[MSG_MAX_SIZE];
    char send_message[MSG_MAX_SIZE] = "Hello Client";
    MPI_Init(&argc, &argv);
    char port_name[MPI_MAX_PORT_NAME];
    MPI_Status status;
    MPI_Comm intercomm;
    MPI_Open_port(MPI_INFO_NULL, port_name);
    printf("Portname: %s\n", port_name);
    printf("Wait for client...\n");
    MPI_Comm_accept(port_name, MPI_INFO_NULL, 0, MPI_COMM_SELF, &intercomm);
    printf("Client Connected\n");
    MPI_Recv(recv_message, MSG_MAX_SIZE, MPI_CHAR, 0, 0, intercomm, &status);
    printf("Received from client: %s\n", recv_message);
    printf("Send to client: %s\n", send_message);
    MPI_Send(send_message, MSG_MAX_SIZE, MPI_CHAR, 0, 0, intercomm);
    MPI_Comm_free(&intercomm);
    MPI_Close_port(port_name);
    MPI_Finalize();

    return 0;
}
