/*
 *	Viet chuong trinh A tao ra 2 tien trinh con B va C.
 *	Tien trinh B, C tao ra 2 tien trinh BZ, CZ. Thuc hien
 *	ghi noi dung "Hello I am B process" (doi voi tien trinh
 *	B va tuong tu cac tien trinh con lai) theo thu tu:
 *	BZ -> CZ -> B -> C. Tiet trinh A dung waitpid() de xac
 *	dinh xe B ket thuc thif nhay vafo ghi file luon
 *	CO NGHIA LA THU TU THUC SU LA:
 *	BZ -> CZ -> B -> A -> C
 * */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>

int writeFileHello(char* write_buf){
	/* Write file hello.txt */
	int fd;  //dinh danh file
        int num_write = 0;  //So byte duoc ghi vao file
        //char write_buf[] = "Hello I'm BZ process\n"
	/* Open file open() */
        fd = open("hello.txt", O_RDWR | O_CREAT, 0666);
        if(-1 == fd){
        	printf("open() hello.txt failed\n");
        	return -1;
	}
        lseek(fd, 0, SEEK_END);  //Dat con tro o cuoi file de viet them
        /* Write file write() */
        num_write = write(fd, write_buf, strlen(write_buf));

	return num_write;
}

int main(int argc, char* argv[]){
	
	pid_t B_pid;  //Bien chua pid  

	/* Tao tien trinh con */
	B_pid = fork();
	if(B_pid >=0){
		if(0 == B_pid){  //Process con B
		      	
			pid_t BZ_pid = fork();
			if(BZ_pid >=0){
				if(0 == BZ_pid){  //Process con BZ
					printf("I am the process BZ\n");
					printf("BZ's PID is: %d, my parrent (B) PID is: %d\n", getpid(),getppid());
					
					/* Write file hello.txt */
					writeFileHello("Hello I'm BZ process\n");				
					
				}else{  //Process cha B
					printf("I am the process B\n");
					printf("B's PID is: %d, my parrent (A) PID is: %d\n", getpid(),getppid());
					sleep(2);  //B viet dong thu 3

					/* Write file hello.txt */
                                        writeFileHello("Hello I'm B process\n");
					
					sleep(1);  //Cho cho den khi process BZ ket thuc
				}
			}else{  /* Tien trinh con khong duoc tao thanh cong */
				printf("fork() unsuccessfully\n");
			}
	
		}else{  //Process cha A

			pid_t C_pid = fork();
                        if(C_pid >=0){
                                if(0 == C_pid){  //Process con C
					
					pid_t CZ_pid = fork();
                        		if(CZ_pid >=0){
                                		if(0 == CZ_pid){  //Process con CZ
                                        		printf("I am the process CZ\n");
                                        		printf("CZ's PID is: %d, my parrent (C) PID is: %d\n", getpid(),getppid());
							sleep(1);  //CZ viet dong thu 2

                                			/* Write file hello.txt */
                                        		writeFileHello("Hello I'm CZ process\n");

						}else{  //Process cha C
                                        		printf("I am the process C\n");
                                        		printf("C's PID is: %d, my parrent (A) PID is: %d\n", getpid(),getppid());
							sleep(3);  //C viet dong cuoi

							/* Write file hello.txt */
                                 			writeFileHello("Hello I'm C process\n");
                       
							sleep(1);  //Cho cho den khi process C ket thuc
                                		}
                        		}else{  /* Tien trinh con khong duoc tao thanh cong */
                		                printf("fork() unsuccessfully\n");
		                        }

                                }else{  //Process cha A
					printf("I am the process A\n");
        		                printf("A's PID is: %d\n", getpid());
                     
					int status_B;
					waitpid(B_pid, &status_B, WUNTRACED); 

					/* Write file hello.txt */
					writeFileHello("Hello I'm A process\n");
                                        
					while(1);
                                }
                        }else{  /* Tien trinh con khong duoc tao thanh cong */
                                printf("fork() unsuccessfully\n");
                        }

		}
	}else{  /* Tien trinh con khong duoc tao thanh cong */
		printf("fork() unsuccessfully\n");
	}

	return 0;
}
