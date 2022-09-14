#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>

pthread_t thread_id1, thread_id2;

typedef struct{
	char name[30];
	char msg[30];
} thr_data_t;

/* Function handle thread */
static void *thr_handle(void *args){
	pthread_t now_tid = pthread_self();
	thr_data_t *data = (thr_data_t *) args;  //Ep kieu cho bien args thanh kieu thr_data_t*

	if(pthread_equal(now_tid, thread_id1)){  //Neu tra ve khac 0 thread_id so sanh bang nhau
		printf("I am thread_id1\n");		
	}else if(pthread_equal(now_tid, thread_id2)){
		printf("I am thread_id2\n");
		printf(" Hello %s, welcome to join: %s\n", data->name, data->msg);
	}
}

/* Function handle thread 2 */
static void *thr_handle_2(void *args){
	printf("Hi i am thread handle 2\n");
}

int main(int argc, char const *argv[]){
	
	int ret;
	thr_data_t data = {0};

	/* Set data */
	strncpy(data.name, "Hwng", sizeof(data.name));
	strncpy(data.msg, "Linux programing", sizeof(data.msg));

	if(ret = pthread_create(&thread_id1, NULL, &thr_handle, NULL)){  //Neu tra ve la 0 thi thread duoc tao thanh cong
		printf("thread_create() error number=%d\n", ret);
		return -1;
	}
	
	printf("Create thread 2 affter thread 1 about 2 seconds\n");
	sleep(2);  //Tao thread2 sau khi tao thread1 2s

	if(ret = pthread_create(&thread_id2, NULL, &thr_handle, &data)){  //Neu tra ve la 0 thi thread duoc tao thanh cong
		printf("thread_create() error number=%d\n", ret);
		return -1;
	}

	sleep(5);  //Cho chay het thread
	return 0;
}
