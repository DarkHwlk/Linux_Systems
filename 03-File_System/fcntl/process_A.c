#include <stdio.h>
#include <sys/stat.h> 
#include <sys/file.h> 
#include <unistd.h> 
#include <fcntl.h> 

int main(void) 
{ 
    int fd; 
    char text[16] = {0}; 
    struct flock fl; // thong tin lock
 
    sprintf(text, "hello word\n"); 

    if((fd=open("./test.txt", O_RDWR | O_CREAT, 0666)) == -1) { 
        printf("can not create file \n"); 
        return 0; 
    } else { 
        printf("create file test.txt\n"); 
    } 

    if(write(fd, text , sizeof(text) - 1) == -1) { 
        printf("can not write file \n"); 
        return 0; 
    } else { 
        printf("write file \n"); 
    } 

    fl.l_start = 1;         /* Byte bat dau cua lock tinh tu whence */
    fl.l_len = 5;           /* So luong bytes can lock; neu = 0 thi lock tu start den cuoi file */
    fl.l_type = F_WRLCK;    /* Lock type: F_RDLCK, F_WRLCK, F_UNLCK */
    fl.l_whence = SEEK_SET; /* How to interpret 'l_start': SEEK_SET, SEEK_CUR, SEEK_END */
	
    /* Lock fcntl() */
    if(fcntl(fd, F_SETLK, &fl) == -1) { 
        printf("can not set write lock byte 1-5\n"); 
    } else { 
        printf("set write lock byte 1-5 \n"); 
    } 

    while (1) { 
        sleep(1); 
    } 

    close(fd); 
    return 0; 
}
