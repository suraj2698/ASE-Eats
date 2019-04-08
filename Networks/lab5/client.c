/*
 * client.c
 * 
 * Copyright 2022  <examuser@11cpu0226L>
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 * 
 * 
 */


#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <string.h>

int main(int argc, char **argv)
{
	struct sockaddr_in serv_addr, client_addr;
	unsigned int sockfd, client_len;
	
	sockfd = socket (AF_INET, SOCK_DGRAM, 0);
	
	bzero ((char*)&serv_addr, sizeof (serv_addr));
	serv_addr.sin_family = AF_INET;
	inet_aton ("127.0.0.1", &serv_addr.sin_addr);
	serv_addr.sin_port = htons (33324);
	
	bzero ((char*) &client_addr, sizeof (client_addr));
	client_addr.sin_family = AF_INET;
	inet_aton ("127.0.0.1", &client_addr.sin_addr);
	client_addr.sin_port = htons (0);
	
	bind (sockfd, (struct sockaddr*)&client_addr, sizeof
	(client_addr));
	
	while(1){
	char msg[100];
	gets(msg);
	sendto (sockfd, msg, 30, 0, (struct sockaddr*)&serv_addr, sizeof (serv_addr));
	recvfrom (sockfd, msg, 30, 0, (struct sockaddr*)&client_addr, &client_len);
	printf ("%s\n", msg);
	}
	return 0;
}

