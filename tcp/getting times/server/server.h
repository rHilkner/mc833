#ifndef SERVER_H
#define SERVER_H

// Enumerating permissions on the server
typedef enum {none, student, professor, waitingForComment, master} socket_permission;

// Struct that keeps client socket file descriptor and permission (student or professor)
typedef struct _skt {
   int fd;
   socket_permission permission;
} skt;

// Reads commentary of discipline. This function is only called after "discipline_id addCommentary" request is made.
extern char* readDisciplineCommentary();

#endif
