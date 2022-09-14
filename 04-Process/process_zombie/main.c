#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

/* 
 * Tien trinh con chet truoc tien trinh cha nen tien trinh con la tien trinh zombie
 *
 * Mo 1 terminal khac de theo doi tien trinh bang lenh:
 *       ps aux | grep app
 * Se thay co tien trinh co trang thai Z+ la tien trinh zombie
 * */

int main(int argc, char* argv[]){
	
	pid_t child_pid;
	int status;
	int counter = 0;

	child_pid = fork();
	if(child_pid >= 0){
		if(0 == child_pid){  //Process con
			printf("Child process\n");
		}else{   //Process cha
			while(1);

			/* Su dung wait() de giai phong tien trinh zombie */
			//wait(&status);
		}
	}else{
		printf("fork() unsuccessfully\n");
	}

	return 0;
}
