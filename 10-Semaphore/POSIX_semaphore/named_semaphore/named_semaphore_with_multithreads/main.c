// Thread
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
// Semaphore
#include <fcntl.h>
#include <errno.h>
#include <time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <semaphore.h>

// Define semaphore
#define     POSIX_SEM_NAMED       "/semaphore_threads"  //Duong dan ten file semaphore
#define     R_W_PERM               0666  // Ma quyen
#define     SEM_WAITING_TIMEOUT         10000 
#define     MSECS_IN_SEC                1000

int counter = 0;  //shared resource

typedef struct {
	char name[30];
	char msg[30];
} thread_args_t;

static void *handle_thr1(void* args){
	printf("Hello, i am Thread 1\n");
	
	thread_args_t *data = (thread_args_t *)args;  //Ep kieu con tro thread_args_t cho bien args
	
	/* Semaphore */
    	int ret = -1;
    	int current_value;
    	sem_t *sem;
    	struct timespec timeout;
    	
    	/* Tao semaphore, neu ton tai roi thi tra ve loi */
	sem = sem_open(POSIX_SEM_NAMED, O_CREAT|O_EXCL, R_W_PERM, 1);
	if (sem == SEM_FAILED) {  //Co loi trong luc mo sem
		if (errno != EEXIST) {  //Loi
		    printf("Failed to open semaphore error: %s\n", strerror(errno));
		    //return -1;
		}

		// Da ton tai semaphore theo duong dan -> mo va khong can tao moi
		printf("Semaphore is available\n");
		sem = sem_open(POSIX_SEM_NAMED, 0);  //Mo file va khong can tao moi
		if (sem == SEM_FAILED) {
		    printf("Failed to open semaphore error: %s\n", strerror(errno));
		    //return -1;
		}
	}
	/* Get current semaphore */
	sem_getvalue(sem, &current_value);
	printf("Current semaphore value =%d.\n", current_value);

	/* Get currentTime */
	if (clock_gettime(CLOCK_REALTIME, &timeout) == -1)
	{
		printf("Failed to get current time error: %s\n", strerror(errno));
		//return -1;
	}
	timeout.tv_sec += SEM_WAITING_TIMEOUT / MSECS_IN_SEC;  // set timeout = currentTime+10s
	
	/* Wait semaphore voi timeout */
	ret = sem_timedwait(sem, &timeout);
	if (ret == -1)
	{
		printf("Failed to wait semaphore error: %s\n", strerror(errno));
		//return -1;
	}
	
	/* Critical section */
	printf("Hello %s!\n", data->name);
	printf("Thread 1 handle, counter: %d\n", ++counter);
	printf("Thread 2 handle will active after 5 seconds\n");
	sleep(5);	
	
	/* Tao them semaphore */
	ret = sem_post(sem);
	if (ret == -1)
	{
		printf("Failed to release semaphore error: %s\n", strerror(errno));
		//return -1;
	}	

	ret = sem_close(sem);
	if (ret == -1)
	{
		printf("Failed to close semaphore error: %s\n", strerror(errno));
		//return -1;
	}

	sem_unlink(&POSIX_SEM_NAMED);
	
	pthread_exit(NULL);
}

static void *handle_thr2(void* args){
	sleep(1);  //De thread 1 chay truoc
	
	printf("Hello, i am Thread 2\n");
	
	/* Semaphore */
    	int ret = -1;
    	int current_value;
    	sem_t *sem;
    	struct timespec timeout;
    	
    	/* Tao semaphore, neu ton tai roi thi tra ve loi */
	sem = sem_open(POSIX_SEM_NAMED, O_CREAT|O_EXCL, R_W_PERM, 1);
	if (sem == SEM_FAILED) {  //Co loi trong luc mo sem
		if (errno != EEXIST) {  //Loi
		    printf("Failed to open semaphore error: %s\n", strerror(errno));
		    //return -1;
		}

		// Da ton tai semaphore theo duong dan -> mo va khong can tao moi
		sem = sem_open(POSIX_SEM_NAMED, 0);  //Mo file va khong can tao moi
		if (sem == SEM_FAILED) {
		    printf("Failed to open semaphore error: %s\n", strerror(errno));
		    //return -1;
		}
	}
	
	/* Get current semaphore */
	sem_getvalue(sem, &current_value);
	printf("Current semaphore value =%d.\n", current_value);

	/* Locking with timeout */
	if (clock_gettime(CLOCK_REALTIME, &timeout) == -1)
	{
		printf("Failed to get current time error: %s\n", strerror(errno));
		//return -1;
	}
	timeout.tv_sec += SEM_WAITING_TIMEOUT / MSECS_IN_SEC;  //10s
	
	/* Wait semaphore voi timeout */
	ret = sem_timedwait(sem, &timeout);
	if (ret == -1)
	{
		printf("Failed to wait semaphore error: %s\n", strerror(errno));
		//return -1;
	}
	
	
	/* Critical section */
	printf("Thread 2 handle, counter: %d\n", ++counter);

	/* Tao them sem */
	ret = sem_post(sem);
	if (ret == -1)
	{
		printf("Failed to release semaphore error: %s\n", strerror(errno));
		//return -1;
	}

	ret = sem_close(sem);
	if (ret == -1)
	{
		printf("Failed to close semaphore error: %s\n", strerror(errno));
		//return -1;
	}

	sem_unlink(&POSIX_SEM_NAMED);
	
	pthread_exit(NULL);
}

int main(int argc, char* const *argv[]){

	int ret;
	thread_args_t data;
	pthread_t thread_id1, thread_id2;

	memset(&data, 0x0, sizeof(thread_args_t));
	strncpy(data.name, "Hwng", sizeof(data.name));

	if(ret = pthread_create(&thread_id1, NULL,&handle_thr1, &data)){
		printf("pthread_create()error number = %d\n", ret);
		return -1;
	}

	if(ret = pthread_create(&thread_id2, NULL,&handle_thr2, NULL)){
		printf("pthread_create()error number = %d\n", ret);
		return -1;
	}

	/* Block for the end of a thread and release */
	pthread_join(thread_id1, NULL);
	pthread_join(thread_id2, NULL);

	return 0;
}
