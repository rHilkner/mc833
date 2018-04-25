#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <netdb.h>
#include <netinet/in.h>
#include <sys/time.h>
#include <math.h>

#include <string.h>

#define BUFFER_SIZE 12500

char buffer[BUFFER_SIZE];
int socket_fd;


void simulateRequests() {
    // Number of requests of each operation
    int num_requests = 30;

    // Getting timeval structs to get time delay on requests made
    struct timeval start, stop;

    // Keeping time array of each request
    int request_times[7][num_requests];

    char *all_list = "all list";
    char *all_info = "all info";
    char *mc833_title = "MC833 title";
    char *mc833_menu = "MC833 menu";
    char *mc833_schedule = "MC833 schedule";
    char *mc833_commentary = "MC833 commentary";
    char *mc833_addCommentary = "MC833 addCommentary";
    char *commentary = "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Praesent mollis aliquet mattis. Pellentesque vitae dolor in massa tincidunt finibus. Sed interdum nisi neque, eget lobortis eros pretium sed. Vivamus eu finibus eros. Aliquam rhoncus molestie ante. Etiam consequat ligula id ante rutrum, at faucibus mauris egestas. Pellentesque tincidunt mi dui, nec vehicula sem pretium nec. Morbi placerat maximus magna. Nullam nulla sapien, viverra vel molestie in, tincidunt eget lorem. Fusce id dictum turpis. Mauris a bibendum purus.\n\
Morbi quis nibh ut nibh convallis scelerisque nec vel metus. Nam imperdiet ipsum in fringilla rutrum. In magna turpis, efficitur nec velit sit amet, accumsan posuere arcu. Proin ullamcorper volutpat eleifend. Lorem ipsum dolor sit amet, consectetur adipiscing elit. Suspendisse efficitur ornare porttitor. Praesent eu augue vel lectus maximus pharetra eget non nisl.\n\
In molestie aliquam viverra. Sed vel placerat justo, id porttitor velit. Phasellus consectetur diam ac felis ultrices nullam.\n";

    char *requests[] = {all_list, all_info, mc833_title, mc833_menu, mc833_schedule, mc833_commentary, mc833_addCommentary};

    // Assigning to database as professor
    // Send message to the server
    int n = write(socket_fd, "2", strlen("2"));

    if (n < 0) {
        perror("ERROR writing to socket");
        exit(1);
    }

    n = 0;
    while (n == 0) {
        // Now read server response
        bzero(buffer, BUFFER_SIZE);
        n = read(socket_fd, buffer, BUFFER_SIZE);
    }

    if (n < 0) {
        perror("ERROR reading from socket");
        exit(1);
    }

    // simulating all requests
    for (int i = 0; i < 6; i++) {
        char* current_request = requests[i];

        for (int j = 0; j < num_requests; j++) {
            // Getting initial time
            gettimeofday(&start, NULL);

            // Send message to the server
            int n = write(socket_fd, current_request, strlen(current_request));

            if (n < 0) {
                perror("ERROR writing to socket");
                exit(1);
            }

            // Now read server response
            bzero(buffer, BUFFER_SIZE);
            n = read(socket_fd, buffer, BUFFER_SIZE);

            if (n < 0) {
                perror("ERROR reading from socket");
                exit(1);
            }

            // Getting final time
            gettimeofday(&stop, NULL);

            request_times[i][j] = stop.tv_usec - start.tv_usec;
        }
        
    }

    // simulating addCommentary (2 reqs needed)
    for (int j = 0; j < 2*num_requests; j++) {
        char* current_request;

        // Getting initial time
        gettimeofday(&start, NULL);

        if (j%2) {
            current_request = requests[6];
        } else {
            current_request = commentary;
        }

        // Send message to the server
        int n = write(socket_fd, current_request, strlen(current_request));

        if (n < 0) {
            perror("ERROR writing to socket");
            exit(1);
        }

        // Now read server response
        bzero(buffer, BUFFER_SIZE);
        n = read(socket_fd, buffer, BUFFER_SIZE);

        if (n < 0) {
            perror("ERROR reading from socket");
            exit(1);
        }

        // Getting final time
        gettimeofday(&stop, NULL);

        if (j%2) {
            request_times[6][j/2] = stop.tv_usec - start.tv_usec;
        } else {
            request_times[6][j/2] += stop.tv_usec - start.tv_usec;
        }
        
    }

    // printing times
    for (int i = 0; i < 7; i++) {
        for (int j = 0; j < num_requests; j++) {
            printf("%d\t", request_times[i][j]);
        }
        printf("\n");

    }
}

int main(int argc, char *argv[]) {
    int portno, n = 0;
    struct sockaddr_in serv_addr;
    struct hostent *server;

    if (argc < 3) {
        fprintf(stderr, "usage %s hostname port\n", argv[0]);
        exit(0);
    }

    portno = atoi(argv[2]);

    // Create a socket point
    socket_fd = socket(AF_INET, SOCK_STREAM, 0);

    if (socket_fd < 0) {
        perror("ERROR opening socket");
        exit(1);
    }

    // Try to find host
    server = gethostbyname(argv[1]);

    if (server == NULL) {
        fprintf(stderr, "ERROR, no such host\n");
        exit(0);
    }

    // Getting server address (IP and Port)
    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr, (char *)&serv_addr.sin_addr.s_addr, server->h_length);
    serv_addr.sin_port = htons(portno);

    // Now connect to the server
    if (connect(socket_fd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0) {
        perror("ERROR connecting");
        exit(1);
    }

    // Wait for welcome message (handshake)
    while (n == 0) {
        bzero(buffer, BUFFER_SIZE);
        n = read(socket_fd, buffer, BUFFER_SIZE);
        printf("%s\n", buffer);
    }
    

    // Now ask for a message from the user, this message will be read by server
    simulateRequests();

    return 0;
}
