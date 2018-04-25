#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "controller.h"
#include "services.h"
#include "server.h"

#define MAX_CLIENTS 30


typedef struct addComment {
	int socket_fd;
	char discipline_id[6];
} addCommentaryToDiscipline;

// Initializing array to map sockets that asked to add commentary on a discipline_id
addCommentaryToDiscipline addComment[MAX_CLIENTS];

// Gets the dicipline's identificator
char* getDisciplineID(char request[]) {

	char *discipline_id = malloc(6 * sizeof(char));

	strncpy(discipline_id, request, 5);
	discipline_id[5] = '\0';

	return discipline_id;
}

char* invalidRequest() {
	char req_answer[] = "Invalid request type.\n\n";
	char *invalid_req = malloc(strlen(req_answer) * sizeof(char));
	strcpy(invalid_req, req_answer);

	return invalid_req;
}


// Gets the type of the request
char* getRequestType(char request[]) {

	char *space_pointer;
	char *request_type;

	space_pointer = strstr(request, " ");

	if (space_pointer == NULL) {
		return NULL;
	}

	space_pointer++;
	request_type = malloc(strlen(space_pointer) * sizeof(char));
	strcpy(request_type, space_pointer);

	char *pos;
	pos = strchr(request_type, '\n');

	if (pos != NULL)
	    *pos = '\0';

	return request_type;
}


// Parses given request of type "request_prefix request_type", in which request_prefix
// may be "All" or the id of a single discipline
char* getRequest(char request[], skt *socket) {

	char *request_type;
	char *request_answer;

	request_type = getRequestType(request);

	// Checking if request valid
	if (request_type == NULL) {
		request_answer = invalidRequest();

	} else if (strncmp(request, "all", 3) == 0) {

		if (strcmp(request_type, "list") == 0) {
			request_answer = getAllDisciplinesList();

		} else if (strcmp(request_type, "info") == 0) {
            request_answer = getAllDisciplinesInfos();

		} else {
			request_answer = invalidRequest();
		}

	} else {

		char *discipline_id;
		discipline_id = getDisciplineID(request);

		if (!isValid(discipline_id)) {
			request_answer = invalidRequest();

		} else if (strcmp(request_type, "addCommentary") == 0) {

			if (socket->permission == professor) {
				// Keeping information that the determined socket asked to add comment to the discipline id (needed on addCommentary())
				for (int i = 0; i < MAX_CLIENTS; i++) {
					if (addComment[i].socket_fd == 0) {
						addComment[i].socket_fd = socket->fd;
						socket->permission = waitingForComment;
						strcpy(addComment[i].discipline_id, discipline_id);
					}
				}
				
				asprintf(&request_answer, "Please, insert your commentary to discipline %s:\n", discipline_id);
			} else {
				request_answer = strdup("You don't have professor's permission to make this request.\n");
			}

		} else if (strcmp(request_type, "title") == 0) {
			request_answer = getDisciplineTitle(discipline_id);

		} else if (strcmp(request_type, "menu") == 0) {
			request_answer = getDisciplineMenu(discipline_id);

		} else if (strcmp(request_type, "schedule") == 0) {
			request_answer = getDisciplineSchedule(discipline_id);

		} else if (strcmp(request_type, "commentary") == 0) {
			request_answer = getDisciplineCommentary(discipline_id);

		} else {
			request_answer = invalidRequest();
		}

		free(discipline_id);
	}

	free(request_type);

	/* WARNING: It is important that request_answer is freed (in the function caller)
	 * after it is not used anymore */
	return request_answer;
	
}

// Returns possible commands for given socket
char* getCommands() {
	// This function is called once for every client, so we'll initialize addComment array here
	for (int i = 0; i < MAX_CLIENTS; i++) {
		addComment[i].socket_fd = 0;
		addComment[i].discipline_id[0] = '\0';
	}

	// Instantiating message to return
	char commands_message[] = "\nHere are the commands the server can interpret:\n\
\"all list\" - prints list of id and title of every discipline in the database\n\
\"all info\" - prints id, title, menu, schedule and commentary of every discipline in the database\n\
\"discipline_id title\" - prints title of discipline of given id (*)\n\
\"discipline_id menu\" - prints menu of discipline of given id (*)\n\
\"discipline_id schedule\" - prints schedule of discipline of given id (*)\n\
\"discipline_id commentary\" - prints commentary of discipline of given id (*)\n\
\"discipline_id addCommentary\" - makes request to add commentary to discipline of given id (only professors allowed) (*)\n\
* if the given discipline id exists on the database\n\
Obs.: you can get every discipline_id with the command \"all list\"\n\n";

	char *commands = malloc(strlen(commands_message) * sizeof(char));
	strcpy(commands, commands_message);

	return commands;
}

// Adds commentary to a discipline
char* addCommentary(char* commentary, skt *socket) {

	// Checking if socket has logged out
	if (commentary == NULL) {
		for (int i = 0; i < MAX_CLIENTS; i++) {
			if (addComment[i].socket_fd == socket->fd) {
				addComment[i].socket_fd = 0;
				addComment[i].discipline_id[0] = '\0';
			}
		}
		return NULL;
	}

	// Getting discipline id 
	char *discipline_id = malloc(6 * sizeof(char));

	for (int i = 0; i < MAX_CLIENTS; i++) {
		if (addComment[i].socket_fd == socket->fd) {
			strcpy(discipline_id, addComment[i].discipline_id);
			addComment[i].socket_fd = 0;
			addComment[i].discipline_id[0] = '\0';
		}
	}

	return setDisciplineCommentary(discipline_id, commentary);
}
