// Description: A simple UDP client
// Usage: ./client <host> <port>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h> 
#include <netinet/in.h>
#include <sys/time.h>

#define BUFFER_SIZE 12500

void simulateRequests(struct sockaddr_in serveraddr, int sockfd) {
    // Number of requests of each operation
    int num_requests = 30;
	// Counters
	int i, j, n;
	// Length of server address
	int serverlen;
    // timeval structs to get time delay on requests made (in milliseconds)
    struct timeval start, stop;
    // Keeping time array of each request
    long long int request_times[7][num_requests];
    // answer for incoming messages
    char answer[BUFFER_SIZE];

    char *all_list = "all list";
    char *all_info = "all info";
    char *mc833_title = "MC833 title";
    char *mc833_menu = "MC833 menu";
    char *mc833_schedule = "MC833 schedule";
    char *mc833_commentary = "MC833 commentary";
    char *mc833_addCommentary = "MC833 addCommentary professor \
Lorem ipsum dolor sit amet, consectetur adipiscing elit.";
    
    char *requests[] = {
						all_list,
    					all_info,
    					mc833_title,
    					mc833_menu,
    					mc833_schedule,
    					mc833_commentary,
    					mc833_addCommentary
    				   };

    // Simulating all requests
    for (i = 0; i < 7; i++) {
        char current_request[BUFFER_SIZE];
        strcpy(current_request, requests[i]);

        for (j = 0; j < num_requests; j++) {
            // Getting initial time
            gettimeofday(&start, NULL);

            // Send message to the server
		    serverlen = sizeof(serveraddr);
            n = sendto(sockfd, current_request, strlen(current_request), 0, &serveraddr, serverlen);
            if (n < 0) {
                perror("ERROR writing to socket");
                exit(1);
            }

            // Now read server response
            bzero(answer, BUFFER_SIZE);
    
		    // Printing the server's reply
		    n = recvfrom(sockfd, answer, BUFFER_SIZE, 0, &serveraddr, &serverlen);
            if (n < 0) {
                perror("ERROR reading from socket");
                exit(1);
            }

            printf("%d: %s", j, answer);

            // Getting final time
            gettimeofday(&stop, NULL);

            request_times[i][j] = (stop.tv_sec - start.tv_sec) * 1000000 + (stop.tv_usec - start.tv_usec);
        }
        
    }

    sleep(1);

    // printing times
    for (i = 0; i < 7; i++) {
        for (j = 0; j < num_requests; j++) {
            printf("%llu\t", request_times[i][j]);
        }
        printf("\n");
    }
}

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
    char answer[BUFFER_SIZE];

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

    // Simulating requests to server
    simulateRequests(serveraddr, sockfd);

    return 0;
}