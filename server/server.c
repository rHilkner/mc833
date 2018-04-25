// Description: A simple server side code, which echos back the received message.
// Handle multiple socket connections with select and fd_set on Linux 
#include <stdio.h>
#include <string.h>   // strlen 
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>   // close 
#include <arpa/inet.h>  // close 
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/time.h> // FD_SET, FD_ISSET, FD_ZERO macros
#include "controller.h"
#include "server.h"

// Defining server's port number
#define PORT 8888
// Defining maximum number of simultaneous clients
#define MAX_CLIENTS 30


// Address of the server with IP and Port
struct sockaddr_in address;
// Array to keep each client socket (struct declared on "server.h")
skt client_socket[MAX_CLIENTS];

// Master socket will assign clients to new ports
skt master_socket;
// Set of socket file descritors (fd)
fd_set readfds;
// Size of socket address
int addrlen;
// Keeps highest file descriptor number (need it for the select function)
int max_socket_fd;

// Initializes all sockets with blank values
void initializeSockets() {
    // Initializing all client_socket[] to 0 so not checked 
    // for (int i = 0; i < MAX_CLIENTS; i++) {
    //     client_socket[i] = 0;
    // }

    // Initializing all client_socket[] to 0 so not checked 
    for (int i = 0; i < MAX_CLIENTS; i++) {
        client_socket[i].fd = 0;
        client_socket[i].permission = none;
    }
}

