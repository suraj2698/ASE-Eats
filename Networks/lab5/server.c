#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <string.h>

int isMatch(char* a, char*b){
for(int i=0, j=0;a[i]!='\0'&&b[i]!='\0';i++,j++)
{
	if(a[i]!=b[i])
	return 0;
}
return 1;
}
void copy(char *a, char*b){
	for(int i=0;b[i]!='\0';i++){
	a[i] = b[i];
	}
}
int main(){
	struct sockaddr_in server, client;
	unsigned int clientlen, sockfd;
	char rmsg[100], smsg[100]="error";
	char dns[2][100] = {"www.amrita.edu", "www.google.com"};
	char ip[2][50] = {"123.32.32.1\0", "132.12.23.23\0"};
	sockfd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	bzero((char*)&server, sizeof(server));
	server.sin_family = AF_INET;
	inet_aton("127.0.0.1", &server.sin_addr);
	server.sin_port = htons(33324);
	bind(sockfd, (struct sockaddr*)&server, sizeof(server));	

	while(1){
	for(int i=0;smsg[i]!='\0';i++)
	smsg[i] = NULL;
	smsg[0] = 'e';
	
	recvfrom(sockfd, rmsg,30,0, (struct sockaddr*)&client, &clientlen);
	for(int i=0;i<2;i++){
		if(isMatch(rmsg, dns[i])==1)
		{
		copy(smsg, ip[i]);
		break;
		}
	}
	sendto(sockfd, smsg, 30, 0, (struct sockaddr*)&client, clientlen);
	}
}

