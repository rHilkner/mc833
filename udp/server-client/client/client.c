/* 
 * udpclient.c - A simple UDP client
 * usage: udpclient <host> <port>
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 

#define BUFFER_SIZE 1024

// Wrapper for perror
void error(char *msg) {
    perror(msg);
    exit(0);
}

int main(int argc, char **argv) {
    int sockfd, portno, n;
    int serverlen;
    struct sockaddr_in serveraddr;
    struct hostent *server;
    char *hostname;
    char buffer[BUFFER_SIZE];
    char *message = "MC833 title";

    // Checking command line arguments
    if (argc != 3) {
       fprintf(stderr,"usage: %s <hostname> <port>\n", argv[0]);
       exit(0);
    }
    hostname = argv[1];
    portno = atoi(argv[2]);

    // Creating the socket
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) 
        error("ERROR opening socket");

    // gethostbyname: get the server's DNS entry
    server = gethostbyname(hostname);
    if (server == NULL) {
        fprintf(stderr, "ERROR, no such host as %s\n", hostname);
        exit(0);
    }

    // Building the server's Internet address */
    bzero((char *) &serveraddr, sizeof(serveraddr));
    serveraddr.sin_family = AF_INET;
    bcopy((char *)server->h_addr,
          (char *)&serveraddr.sin_addr.s_addr,
          server->h_length);
    serveraddr.sin_port = htons(portno);

    strcpy(buffer, message);

    // Sending the message to the server
    serverlen = sizeof(serveraddr);
    n = sendto(sockfd, buffer, strlen(buffer), 0, &serveraddr, serverlen);
    if (n < 0) 
      error("ERROR in sendto");
    
    // Printing the server's reply
    n = recvfrom(sockfd, buffer, BUFFER_SIZE, 0, &serveraddr, &serverlen);
    if (n < 0) 
      error("ERROR in recvfrom");
    
    printf("%s", buffer);

    return 0;
}