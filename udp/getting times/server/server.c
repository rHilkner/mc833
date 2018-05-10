// Description: A simple TCP server side code, which echos back the received message.
// Handle multiple socket connections with select and fd_set on Linux.

#include <stdio.h>
#include <string.h>   // strlen 
#include <stdlib.h>
#include <netdb.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>  // close 
#include <arpa/inet.h>  // close 
#include "controller.h"

// Defining server's port number
#define PORT 8888
// Data buffer of 1k
#define BUFSIZE 1024

// Prints error message
void error(char *msg) {
    perror(msg);
    exit(1);
}

int main(int argc, char **argv) {
    int master_socket; /* socket */
    int clientlen; /* byte size of client's address */
    struct sockaddr_in serveraddr; /* server's addr */
    struct sockaddr_in clientaddr; /* client addr */
    struct hostent *hostp; /* client host info */
    char buffer[BUFSIZE]; /* message buffer */
    char *answer; /* request answer */
    char *hostaddrp; /* dotted decimal host addr string */
    int optval; /* flag value for setsockopt */
    int n; /* message byte size */
    // timeval structs to get time delay on requests made (in milliseconds)
    struct timeval start, stop;
    long long int processing_time;

    // Creating the master socket
    master_socket = socket(AF_INET, SOCK_DGRAM, 0);
    if (master_socket < 0)
        error("ERROR opening socket");

    /* setsockopt: Debugging trick that lets us rerun the server immediately
     * after we kill it; otherwise we have to wait about 20 secs. Eliminates
     * "ERROR on binding: Address already in use" error. */
    optval = 1;
    setsockopt(master_socket, SOL_SOCKET, SO_REUSEADDR,
               (const void *)&optval , sizeof(int));

    // Building the server's Internet address
    bzero((char *) &serveraddr, sizeof(serveraddr));
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);
    serveraddr.sin_port = htons(PORT);

    // bind: associate the parent socket with a port
    if (bind(master_socket, (struct sockaddr *) &serveraddr,
             sizeof(serveraddr)) < 0)
        error("ERROR on binding");

    // Main loop: wait for a datagram, then echo it
    clientlen = sizeof(clientaddr);
    while (1) {

        // recvfrom: receive a UDP datagram from a client
        bzero(buffer, BUFSIZE);
        n = recvfrom(master_socket, buffer, BUFSIZE, 0,
                     (struct sockaddr *) &clientaddr, &clientlen);
        if (n < 0)
            error("ERROR in recvfrom");

        // Getting initial time
        gettimeofday(&start, NULL);

        // gethostbyaddr: determine who sent the datagram
        hostp = gethostbyaddr((const char *)&clientaddr.sin_addr.s_addr,
                              sizeof(clientaddr.sin_addr.s_addr), AF_INET);
        if (hostp == NULL)
            error("ERROR on gethostbyaddr");

        hostaddrp = inet_ntoa(clientaddr.sin_addr);

        if (hostaddrp == NULL)
            error("ERROR on inet_ntoa\n");

        // printf("server received datagram from %s (%s)\n", hostp->h_name, hostaddrp);
        // printf("server received %lu/%d bytes: %s\n", strlen(buffer), n, buffer);

        answer = getRequest(buffer);

        // Getting final time
        gettimeofday(&stop, NULL);
        processing_time = (stop.tv_sec - start.tv_sec) * 1000000 + (stop.tv_usec - start.tv_usec);

        // sendto: echo the input back to the client
        n = sendto(master_socket, answer, strlen(answer), 0,
                   (struct sockaddr *) &clientaddr, clientlen);
        if (n < 0)
            error("ERROR in sendto");

        printf("%llu\n", processing_time);
    }
}
