#include <stdio.h>
#include <unistd.h>
#include <omp.h>
#include <time.h>

int main(int argc, char *argv){

    int numCPU, nthreads, id;
    clock_t cpuStart, cpuEnd;

    //print number of cores 
    numCPU = sysconf(_SC_NPROCESSORS_ONLN);
    printf("Number of processors: %d\n", numCPU);

    //print max number of threads
    printf("Maximum number of threads: %d\n", omp_get_max_threads());
    
    cpuStart = clock();
    
    //start parallel execution
    #pragma omp parallel private(nthreads, id)
    {
        id = omp_get_thread_num();
        printf("Hi there! I am thread  %d\n", id);

        //Accessed only by master thread 
        #pragma omp master
        {
            printf("Hello. I am the master thread.\n");
            
            //print number of threads participating in execution
            nthreads = omp_get_num_threads();
            printf("Number of threads participating in execution: %d\n", nthreads);

        }
    }

    cpuEnd = clock();

    //Compute execution time
    double cpuElapsedTime = ( (double)(cpuEnd - cpuStart) ) / CLOCKS_PER_SEC ;
    printf("CPU Elapsed Time: %10.8f sec\n", cpuElapsedTime);

    return 0;
}
