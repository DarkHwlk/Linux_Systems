#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>

#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <stddef.h>

#define BUF_SIZE 10 
#define PORT_NUM 50002

int main(int argc, char *argv[])
{    
	if(argc<3){  //Kiem tra so luong argument truyen vao
		printf("command: ./client <ip_addr> <message>");
		exit(1);
	}
	struct sockaddr_in svaddr;
    int fd;
    size_t msgLen;
    ssize_t numBytes;
    char resp[BUF_SIZE];
	
    fd = socket(AF_INET, SOCK_DGRAM, 0);      
    if (fd == -1)
		return 1;
    memset(&svaddr, 0, sizeof(struct sockaddr_in));
    svaddr.sin_family = AF_INET;
    svaddr.sin_port = htons(PORT_NUM);
    if(inet_pton(AF_INET, argv[1], &svaddr.sin_addr) <= 0)
		return 1;

	msgLen = strlen(argv[2]);
	if(sendto(fd, argv[2],msgLen,0,(struct sockaddr *)&svaddr, sizeof(struct sockaddr_in)) != msgLen)
		return 1;
	numBytes = recvfrom(fd, resp, BUF_SIZE, 0, NULL, NULL);
	if (numBytes == -1)
			return 1;
	else
		printf("Response : %s\n", resp);
    
	return 0;
}
