#include<stdio.h>  // header file for standard input and output
#include<unistd.h>// code's entry point to various constant,type and function declarations comprising POSIX operating system API
#include<stdlib.h> // header file which includes functions involving memory allocation, process control
#include<time.h>// header file to provide standardized access to time/date manipulation and formatting  
#include<pthread.h>//provide the POSIX thread(pthread) standard API(Application program Interface) for all thread related functions


#define MIN_PID 100
#define MAX_PID 1000
#define MIN_THREADS 100
#define MAX_SLEEP 15

int *pid;
int MIN_P_ID,MAX_P_ID,NO_OF_THREADS,SIZE;

int allocate_map();
int allocate_pid();
void release_pid(int pid);

int allocate_map()
 {
	SIZE = (MAX_P_ID - MIN_P_ID + 1);
	pid = calloc(SIZE,sizeof(int));

	if (pid != NULL)
		return 1;

	return -1;
}
