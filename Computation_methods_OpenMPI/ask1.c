/********************************************
 * Ergasia 3 - Askhsh 1 - February 9, 2022  *
 * Iliadis Ilias - 2523                     *
 * Iliadis Grigorios - 2522                 *
 * *****************************************/
#include <stdio.h>
#include <string.h>
#include <mpi.h>

int main(int argc, char *argv[])
{
    int rank, size,length;
    char msg_string[80];
    MPI_Status status;
    const int tag = 42;

    MPI_Init(&argc, &argv);

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    MPI_Barrier(MPI_COMM_WORLD);
    double execution_time = MPI_Wtime();
    double total_bcast_time = 0.0;

    if(rank == 0)
    {
        //printf("number of tasks: %d\n", size);
        strcpy(msg_string,"Hello.This is the master node!\n");
        //printf("%s", msg_string);
        
        total_bcast_time -= MPI_Wtime();
    }
        MPI_Bcast(msg_string,80,MPI_CHAR,0,MPI_COMM_WORLD);
    
    if(rank == 0){
        total_bcast_time += MPI_Wtime();
        
        int nodes_replied=0;
        int buffer;
        for(int p=1; p<size; p++){
            MPI_Recv(msg_string,80,MPI_CHAR,MPI_ANY_SOURCE,0,MPI_COMM_WORLD,&status);
            //printf("Received message form process:%d\n",status.MPI_SOURCE);
            
            nodes_replied++;
        }
        //printf("%d nodes replied back to master node.\n",nodes_replied);
    }

    else

    {   
        //printf("Hello.This is node %d\n",rank);
        //printf("From master: %s", msg_string);
        sprintf(msg_string,"Hello.This is node %d\n",rank);
        MPI_Send(msg_string,80,MPI_CHAR,0,0,MPI_COMM_WORLD);
    }
    
    if(!rank){
        printf("Execution Time: %lf ",MPI_Wtime() - execution_time);
        printf("Broadcast Time: %lf\n",total_bcast_time);
    }
    
    MPI_Finalize();
    return 0;
}