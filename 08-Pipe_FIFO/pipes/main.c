#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <signal.h>

#define MSG_SIZE 20

char *msg1 = "hello, Hwng #1";
char *msg2 = "hello, Hwng #2";
char *msg3 = "hello, Hwng #3";
char *msg4 = "hello, Hwng #4";

char pipe_buff[MSG_SIZE];
int fds[2], i;

void sig_handler1(int num){
	printf("I am signal handler1: %d\n", num);
	write(fds[1], msg4, MSG_SIZE);
}

int main(int argc, char const *argv[]){
	
	/* Tao pipe */
	if(pipe(fds) < 0){
		printf("pipe() unsuccesfully\n");
		exit(1);
	}
	
	/* write() pipe */
	write(fds[1], msg1, MSG_SIZE);
	write(fds[1], msg2, MSG_SIZE);
	write(fds[1], msg3, MSG_SIZE);

	printf("sleep 2 seconds\n");
	sleep(2);

	for (i=0; i<3; i++){
		/* read() pipie */
		read(fds[0], pipe_buff, MSG_SIZE);
		printf("msg[%d]: %s\n", i+1, pipe_buff);
	}

	return 0;
}
