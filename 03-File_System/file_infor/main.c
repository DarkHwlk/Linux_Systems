#include <string.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>  //for open()
#include <sys/stat.h>  //for stat | fstat 

int main(){
	struct stat statbuff;  //bien chua thong tin
	int fd;

	if( (fd=open("./hello.txt",O_RDWR | O_CREAT, 0666)) == -1 ){
		printf("CAN NOT open file heello.txt\n");
		return 0;
	}else{
		printf("CAN open hello.txt\n");
	}
	
	/* Get infor of file fstat() */
	fstat(fd, &statbuff);

	/* Print infor */
	int size = statbuff.st_size;
	printf("Size of file: %d\n", size);

	close(fd);
	return 0;
}
