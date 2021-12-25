MPICC = ~/mpich-install/bin/mpicc

all: serv client

task_19_serv: Assignment19_serv.c
	${MPICC} Assignment19_serv.c -o task_19_serv
serv: task_19_serv

task_19_client: Assignment19_client.c
	${MPICC} Assignment19_client.c -o task_19_client
client: task_19_client

clean:
	rm task_19_serv task_19_client
#Default target
.PHONY: all
