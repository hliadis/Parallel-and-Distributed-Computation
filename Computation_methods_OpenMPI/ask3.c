/********************************************
 * Ergasia 3 - Askhsh 3 - February 9, 2022  *
 * Iliadis Ilias - 2523                     *
 * Iliadis Grigorios - 2522                 *
 * *****************************************/
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mpi.h>
#define VARIABLES 1000000
#define ITERATIONS 50
#define SQUARE(N) ((N)*(N))

int main(int argc, char *argv[]){
    
    int id, prev, nxt, tag, it, np, k;
    double y, y_prev=0.0, y_next=0.0, diff, res, total_diff, total_res;
    double *x_local, *xnew_local;
    double comm_time, comput_time, total_comm_time, start, end;

    MPI_Status status;
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD,&np);
    MPI_Comm_rank(MPI_COMM_WORLD,&id);

    int patrition_size = VARIABLES / np;
    xnew_local = (double *)calloc(patrition_size,sizeof (double));
    x_local= (double *)calloc(patrition_size, sizeof (double));

    tag = 1; prev = id-1; nxt = id+1;
    comm_time = comput_time = total_comm_time = 0.0;

    for(it=1; it<=ITERATIONS; it++)
    {   
        if(!id)
            start = MPI_Wtime();
        
        //Computation of Jacobi implemented here
        for(k=0; k<patrition_size; k++){
            if(k == 0){
                
                if(id == 0)
                    xnew_local[k] = x_local[k+1]/2.0;
                else
                    xnew_local[k] = (y_prev + x_local[k+1]) / 2.0;
            }
            else if(k == patrition_size - 1){
                
                if(id == np - 1)
                    xnew_local[k] = ( x_local[k-1] + (VARIABLES + 1) ) / 2.0;
                else
                    xnew_local[k] = (x_local[k-1] + y_next) / 2.0;
            }
            else 
                xnew_local[k] = (x_local[k-1] + x_local[k+1]) / 2.0;
        }

        if(!id){
            end = MPI_Wtime();
            comput_time += end-start;
        }

        //Establish communications between processes
        double  left_limit = xnew_local[0];
        double right_limit = xnew_local[patrition_size - 1];
        
        start = MPI_Wtime();

        if(id > 0)
            MPI_Send(&left_limit,1,MPI_DOUBLE,prev,tag,MPI_COMM_WORLD);
        if(id < np - 1)
            MPI_Send(&right_limit,1,MPI_DOUBLE,nxt,tag,MPI_COMM_WORLD);
        if(id < np - 1)
            MPI_Recv(&y_next,1,MPI_DOUBLE,nxt,tag,MPI_COMM_WORLD,&status);
        if(id > 0)
            MPI_Recv(&y_prev,1,MPI_DOUBLE,prev,tag,MPI_COMM_WORLD,&status);

        end = MPI_Wtime();
        comm_time += end-start;

        //Compute residual
        res = 0.0;
        comm_time -= MPI_Wtime();
        if(!id)
            start = MPI_Wtime();
        for(k=0; k<patrition_size; k++){
            if(k == 0){
                if(id == 0)
                    res += SQUARE(2*xnew_local[k] - xnew_local[k+1]);
                else
                    res += SQUARE(2*xnew_local[k] - y_prev);
            }
            else if(k == patrition_size - 1){
                if(id == np - 1)
                    res += SQUARE(2*xnew_local[k] - (VARIABLES + 1) - xnew_local[k-1]);
                else
                    res += SQUARE(2*xnew_local[k] - xnew_local[k-1] - y_next);
            }
            else
                res += SQUARE(2*xnew_local[k] - xnew_local[k-1] - xnew_local[k+1]);
        }
        comm_time += MPI_Wtime();
        //Compute difference
        diff = 0.0;
        for(k=0; k<patrition_size; k++){
            diff += SQUARE(x_local[k] - xnew_local[k]);
        }
        memcpy(x_local, xnew_local, patrition_size * sizeof(double));
        
        if(!id){
            end = MPI_Wtime();
            comput_time += end-start;
        }
        
        //sum all local resudial and difference computations
        start = MPI_Wtime();    
        MPI_Reduce(&res,&total_res,1,MPI_DOUBLE,MPI_SUM,0,MPI_COMM_WORLD);
        MPI_Reduce(&diff,&total_diff,1,MPI_DOUBLE,MPI_SUM,0,MPI_COMM_WORLD);
        end = MPI_Wtime();
        
        comm_time += end-start;
        if(!id)
            printf ("Iter: %d Residual: %.8lf Difference: %.8lf\n", it, sqrt(total_res), sqrt(total_diff));
    }

    MPI_Reduce(&comm_time,&total_comm_time,1,MPI_DOUBLE,MPI_SUM,0,MPI_COMM_WORLD);

    if(!id){		
	    total_comm_time = total_comm_time/np;
        printf("Computation time = %lf\nCommunication time = %lf\n",comput_time,total_comm_time);
    }

    free(x_local);
    free(xnew_local);
    MPI_Finalize();
    
    return 0;
}