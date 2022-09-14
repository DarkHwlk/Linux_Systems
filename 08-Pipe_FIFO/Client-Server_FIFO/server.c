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
#define KEY "1912"
#define SERVICE1 "HELLO"
#define SERVICE2 "UPPERCASE"
#define SERVICE3 "LOWERCASE"

int responseClient(int status){
	if(status == 1){	
		char buff[] = "SUCCESS";
		int fd = open(FIFO_REQUEST, O_WRONLY);
        	write(fd, buff, strlen(buff) +1);
        	close(fd);
		return 0;
	}else{
		char buff[] = "FAIL";
                int fd = open(FIFO_REQUEST, O_WRONLY);
                write(fd, buff, strlen(buff) +1);
                close(fd);
                return 0;
	}
}

int main(int argc, char const *argv[])
{   
    char buffRequest[BUFF_SIZE];
    int fdRequest;

    /* Noi dung request */
    char* nameClient;
    char* serviceClient;
    char* keyClient;

    // mkfifo(<pathname>, <permission>)
    mkfifo(FIFO_REQUEST, 0666);

    while (1) {
        // Read first
        fdRequest = open(FIFO_REQUEST, O_RDONLY);
        read(fdRequest, buffRequest, BUFF_SIZE);  //Block neu k co du lieu
        printf("Client request: %s\n", buffRequest);
        close(fdRequest);

	/* Kiem tra noi dung request */
	nameClient = strtok(buffRequest, ">");
	serviceClient = strtok(NULL, ">");
	keyClient = strtok(NULL, ">");

	/* Xu li Request */
	if(strcmp(keyClient,KEY) == 0){
		/* Key chinh xac */
		if(strcmp(serviceClient, SERVICE1) == 0){
                	/* Service 1 */
			printf("Client that have name: %s, request SERVICE1\n", nameClient);
			responseClient(1);
        	}else if(strcmp(serviceClient, SERVICE2) == 0){
                        /* Service 2 */
                        printf("Client that have name: %s, request SERVICE2\n", nameClient);
			responseClient(1);
                }else if(strcmp(serviceClient, SERVICE3) == 0){
                        /* Service 3 */
                        printf("Client that have name: %s, request SERVICE3\n", nameClient);
			responseClient(1);
                }
	}else{
		printf("Key of request is not exact\n");
		responseClient(0);  // response fail
	}
    }

    return 0;
}
