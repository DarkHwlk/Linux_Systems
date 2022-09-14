#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

// FIFO Request file path
#define FIFO_REQUEST   "./SolveRequestFIFO"
#define BUFF_SIZE   1024

// Service and Key
#define KEY "1912";
#define SERVICE1 "HELLO";
#define SERVICE2 "UPPERCASE";
#define SERVICE3 "LOWERCASE";

int main(int argc, char const *argv[])
{   
	/* Noi dung request */
        char* nameClient = "./ClientFIFO";
        char* serviceClient = SERVICE1;
        char* keyClient = KEY;

	char buffRequest[BUFF_SIZE] = "./ClientFIFO>HELLO>1912";
    	char buffResponse[BUFF_SIZE]; 
	int fdRequest;
	pid_t pid =  getpid();

    /* Create FIFO */
    // mkfifo(<pathname>, <permission>)
    mkfifo(FIFO_REQUEST, 0666);
    mkfifo(nameClient, 0666);

    while (1) {
        // Request
        fdRequest = open(FIFO_REQUEST, O_WRONLY);
        write(fdRequest, buffRequest, strlen(buffRequest) +1);
        close(fdRequest);
        // Wait response
	fdRequest = open(FIFO_REQUEST, O_RDONLY);
        read(fdRequest, buffResponse, BUFF_SIZE);  //Block neu k co du lieu
        printf("Server response: %s\n", buffRequest);
        close(fdRequest);
	if(strcmp( buffResponse, "SUCCESS") == 0){
		printf("Server response SUCCESS\n");	
		return 0;
	}else
		printf("Server response FAIL\n");	
    }

    return 0;
}