// Configures master socket to receive incoming connections
void setMasterSocket() {
	// Creating a master socket 
    master_socket.fd = socket(AF_INET, SOCK_STREAM, 0);
    // This permission will never be changed while the server exists
    master_socket.permission = master;

    if (master_socket.fd == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    // Set master socket to allow multiple connections
    if (setsockopt(master_socket.fd, SOL_SOCKET, SO_REUSEADDR, &(int){ 1 }, sizeof(int)) < 0) {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }

    // Setting address with IP (INADDR_ANY) and Port to bind master socket at
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    // Keeping size of address
	addrlen = sizeof(address);

    // Binding the socket to localhost port 8888 
    if (bind(master_socket.fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    printf("Listener on port %d\n", PORT);

    // Specifying maximum of 3 pending connections for the master socket 
    if (listen(master_socket.fd, 3) < 0) {
        perror("listen");
        exit(EXIT_FAILURE);
    }
}

// Adds all non-blank sockets to socket reading set
void addValidSocketsToReadSet() {
	// Clearing the socket set 
    FD_ZERO(&readfds);

    // Adding master socket to set 
    FD_SET(master_socket.fd, &readfds);
    max_socket_fd = master_socket.fd;

    // Adding child sockets to set 
    for (int i = 0; i < MAX_CLIENTS; i++) {
        // Socket descriptor
        int socket_fd = client_socket[i].fd;

        // If socket descriptor is valid then add to reading set 
        if(socket_fd > 0)
            FD_SET(socket_fd, &readfds);

        // Keeping highest file descriptor number (need it for the select function)
        if(socket_fd > max_socket_fd)
            max_socket_fd = socket_fd;
    }
}

// Waits for an activity on one of the sockets
void waitForActivity() {
    // Timeout is NULL, so wait indefinitely
    int activity = select(max_socket_fd + 1, &readfds, NULL, NULL, NULL);

    // Verifying error on socket activity
    if ((activity < 0) && (errno != EINTR)) {
        printf("-> WARNING: select error");
    }
}

// Reads incoming connectiong on the master socket
void readIncomingConnections() {
	int new_socket = accept(master_socket.fd, (struct sockaddr *)&address, (socklen_t*)&addrlen);

    if (new_socket < 0) {
        perror("accept");
        exit(EXIT_FAILURE);
    }

    // Informing of new user connection
    printf("New connection, socket file descriptor is %d, IP is: %s , Port: %d\n",
            new_socket, inet_ntoa(address.sin_addr), ntohs(address.sin_port));

    // Sending new connection greeting message
    char *message = "You are connected to 1s2018 IC disciplines' database.\nAre you (1) a student or (2) a professor? ";

    if (send(new_socket, message, strlen(message), 0) != strlen(message)) {
        perror("send");
    }

    printf("Welcome message sent successfully\n");

    // Adding new socket to array of sockets
    for (int i = 0; i < MAX_CLIENTS; i++) {
        // Assigning new socket to some empty position
        if (client_socket[i].fd == 0) {
            client_socket[i].fd = new_socket;
            printf("Adding to list of sockets at index %d\n", i);

            break;
        }
    }
}

// Reads IO operations on generic sockets
void readSocketIO(skt *socket) {
	// Data buffer of 1k
    char buffer[1025];
    int valread = read(socket->fd, buffer, 1024);

    // Checking if message was for closing (EOF) and also read the incoming message 
    if (valread == 0) {

        // Somebody disconnected, get his details and print 
        getpeername(socket->fd, (struct sockaddr*)&address, (socklen_t*)&addrlen);
        printf("Host disconnected, IP %s, Port %d\n",
               inet_ntoa(address.sin_addr), ntohs(address.sin_port));

        // If socket was requesting to add commentary, then stop waiting for commentary
        addCommentary(NULL, socket);

        // Closing the socket and marking as 0 in list for reuse 
        close(socket->fd);
        socket->fd = 0;
        socket->permission = none;
    }

    // Getting and echoing back the message that came in
    else {
        // Setting the string terminating NULL byte on the end of the data read
        buffer[valread] = '\0';
        char* answer;

        // Interpreting incoming message and getting the answer
    	switch(socket->permission) {

    		case none:
    			if (buffer[0] - '0' != 1 && buffer[0] - '0' != 2) {
    				char answer_string[] = "Invalid authentication.\nPlease insert (1) if you are a student or (2) if you are a professor: ";
    				answer = malloc(strlen(answer_string) * sizeof(char));
    				strcpy(answer, answer_string);
    				break;
    			}

    			socket->permission = buffer[0] - '0';
    			answer = getCommands();
	    		break;

    		case student:
    		case professor:
		        answer = getRequest(buffer, socket);
    			break;

    		case waitingForComment:
    			answer = addCommentary(buffer, socket);
    			break;

			default:
				answer = NULL;
    	}

    	// Echoing answer back to client
    	send(socket->fd, answer, strlen(answer), 0);
        free(answer);
    }
}

// Let the magic begin...
int main(int argc , char *argv[]) {

    // Getting timeval structs to get time delay on requests made
    struct timeval start, stop;
    int processment_time[7][30];
    int k = 0;

	// Initializing all sockets with blank
	initializeSockets();

	// Configuring master socket to read new connections and control other sockets
	setMasterSocket();

    printf("Waiting for connections...\n");



    // connecting to client


    // Adding every valid (not blank) socket to the reading set
    addValidSocketsToReadSet();

    // Waiting for an activity on one of the sockets
    waitForActivity();

    // Calculating time of processment after receiving an activity
    gettimeofday(&start, NULL);

    // If master socket is on reading set, then it is an incoming connection 
    if (FD_ISSET(master_socket.fd, &readfds)) {
        readIncomingConnections();
    }

    // For every socket, if it is on the reading set then read its IO operation
    for (int i = 0; i < MAX_CLIENTS; i++) {
        skt *socket = &client_socket[i];

        if (FD_ISSET(socket->fd, &readfds)) {
            readSocketIO(socket);
        }
    }


    // reading requests and calculating processment time
    
    // Accepting incoming connections
    while (k < 8*30) {
    	// Adding every valid (not blank) socket to the reading set
        addValidSocketsToReadSet();

        // Waiting for an activity on one of the sockets
        waitForActivity();

        // Calculating time of processment after receiving an activity
        gettimeofday(&start, NULL);

        // If master socket is on reading set, then it is an incoming connection 
        if (FD_ISSET(master_socket.fd, &readfds)) {
            readIncomingConnections();
        }

        // For every socket, if it is on the reading set then read its IO operation
        for (int i = 0; i < MAX_CLIENTS; i++) {
            skt *socket = &client_socket[i];

            if (FD_ISSET(socket->fd, &readfds)) {
            	readSocketIO(socket);
            }
        }

        // Getting final time of processment
        gettimeofday(&stop, NULL);

        if (k < 6*30) {
            processment_time[k/30][k%30] = stop.tv_usec - start.tv_usec;
        } else {
            if (k%2) {
                processment_time[6][(k%60)/2] = stop.tv_usec - start.tv_usec;
            } else {
                processment_time[6][(k%60)/2] += stop.tv_usec - start.tv_usec;
            }
        }

        k++;
    }

    for (int i = 0; i < 7; i++) {
        for (int j = 0; j < 30; j++) {
            printf("%d\t", processment_time[i][j]);
        }
        printf("\n");
    }

    return 0;
}
