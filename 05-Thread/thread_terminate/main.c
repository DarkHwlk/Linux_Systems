#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>

pthread_t thread_id1, thread_id2, thread_id3;

typedef struct{
	char name[30];
	char msg[30];
} thr_data_t;

/* Function handle thread 1 */
static void *thr_handle_1(void *args){
	thr_data_t *data = (thr_data_t *) args;  //Ep kieu cho bien args thanh kieu thr_data_t*
	sleep(1);
	printf("Hi i am thread handle 1\n");
	printf("Thread 1: Hello %s, welcome to join: %s\n", data->name, data->msg);
	
	pthread_exit(NULL);
}

/* Function handle thread 2 */
static void *thr_handle_2(void *args){

	while(1){
		printf("Hi i am thread handle 2\n");
		sleep(1);
	}
	
	pthread_exit(NULL);
}

/* Function handle thread 3 */
static void *thr_handle_3(void *args){
	
       //pthread_detach() dua thread vao trang thai detach => he dieu hanh tu dong clean thread => pthread_join() k the lay duoc trang thai,...
	pthread_detach(pthread_self()); //Neu lenh nay bi comment thi chi create toi da duoc 32000 thread	
	pthread_exit(NULL);
}

int main(int argc, char const *argv[]){
	
	int ret, counter = 0;
	int retval;
	thr_data_t data = {0};

	/* Set data */
	strncpy(data.name, "Hwng", sizeof(data.name));
	strncpy(data.msg, "Linux programing", sizeof(data.msg));

	if(ret = pthread_create(&thread_id1, NULL, &thr_handle_1, &data)){  //Neu tra ve la 0 thi thread duoc tao thanh cong
		printf("thread_create() error number=%d\n", ret);
		return -1;
	}

	if(ret = pthread_create(&thread_id2, NULL, &thr_handle_2, NULL)){  //Neu tra ve la 0 thi thread duoc tao thanh cong
		printf("thread_create() error number=%d\n", ret);
		return -1;
	}
	
	printf("thread 2 will be canceled after 5 seconds => CAN NOT print thread 2 after 5 seconds\n");
	sleep(5);
	pthread_cancel(thread_id2);
	pthread_join(thread_id2, NULL);
	printf("thread 2 termination\n");
	
	while(1){
		if(ret = pthread_create(&thread_id3, NULL, &thr_handle_3, NULL)){  //Neu tra ve la 0 thi thread duoc tao thanh cong
			printf("thread_create() error number=%d\n", ret);
			return -1;
		}
		counter++;
		//pthread_join(thread_id3, NULL);
		if(counter%1000 == 0){
			printf("Thread created: %d\n", counter);
		}
	}
	
	printf("Thread created: %d\n", counter);
	sleep(5);  //Cho chay het thread
	return 0;
}
