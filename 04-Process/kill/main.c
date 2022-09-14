#include <stdio.h>
#include <unistd.h>
#include <signal.h>

int main(int argc, char* argv[]){
	printf("Kill this process after 3 seconds\n");
	sleep(3);
	
	/* Dung tien trinh hien tai bang ham kill() */
	if( kill( getpid(), SIGKILL ) < 0 ){
		printf("Kill is unsuccessfull\nStart loop\n");
		while(1);
	}

	return 0;
}
