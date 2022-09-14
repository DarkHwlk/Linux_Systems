#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char* argv[]){
	
	pid_t child_pid;
	int status_child, rv;

	child_pid = fork();  //tao tien trinh con sao chep tien trinh du lieu cha tu dau den ham fork()

	if(child_pid >= 0){
		if(0 == child_pid){  //process con
			printf("I am the child process, my PID: %d\n",getpid());
			printf("The child process will finish after 5 seconds\n");
			sleep(5);
			exit(0);  //Ket thu tien trinh voi status = 0

		}else{  //process cha | Luc nay child_pid = pid cua process con
			printf("I am the parrent process, my PID: %d\n",getpid());	

			/* Theo doi tien trinh con wait() */
			rv = wait(&status_child);  //Tra ve pid cua tien trinh con da ket thuc
			if(rv == -1){
				printf("wait() is unsuccessful\n");
			}else{
				printf("PID of dead child is: %d\n", rv);
				printf("Status of dead child is: %d\n", status_child);
				
				/* Kiem tra xem tien trinh con ket thuc the nao */
				if(WIFEXITED(status_child)){
					printf("Child process finished NORMALLY\n");
				}else if(WIFSIGNALED(status_child)){
					printf("Child process finished by KILL SIGNAL\n");
				}
			}
		}
	}else{
		printf("fork is unsuccesful\n");
	}

	return 0;
}
