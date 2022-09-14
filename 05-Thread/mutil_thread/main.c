#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>

/* Create lock */
pthread_mutex_t lock1 = PTHREAD_MUTEX_INITIALIZER;

int counter = 2;  //shared resource

typedef struct {
	char name[30];
	char msg[30];
} thread_args_t;

static void *handle_thr1(void* args){
	
	thread_args_t *data = (thread_args_t *)args;  //Ep kieu con tro thread_args_t cho bien args
	
	/* Lock shared resource */
	pthread_mutex_lock(&lock1);
	
	/* Critical section */
	printf("Hello %s!\n", data->name);
	printf("Thread 1 handle, counter: %d\n", ++counter);
	printf("Thread 2 handle will active after 5 seconds\n");
	sleep(5);	
	
	/* Unlock shared resource */
	pthread_mutex_unlock(&lock1);
	
	pthread_exit(NULL);
}

static void *handle_thr2(void* args){
	sleep(1);  //De thread 1 chay truoc

	/* Lock shared resource */
	pthread_mutex_lock(&lock1);  //Dung chung khoa voi thread 1
	
	/* Critical section */
	printf("Thread 2 handle, counter: %d\n", ++counter);
	
	/* Unlock shared resource */
	pthread_mutex_unlock(&lock1);
	
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
