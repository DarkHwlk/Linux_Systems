#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

/* 
 * Su dung ham signal(SIGCHLD, <func>) de goi ham <func>
 * khi tien trinh  con ket thuc de giai phong bo nho
 * tranh tao ra tien trinh zombie
 * */

/* Function call when have SIGCHLD */
void func(int signum){
	printf("Have SIGCHLD => the child process have dead\n");
	wait(NULL);  //Giai phong tienn trinh zombie do tien trinh con tao ra
}

int main(int argc, char* argv[]){
	
	pid_t child_pid;
	child_pid = fork();
	
	if(child_pid >= 0){
		if(0 == child_pid){  //Process con
			printf("Child process PID: %d\n", getpid());
			while(1);
		}else{   //Process cha
			
			/*
			 * khi tien trinh con ket thuc SIGCHLD se bao va nhay vao ham func()
			 * */
			signal(SIGCHLD, func);
			printf("I am parrent\n");
			while(1);
		}
	}else{
		printf("fork() unsuccessfully\n");
	}

	return 0;
}
