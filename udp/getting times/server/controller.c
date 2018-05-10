#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "controller.h"
#include "services.h"
#include "server.h"


char* invalidRequest() {
	char req_answer[] = "Invalid request type.\n\n";
	char *invalid_req = malloc(strlen(req_answer) * sizeof(char));
	strcpy(invalid_req, req_answer);

	return invalid_req;
}

// Gets the dicipline's identificator
char* getDisciplineID(char request[]) {

	char *discipline_id = malloc(6 * sizeof(char));

	strncpy(discipline_id, request, 5);
	discipline_id[5] = '\0';

	return discipline_id;
}


// Gets the type of the request
char* getRequestType(char request[]) {

	char *first_space_pointer, *second_space_pointer;
	char *request_type;

	// Getting the spaces that separate the second word in the request
	first_space_pointer = strstr(request, " ");
	if (first_space_pointer == NULL)
		return NULL;

	second_space_pointer = strstr(++first_space_pointer, " ");

	// Copying second word to request_type
	if (second_space_pointer == NULL) {
		request_type = malloc(strlen(first_space_pointer) * sizeof(char));
		strcpy(request_type, first_space_pointer);
	} else {
		request_type = malloc((second_space_pointer-first_space_pointer+1) * sizeof(char));
		strncpy(request_type, first_space_pointer, second_space_pointer-first_space_pointer);
	}

	char *pos = strstr(request_type, "\n");

	if (pos != NULL)
	    *pos = '\0';

	return request_type;
}

char* getUserPermission(char request[]) {
	char *second_space_pointer, *third_space_pointer;
	char *user_permission;

	// Getting the spaces that separate the third word in the request
	second_space_pointer = strstr(request, " ");
	if (second_space_pointer == NULL)
		return NULL;

	second_space_pointer = strstr(++second_space_pointer, " ");
	if (second_space_pointer == NULL)
		return NULL;

	third_space_pointer = strstr(++second_space_pointer, " ");

	// Copying third word to user_permission
	if (third_space_pointer == NULL) {
		user_permission = malloc(strlen(second_space_pointer) * sizeof(char));
		strcpy(user_permission, second_space_pointer);
	} else {
		user_permission = malloc((third_space_pointer-second_space_pointer+1) * sizeof(char));
		strncpy(user_permission, second_space_pointer, third_space_pointer-second_space_pointer);
	}

	char *pos = strstr(user_permission, "\n");

	if (pos != NULL)
	    *pos = '\0';

	return user_permission;
}

char *getCommentary(char request[]) {
	char *third_space_pointer;
	char *commentary;


	third_space_pointer = strstr(request, " ");
	if (third_space_pointer == NULL)
		return NULL;

	third_space_pointer = strstr(++third_space_pointer, " ");
	if (third_space_pointer == NULL)
		return NULL;

	third_space_pointer = strstr(++third_space_pointer, " ");
	if (third_space_pointer == NULL)
		return NULL;
	
	commentary = malloc(strlen(++third_space_pointer) * sizeof(char));
	strcpy(commentary, third_space_pointer);

	char *pos = strstr(commentary, "\n");

	if (pos != NULL)
	    *pos = '\0';

	return commentary;
}


// Parses given request of type "request_prefix request_type <user_permission> <commentary>",
// in which request_prefix may be "All" or the id of a single discipline and <> are optional
char* getRequest(char request[]) {

	char *request_type;
	char *request_answer;
	int q;

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

		} else if (strncmp(request_type, "addCommentary", 13) == 0) {

			char *user_permission = getUserPermission(request);

			if (strncmp(user_permission, "professor", 9) == 0) {
				char *commentary = getCommentary(request);
				
				if (commentary == NULL) {
					request_answer = strdup("The commentary is invalid.\n");
				} else {
					request_answer = setDisciplineCommentary(discipline_id, commentary);
				}

				free(commentary);

			} else {
				request_answer = strdup("You must have professor's permission to make this request.\n");
			}

			if (user_permission != NULL) {
				free(user_permission);
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
