#include <string.h>
#include <stdlib.h>

#include "controller.h"
#include "services.h"
#include "server.h"

typedef enum {professor, student} permission;

// Gets the dicipline's identificator
char* getDisciplineID(char request[]) {

	char *discipline_id = malloc(6 * sizeof(char));

	strncpy(discipline_id, request, 5);
	discipline_id[5] = '\0';

	return discipline_id;
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

	return request_type;
}


/* Parses given request of type "request_prefix request_type", in which request_prefix
 * may be "All" or the id of a single discipline */
char* getRequest(char request[], permission user_permission) {

	char *request_answer;

	char *request_type;
	request_type = getRequestType(request);

	// Checking if request valid
	if (request_type == NULL) {
		char req_answer[] = "Invalid request type.\n\0";
		request_answer = calloc(strlen(req_answer), sizeof(char));
		strcpy(request_answer, req_answer);

		return request_answer;

	} else if (strncmp(request, "All", 3) == 0) {

		if (strcmp(request_type, "list") == 0) {
			request_answer = getAllDisciplinesList();

		} else if (strcmp(request_type, "info") == 0) {
            request_answer = getAllDisciplinesInfos();
		}

	} else {

		char *discipline_id;
		discipline_id = getDisciplineID(request);

		if (strcmp(request_type, "addCommentary") == 0) {

			if (user_permission == professor) {
				char *commentary = readDisciplineCommentary();
				request_answer = setDisciplineCommentary(discipline_id);
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
			char req_answer[] = "Invalid request type.\n\0";
			request_answer = calloc(strlen(req_answer), sizeof(char));
			strcpy(request_answer, req_answer);
		}

		free(discipline_id);
	}

	free(request_type);

	/* WARNING: It is important that request_answer is freed (in the function caller)
	 * after it is not used anymore */
	return request_answer;
	
}
