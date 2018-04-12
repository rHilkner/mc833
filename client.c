#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Gets the dicipline's identificator
char* getDisciplineID(char request[]) {
	char *discipline_id = calloc(6, sizeof(char));

	strncpy(discipline_id, request, 5);
	discipline_id[5] = 0;

	return discipline_id;
}

// Gets the type of the request
char* getRequestType(char request[]) {
	char *space_pointer;
	char *request_type;

	space_pointer = strstr(request, " ");
	space_pointer++;

	request_type = calloc(strlen(space_pointer), sizeof(char));
	strcpy(request_type, space_pointer);

	return request_type;
}

// Parses given request of type ""
char* getRequest(char request[]) {
	char *discipline_id;
	char *request_type;

	discipline_id = getDisciplineID(request);
	request_type = getRequestType(request);

	char *request_answer;

	if (strcmp(request_type, "title") == 0) {
		char req_answer[] = "Invalid request type.\n\0";
		request_answer = calloc(strlen(req_answer), sizeof(char));
		strcpy(request_answer, req_answer);

	} else if (strcmp(request_type, "menu") == 0) {
		char req_answer[] = "Invalid request type.\n\0";
		request_answer = calloc(strlen(req_answer), sizeof(char));
		strcpy(request_answer, req_answer);

	} else if (strcmp(request_type, "schedule") == 0) {
		char req_answer[] = "Invalid request type.\n\0";
		request_answer = calloc(strlen(req_answer), sizeof(char));
		strcpy(request_answer, req_answer);

	} else if (strcmp(request_type, "commentary") == 0) {
		char req_answer[] = "Invalid request type.\n\0";
		request_answer = calloc(strlen(req_answer), sizeof(char));
		strcpy(request_answer, req_answer);

	} else {
		char req_answer[] = "Invalid request type.\n\0";
		request_answer = calloc(strlen(req_answer), sizeof(char));
		strcpy(request_answer, req_answer);
	}

	free(discipline_id);
	free(request_type);

	return request_answer;
	
}



int main() {
	char a[] = "MC833 menu\0";
	char *request_answer = getRequest(a);

	printf("%s\n", request_answer);

	free(request_answer);

	return 0;
}