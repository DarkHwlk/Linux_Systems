#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char* argv[]){
	//printf("Run command line 'ls -lah' after 2 seconds\n");
	//sleep(2);  //delay 2s
	
	/* Goi tien trinh khac execl() */
	//execl( "/bin/ls", "ls", "-l", "-a", "-h", NULL );
	
	printf("\n\nRun program './app' in folder lesson4/arg_env after 3 seconds\n");
	sleep(3);

	/* Goi tien trinh ./app o thu muc lesson4/arg_env */
	execl( "../arg_env/app", "./app", "hello", "Hwng", NULL );

	return 0;
}
