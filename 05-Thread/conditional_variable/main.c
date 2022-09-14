#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>

#define THRESHOLD 5

/* Create lock */
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

/* Create conditional_variable */
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

int counter = 0;  //shared resource

typedef struct {
	char name[30];
	char msg[30];
} thread_args_t;

static void *handle_thr1(void* args){
	
	thread_args_t *data = (thread_args_t *)args;  //Ep kieu con tro thread_args_t cho bien args
	
	/* Lock shared resource */
	pthread_mutex_lock(&lock);
	
	/* Critical section */
	printf("Thread 1: Hello %s!\n", data->name);
	
	while(counter < THRESHOLD){
		counter++;
		printf("Thread 1 handle, counter: %d\n", counter);
		sleep(1);
	}
	
	/* Gui 1 signal den thread 2 */
	pthread_cond_signal(&cond);
	
	/* Unlock shared resource */
	pthread_mutex_unlock(&lock);
	
	pthread_exit(NULL);
}

static void *handle_thr2(void* args){
	sleep(1);  //De thread 1 chay truoc

	/* Roi vao trang thai block trong khi wait signal
	 * Sau khi co signal se thoat khoi trang thai
	 * block va tien hanh lock shared resource 
	 * (Trong luc wait thread k su dung tai nguyen CPU) */
	pthread_cond_wait(&cond, &lock);

	/* Critical section */	
	printf("Thread 2 handle, counter: %d\n", counter);
	
	/* Unlock shared resource */
	pthread_mutex_unlock(&lock);
	
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
