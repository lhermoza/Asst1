#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>
#include "mymalloc.h"

int i;

void testCaseA();
void testCaseB();
void testCaseC();
void testCaseD();
void testCaseE();
void testCaseF();

void testCaseA(){
   	printf("\n");
  	printf("Malloc() 1 byte and immediately free it - 150 times.\n");
  	int k, sum=0;
	for (k=0; k<100; k++) {
	   	void* a = malloc(1);
	   	struct timeval start, end;
	   	gettimeofday(&start, NULL);
	  	for (i = 0; i < 150; i++) {
			free(a);
			int malloccont = 0;
			a = malloc(1);
	    	}
	    free(a);
	
		gettimeofday(&end, NULL);
		sum = sum+((end.tv_sec*1000000 + end.tv_usec) - (start.tv_sec * 1000000 + start.tv_usec));
		//printf("\nRuntime for test case A: %ld microseconds\n", ((end.tv_sec*1000000 + end.tv_usec) - (start.tv_sec * 1000000 + start.tv_usec)));
	}
	sum = sum/100;
	printf("\nRuntime for test case A: %d microseconds\n", sum);
}

void testCaseB(){
 	printf("\n");
	printf("Malloc() 1 byte, store the pointer in an array - 150 times.\n");
	int k, sum=0;
	for (k=0; k<100; k++) {
		void * a[50];
		struct timeval start, end;
		gettimeofday(&start, NULL);
	
		for (i=0; i<3; i++) {
			for(i = 0; i < 50; i++){
				a[i] = malloc(1);
			}
			for (i=0; i<50; i++) {
				free(a[i]);
			}
		}
			gettimeofday(&end, NULL);
			sum = sum+((end.tv_sec*1000000 + end.tv_usec) - (start.tv_sec * 1000000 + start.tv_usec));
			//printf("\nRuntime for test case B: %ld microseconds\n", ((end.tv_sec*1000000 + end.tv_usec) - (start.tv_sec * 1000000 + start.tv_usec)));
	}
	sum = sum/100;
	printf("\nRuntime for test case B: %d microseconds\n", sum);
}	
	
void testCaseC(){
	printf("\n");
	printf("Randomly choose between a 1 byte malloc() or free()ing a 1 byte pointer - do this 50 times.\n");
	printf("- Keep track of each operation so that you eventually malloc() 50 times.\n");
	printf("- Keep track of each operation so that you eventaully free() all pointers\n");
	int k, sum=0;
	for (k=0; k<100; k++) {
		i = 0;
		int malloccount = 0;
		int random;
		void * a[50];
	 	struct timeval start, end;
	 	gettimeofday(&start, NULL);
	   	while(malloccount < 50){
			random = rand() % 2;
		if(random){
		    a[i] = malloc(1);
		    if(a[i] != 0){
		        malloccount++;
		        i++;
		    }
		} else{
		    if(i != 0){
		        free(a[--i]);
		    } else{
		    }
		}
	    }
	    //printf("Leftover %d bytes. So I'm gonna free them.\n", i);
	    int j;
	    for(j = 0; j < i; j++){
		free(a[j]);
	    }
	    gettimeofday(&end, NULL);
	    sum = sum+((end.tv_sec*1000000 + end.tv_usec) - (start.tv_sec * 1000000 + start.tv_usec));
		//printf("\nRuntime for test case C: %ld microseconds\n", ((end.tv_sec*1000000 + end.tv_usec) - (start.tv_sec * 1000000 + start.tv_usec)));
	}
	sum = sum/100;
	printf("\nRuntime for test case C: %d microseconds\n", sum);
}

void testCaseD(){
	printf("\n");
	printf("Randomly choosing between randomly-sized malloc() or free()ing a pointer. - many times\n");
	printf("- Keep track of each malloc so all mallocs do not exceed total memory capacity.\n");
	printf("- Keep track of each operation so that you eventually malloc() 50 times.\n");
	printf("- Keep track of each operation so that you eventually free() all pointers.\n");
	printf("- Choose a random allocation size between 1 and 64 bytes.\n");
	int k, sum=0;
	for (k=0; k<100; k++) {
		int randomOper, randomSize, mallocCount = 0;
		void * a[50];
		i=0;
		struct timeval start, end;
		gettimeofday(&start, NULL);
		while(mallocCount < 50){
			randomOper = rand() % 2;
			if(randomOper){
				randomSize = rand() % 64 + 1;
				a[i] = malloc(randomSize);
				if(a[i] != 0){
					mallocCount++;
					i++;
				}
			} else {
				if(i != 0){
					free(a[--i]);
				}
			}
		}
		//printf("There are leftover %d stuff. So I'm gonna free them.\n", i);
		int j;
		for(j = 0; j < i; j++){
			free(a[j]);
		}
		gettimeofday(&end, NULL);
		sum = sum+((end.tv_sec*1000000 + end.tv_usec) - (start.tv_sec * 1000000 + start.tv_usec));
		//printf("\nRuntime for test case D: %ld microseconds\n", ((end.tv_sec*1000000 + end.tv_usec) - (start.tv_sec * 1000000 + start.tv_usec)));
	}
	sum = sum/100;
	printf("\nRuntime for test case D: %d microseconds\n", sum);
};

void testCaseE(){
	printf("\n");
	printf("Malloc an incrementing size. When reached capacity, free all in reverse\n");
		void * a[50];
		i = 0;
		int cont = 0;
		struct timeval start, end;
		gettimeofday(&start, NULL);
		do {
			a[i] = malloc(i);
			if(a[i] == 0){
				cont = 1;
			}
			i++;
		} while(cont == 0);
		int j;
		for(j = 0; j < i-1; j++){
		      free(a[j]);
		}
		gettimeofday(&end, NULL);
		printf("\nTime took for test case E: %d microseconds\n", ((end.tv_sec*1000000 + end.tv_usec) - (start.tv_sec * 1000000 + start.tv_usec)));
};

void testCaseF() {
	printf("\nMalloc 50-byte chunks 50 times, then free all of them, then request max possible block size");
	int k, sum=0;
	for (k=0; k<100; k++) {
		struct timeval start, end;
		gettimeofday(&start, NULL);
		void * a[50];
		for (i=0; i<50; i++) {
			a[i] = malloc(50);
		}
		for (i=0; i<50; i++) {
			free(a[i]);
		}
		void * req = malloc(4080);
		free(req);
		gettimeofday(&end, NULL);
		sum = sum+((end.tv_sec*1000000 + end.tv_usec) - (start.tv_sec * 1000000 + start.tv_usec));
	}
	sum = sum/100;
	printf("\nRuntime for test case F: %d microseconds\n", sum);
};

int main(int argc, char**argv){
	testCaseA();
	testCaseB();
	testCaseC();
	testCaseD();
	testCaseE();
	testCaseF();
	return 0;
}
