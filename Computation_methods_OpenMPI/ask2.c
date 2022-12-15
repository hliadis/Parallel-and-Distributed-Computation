/********************************************
 * Ergasia 3 - Askhsh 2 - February 9, 2022  *
 * Iliadis Ilias - 2523                     *
 * Iliadis Grigorios - 2522                 *
 * *****************************************/
// This program is to caculate PI using MPI
// The algorithm is based on integral representation of PI. If f(x)=4/(1+x^2), then PI is the intergral of f(x) from 0 to 1
#include <stdio.h>
#include <mpi.h>
#include <stdlib.h>
#include <math.h>
#define N 1E7
#define dx (1/N)

int main (int argc, char* argv[])
{
    int rank, size, error, i;
    double pi=0.0, result=0.0, sum=0.0, begin=0.0, end=0.0, x2;
    double PI25DT = 3.141592653589793238462643;
    double *x, *part_sum_ptr;
    double part_sum = 0.0;
    double comput_time = 0.0;
    double total_comput_time = 0.0;
    double comm_time = 0.0;
    MPI_Status status;

    MPI_Init (&argc, &argv);
    //Get process ID
    MPI_Comm_rank (MPI_COMM_WORLD, &rank);
    //Get processes Number
    MPI_Comm_size (MPI_COMM_WORLD, &size);
    //Synchronize all processes and get the begin time

    int partition_size = N / size;

    if(!rank)
    {   
        int i, p;

        x = (double *)calloc(N,sizeof(double));

        for(i = 0; i<N; i++){
            x[i] = i*dx;
        }

        comm_time -= MPI_Wtime();
        for(int p=1; p<size; p++){
            MPI_Send(x + p*partition_size, partition_size, MPI_DOUBLE, p, 0, MPI_COMM_WORLD);
        }
        comm_time += MPI_Wtime();

        part_sum += 4;
        part_sum += 2;

        comput_time -= MPI_Wtime();
        for(i=1; i<partition_size; i++){
            
            if(i%2 == 0)
                part_sum += 2*( 4/(1.0+x[i]*x[i]) );
            else
                part_sum += 4*( 4/(1.0+x[i]*x[i]) );
        }
        comput_time += MPI_Wtime();
    }
   
    else
    {   
        x = (double *)calloc(partition_size,sizeof(double));
        MPI_Recv (x, partition_size, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD, &status);
        
        comput_time -= MPI_Wtime();
        for (i=0; i<partition_size; i++)
        {   
            if(i%2 == 0)
                part_sum += 2*( 4/(1.0+x[i]*x[i]) );
            else
                part_sum += 4*( 4/(1.0+x[i]*x[i]) );
        }
        comput_time += MPI_Wtime();

    }

    MPI_Reduce(&part_sum, &sum, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
    MPI_Reduce(&comput_time,&total_comput_time,1,MPI_DOUBLE,MPI_SUM, 0,MPI_COMM_WORLD);
    //Synchronize all processes and get the end time
    
    //Caculate and print PI
    if (rank==0)
    {   
        sum *= dx/3;
        if(size > 1)
        total_comput_time = total_comput_time/size;
        printf("Computation Time: %lf Communication Time: %lf\n", total_comput_time, comm_time);
        printf("#Processes=%02d    PI=%.8lf    FLOPS=%lf   Error=%.16lf\n", 
                                                            size, sum, 6*(N-1)/(total_comput_time + comm_time), fabs(sum - PI25DT));
    }
    
    error=MPI_Finalize();
    
    return 0;
}
