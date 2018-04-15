#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <netdb.h>
#include <netinet/in.h>

#include <string.h>

int main(int argc, char *argv[]) {
    int sockfd, portno, n;
    struct sockaddr_in serv_addr;
    struct hostent *server;

    char buffer[1025];

    if (argc < 3) {
        fprintf(stderr, "usage %s hostname port\n", argv[0]);
        exit(0);
    }

    portno = atoi(argv[2]);

    /* Create a socket point */
    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    if (sockfd < 0) {
        perror("ERROR opening socket");
        exit(1);
    }

    server = gethostbyname(argv[1]);

    if (server == NULL) {
        fprintf(stderr, "ERROR, no such host\n");
        exit(0);
    }

    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr, (char *)&serv_addr.sin_addr.s_addr, server->h_length);
    serv_addr.sin_port = htons(portno);
    /* Now connect to the server */
    if (connect(sockfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0) {
        perror("ERROR connecting");
        exit(1);
    }
<<<<<<< HEAD

    bzero(buffer, 256);
    n = read(sockfd, buffer, 255);
    printf("%s\n", buffer);

    /* Now get  message from the user, this message
       * will be read by server
    */

    printf("Please enter the message: ");
    bzero(buffer, 1024);
    fgets(buffer, 1024, stdin);

    /* Send message to the server */
    n = write(sockfd, buffer, strlen(buffer));

    if (n < 0) {
        perror("ERROR writing to socket");
        exit(1);
    }

    /* Now read server response */
    bzero(buffer, 1024);
    n = read(sockfd, buffer, 1024);

    if (n < 0) {
        perror("ERROR reading from socket");
        exit(1);
    }
    printf("%s\n", buffer);
=======
    n = 0;
    while(n==0){
        bzero(buffer,1025);
        n = read(sockfd, buffer, 1025);
        printf("%s\n",buffer);
    }
    /* Now ask for a message from the user, this message
       * will be read by server
    */
    while(1) {
        printf("Please enter the message: ");
        bzero(buffer, 1025);
        fgets(buffer, 1025, stdin);

        /* Send message to the server */
        n = write(sockfd, buffer, strlen(buffer));

        if (n < 0) {
            perror("ERROR writing to socket");
            exit(1);
        }

        /* Now read server response */
        bzero(buffer, 1025);
        n = read(sockfd, buffer, 1025);

        if (n < 0) {
            perror("ERROR reading from socket");
            exit(1);
        }
        printf("%s\n", buffer);
    }
>>>>>>> b64aaf173deb727d76eefb44b98df078fc4b4fd5
    return 0;
}
