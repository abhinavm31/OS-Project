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


int allocate_pid()
 {
	int i = 0;
	while (pid[i] != 0) 
	{
		i++;
	}
	if (i + MIN_P_ID > MAX_P_ID) {
		return -1;
	}
	pid[i] = 1;

	return i + MIN_P_ID;
}


void release_pid(int pid1) 
{
	if (pid1 < MIN_P_ID || pid1 > MAX_P_ID) 
	{
		printf("\n PID not present in the range %i - %i \n",MIN_P_ID,MAX_P_ID);
		return;
	}
	pid[pid1 - MIN_P_ID] = 0;
}


pthread_mutex_t lock;


void *thread_fun(int arg) 
{
   int sleepTime = rand() % MAX_SLEEP;
   int waitTime=1;	
    int pid = -1;
    while(pid == -1) {
        pthread_mutex_lock(&lock);
        pid = allocate_pid();
        if (pid == -1) 
	{
            printf("\nPID cannot be assigned due to complete usage of memory \t THREAD : %d will have to wait for pid to release the resources.\n",arg+1);
		sleep(waitTime);
	           }
        pthread_mutex_unlock(&lock);
    }

    printf("\n Thread: %d  has taken PID: %i  PROCESSING for %i  seconds\n",arg+1,pid,sleepTime);
    sleep(sleepTime);

    printf("\n Thread: %d has COMPLETED its execution. \t PID: %i  has RELEASED.\n",arg+1,pid);
    release_pid(pid);

    return NULL;
}


int main()
 {
    int i;
printf("\nEnter Minimum and Maximum Value of PID");
printf(" between 100 & 1000\n\n");
printf("Enter Min PID value : ");

scanf("%d",&MIN_P_ID);

printf("\nEnter Max PID value : ");
scanf("%d",&MAX_P_ID);

printf("\nEnter no. of threads to be created ");
printf("Max :100\n");
scanf("%d",&NO_OF_THREADS);

if(MIN_P_ID < MIN_PID || MAX_P_ID > MAX_PID ||NO_OF_THREADS > MIN_THREADS)
{
printf("\n YOU HAVE ENTERED WRONG VALUES \n");
return 1;
}


 printf("\nEXECUTING\n");
    pthread_t thread_ids[NO_OF_THREADS];
  srand(time(NULL)); 

    pthread_mutex_init(&lock, NULL);

    if (allocate_map() == -1) 
	{
        printf("Cannot initialize the pidmap\n");
        return -1;
    	}

    for (i = 0; i < NO_OF_THREADS; i++) 
	{
        pthread_create(&thread_ids[i],NULL,thread_fun,i);
	sleep(1);
        }

    for (i = 0; i < NO_OF_THREADS; i++)	
	 {
        pthread_join(thread_ids[i],NULL);	
         }

    if (pid != NULL) 
	{
        free(pid);
    	}

    printf("\n\n EXCECUTED SUCCESSFULLY\n\n\n");
    return 0;
}
