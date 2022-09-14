/*
 *	Viet chuong trinh A tao ra 1 tien trinh con B
 *	Trong tien trinh A thuc hien tao ra file hello.txt
 *	nam trong duong dan ./hello.txt va ghi thong 
 *	diep vao file day. B se thuc hien doc lai noi
 *	dung file vaf in ra man hinh
 * */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>  
#include <fcntl.h>  
#include <sys/wait.h>

/* Function is called when the child process die */
void func_SIGCHLD(int signum){
	printf("Have SIGCHLD => the child process have dead\n");
	wait(NULL);
}

int main(int argc, char* argv[]){

	pid_t child_pid = fork();
	if(child_pid >= 0){  //fork() successfully
		if(child_pid == 0){  //Process con (B)
			int fd;  //dinh danh file
        		int num_read = 0;  //so bytes duoc doc cua file
        		char read_buf[20];

			/* Wait for process A write data in file */
			printf(" Wait 5 seconds for process A write data in file\n");
			sleep(5);	

			 /* Open file open() */
        		fd = open("hello.txt", O_RDWR | O_CREAT, 0666);
        		if(-1 == fd){
                		printf("open() hello.txt failed\n");
		        }
			printf("I am child process\n");	
			
		       	/* lseek() */
        		lseek(fd, 0, SEEK_SET);  //Dat con tro o dau file de ham read() doc file

        		/* Read file read() */
        		num_read = read(fd, read_buf, sizeof(read_buf));
		        printf("Read %d bytes from hello.txt\nContent of hello.txt: %s\n", num_read, read_buf);

		}else{  //Process cha (A)

			signal(SIGCHLD, func_SIGCHLD);

			int fd;  //dinh danh file
			int num_write = 0;  //So byte duoc ghi vao file
        		char write_buf[] = "Hello exam1\n";
		
			/* Open file open() */
		        fd = open("hello.txt", O_RDWR | O_CREAT, 0666);
       			if(-1 == fd){
                		printf("open() hello.txt failed\n");
        		}
			printf("I am parrent process\n");	

			/* Write file write() */
        		num_write = write(fd, write_buf, strlen(write_buf));
        		printf("Write %d bytes to hello.txt\n", num_write);
		
			while(1);
		}
	}else{
		printf("fork() unsuccessfully\n");
	}

	return 0;
}
