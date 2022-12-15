#include<stdio.h>
#include<stdlib.h>
#include<time.h>

int create_table(int ***array, int array_size){ //size = n
	*array = (int **)malloc(array_size*sizeof(int*));
	if( *array == NULL ) {
		printf("Problem in memory allocation...\n");
		return(-1);
	}
	for(int i = 0; i < array_size; i++) {
		(*array)[i] = (int *)malloc(array_size*sizeof(int));
		if( (*array)[i] == NULL) {
			printf("Problem in memory allocation...\n");
			return(-1);
		}
	}

	for(int i = 0; i < array_size; i++ ) {
		for(int j = 0 ; j < array_size; j++) {
			(*array)[i][j] = 1;
		}
	}
	return(0);
}

void free_table(int **array, int array_size) {
	for(int i = 0; i<array_size;i++) {
		free(array[i]);
	}
	free(array);
}

int max1(int** array,int  array_size) {
	int max = 0, sum = 0;

	for(int j = 0; j < array_size; j++) {
		for(int i = 0; i <array_size;i++) {
			sum += array[i][j];
		}
		if( sum >= max ) {
			max = sum;
			sum = 0;
		}
	}
	return(max);
}

int max2(int** array,int  array_size) {
	int max = 0, sum = 0;

	for(int j = 0; j < array_size; j++) {
		for(int i = 0; i <array_size;i+=2) {
			sum += array[i][j];
			sum += array[i+1][j];
		}
		if( sum >= max ) {
			max = sum;
			sum = 0;
		}
	}
	return(max);
}
	
int max4(int** array,int  array_size) {
	int max = 0, sum = 0;
	int k, j, i;

	for(j = 0; j < array_size; j++) {
		for(k=0, i = 0; k <array_size/4;i+=4, k++) {
			sum += array[i][j];
			sum += array[i+1][j];
			sum += array[i+2][j];
			sum += array[i+3][j];
		}
		//////REMAINING ITERATIONS/////
		for(k=0; k < array_size % 4; k++, i++){
			sum += array[i][j];
		}
		if( sum >= max ) {
			max = sum;
			sum = 0;
		}
	}
	return(max);
}

int max8(int** array,int  array_size) {
	int max = 0, sum = 0;
	int k, j, i;

	for(j = 0; j < array_size; j++) {
		for(i = 0, k=0 ; k <array_size/8;i+=8, k++) {
			sum += array[i][j];
			sum += array[i+1][j];
			sum += array[i+2][j];
			sum += array[i+3][j];
			sum += array[i+4][j];
			sum += array[i+5][j];
			sum += array[i+6][j];
			sum += array[i+7][j];
		}
		//////REMAINING ITERATIONS/////
		for(k=0; k < array_size % 8; k++, i++){
			sum += array[i][j];
		}

		if( sum >= max ) {
			max = sum;
			sum = 0;
		}
	}
	return(max);
}
	
int max16(int** array,int  array_size) {
	int max = 0, sum = 0;
	int k, j, i;

	for(j = 0; j < array_size; j++) {
		for(i = 0, k = 0; k < array_size/16 ;i+=16, k++) {
			sum += array[i][j];
			sum += array[i+1][j];
			sum += array[i+2][j];
			sum += array[i+3][j];
			sum += array[i+4][j];
			sum += array[i+5][j];
			sum += array[i+6][j];
			sum += array[i+7][j];
			sum += array[i+8][j];
			sum += array[i+9][j];
			sum += array[i+10][j];
			sum += array[i+11][j];
			sum += array[i+12][j];
			sum += array[i+13][j];
			sum += array[i+14][j];
			sum += array[i+15][j];
		}

		//////REMAINING ITERATIONS/////
		for(k=0; k < array_size % 16; k++, i++){
			sum += array[i][j];
		}

		if( sum >= max ) {
			max = sum;
			sum = 0;
		}
	}
	return(max);
}
	
int main(int argc, char *argv[]) {
	int **array = NULL;
	int size, step, max;
	struct timespec tv1, tv2;

	if( argc != 3 ) {
		printf("Wrong arguments...\n");
		return(-1);
	}
	else {
		size = atoi(argv[1]);
		step = atoi(argv[2]);
		printf("Size: %d, step: %d.\n", size, step);
	}

	if(create_table(&array,size)) {
       		printf("Shutting down expiriment...\n");
		return(0);
	}
	//1st norm calculation
	clock_gettime(CLOCK_MONOTONIC_RAW, &tv1);
	switch (step) {
		case 1: max = max1(array, size); break;
		case 2: max = max2(array, size); break;
		case 4: max = max4(array, size); break;
		case 8: max = max8(array, size); break;
		case 16: max = max16(array, size); break;
	}
	clock_gettime(CLOCK_MONOTONIC_RAW, &tv2);
	printf("1st norm of array %dx%d: %d\n", size, size, max);
	printf ("Total time = %10g seconds\n",
			(double) (tv2.tv_nsec - tv1.tv_nsec) / 1000000000.0 +
			(double) (tv2.tv_sec - tv1.tv_sec));
	//
	free_table(array, size);
	return(0);
}

	
		
