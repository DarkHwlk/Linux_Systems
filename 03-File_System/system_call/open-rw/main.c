#include <stdio.h>
#include <string.h>
#include <unistd.h>  //write()
#include <fcntl.h>  //open()

int main(void){
	int fd;  //dinh danh file
	int num_write = 0;  //So byte duoc ghi vao file
	int num_read = 0;  //so bytes duoc doc cua file
	char write_buf[] = "Hello world\n";
	char read_buf[20];

	/* Open file open() */
	fd = open("hello.txt", O_RDWR | O_CREAT, 0666);
	if(-1 == fd){
		printf("open() hello.txt failed\n");
	}
	
	/* Write file write() */
	num_write = write(fd, write_buf, strlen(write_buf));
	printf("Write %d bytes to hello.txt\n", num_write);
	

	/* lseek() */
	lseek(fd, 0, SEEK_SET);  //Dat con tro o dau file de ham read() doc file

	/* Read file read() */
	num_read = read(fd, read_buf, sizeof(write_buf));
	printf("Read %d bytes from hello.txt\nContent of hello.txt: %s\n", num_read, read_buf);
	
	/* Write something append */
	lseek(fd, 0, SEEK_END);  //Dat con tro o cuoi file de viet them 
	num_write = write(fd, write_buf, strlen(write_buf));
	printf("Write %d bytes append hello.txt\n", num_write); 

	/* Close file close() */
	close(fd);

	return 0;
}
