#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "services.h"
#include "database.h"

extern discipline *disciplines;
static int MSG_MAX_SIZE = 2048;

// Gets the list of all discipline ids with its titles
char* getAllDisciplinesList() {
	// Initializing string
	char *disciplines_list = NULL;
	disciplines_list = malloc(2 * sizeof(char));
	disciplines_list[0] = '\0';

	// Getting number of elements in disciplines array
	int db_length = sizeof(disciplines)/sizeof(discipline);

	// Searching for discipline with given id
	for (i = 0; i < db_length; i++) {
		disciplines_list = realloc(disciplines_list, (strlen(disciplines_list) +
													  strlen(disciplines[i].id) +
													  strlen(disciplines[i].title) + 4) * sizeof(char));
		strcat(disciplines_list, disciplines[i].id);
		strcat(disciplines_list, " - ");
		strcat(disciplines_list, disciplines[i].title);
		strcat(disciplines_list, "\n");
	}

	strcat(disciplines_list, "\n");

	return disciplines_list;
}


// Gets discipline informartion for all disciplines
char* getAllDisciplinesInfos() {
	char *disciplines_infos = NULL;
	disciplines_infos = malloc(1 * sizeof(char));
	disciplines_infos[0] = '\0';

	// Getting number of elements in disciplines array
	int db_length = sizeof(disciplines)/sizeof(discipline);

	// Searching for discipline with given id
	for (i = 0; i < db_length; i++) {
		char* disc_info = getDisciplineInfo(disciplines[i]);

		disciplines_infos = (*char) realloc(disciplines_infos, (strlen(disciplines_infos) +
																strlen(disc_info)) * sizeof(char));

		strcat(disciplines_infos, disc_info);

		free(disc_info);
	}

	return disciplines_infos;
}


// Gets all information of discipline with given id
char* getDisciplineInfo(char discipline_id[]) {
	// Finding discipline by id and getting its information
	discipline disc = findDiscipline(discipline_id);
	return getDisciplineInfo(disc);
}

// Gets discipline info for given discipline
char* getDisciplineInfo(discipline* disc) {
	char *discipline_info;

	discipline_info = malloc((strlen(disc->id) + strlen(disc->title) + strlen(disc->menu)
							 + strlen(disc->schedule) + strlen(disc->commentary) + 100) * sizeof(char));

	// Return discipline info as string:
	// "disc.id - disc.title\n"
	// "- Menu: disc.menu\n"
	// "- Schedule: disc.schedule\n"
	// "- Commentary: disc.commentary\n\n"

	strcpy(discipline_info, disc.id);
	strcat(discipline_info, , " - ");
	strcat(discipline_info, , disc.title);
	strcat(discipline_info, , "\n");
	strcat(discipline_info, , "- Menu: ");
	strcat(discipline_info, , disc.menu);
	strcat(discipline_info, , "\n");
	strcat(discipline_info, , "- Schedule: ");
	strcat(discipline_info, , disc.schedule);
	strcat(discipline_info, , "\n");
	strcat(discipline_info, , "- Commentary: ");
	strcat(discipline_info, , disc.commentary);
	strcat(discipline_info, , "\n\n");

	return discipline_info;
}


// Gets title of discipline with given id
char* getDisciplineTitle(char discipline_id[]) {
	char *discipline_title;
	discipline *disc = getDiscipline(discipline_id);

	discipline_info = malloc(strlen(disc->title) + 20, sizeof(char));
	
	strcpy(discipline_title, "- Title: ");
	strcat(discipline_title, disc->title);
	strcat(discipline_title, "\n\n");

	return discipline_title;
}


// Gets menu of discipline with given id
char* getDisciplineMenu(char discipline_id[]) {
	char discipline_menu[2048];
	
	strcpy(discipline_menu, "- Menu: ");
	discipline *disc = getDiscipline(discipline_id);
	strcat(discipline_menu, disc->menu);
	strcat(discipline_menu, "\n\n");

	return discipline_menu;
}


// Gets schedule of discipline with given id
char* getDisciplineSchedule(char discipline_id[]) {
	char discipline_schedule[2048];
	
	strcpy(discipline_schedule, "- Schedule: ");
	discipline *disc = getDiscipline(discipline_id);
	strcat(discipline_schedule, disc->schedule);
	strcat(discipline_schedule, "\n\n");

	return discipline_schedule;
}


// Gets commentary of discipline with given id
char* getDisciplineCommentary(char discipline_id[]) {
	char discipline_commentary[2048];

	strcpy(discipline_commentary, "- Commentary: ");
	discipline *disc = getDiscipline(discipline_id);
	strcat(discipline_commentary, disc->commentary);
	strcat(discipline_commentary, "\n\n");

	return discipline_commentary;
}


// Sets commentary of discipline with given id
char* setDisciplineCommentary(char discipline_id[], char discipline_commentary[]) {
	char return_string[2048];

	discipline *disc = getDiscipline(discipline_id);

	if (*disc == NULL) {
		strcpy(return_string, "- WARNING: Given discipline couldn't be found in database.\n\n");
		return return_string;
	}

	disc->commentary = malloc(strlen(discipline_commentary) * sizeof(char));
	strcpy(disc->commentary, discipline_commentary);

	strcpy(return_string, "-> Commentary was successfully added to the database.\n\n");

	return return_string;
}


discipline* findDiscipline(char discipline_id[]) {

	// Getting number of elements in disciplines array
	int db_length = sizeof(disciplines)/sizeof(discipline);

	// Searching for discipline with given id
	for (i = 0; i < db_length; i++) {
		if (strcmp(disciplines[i].id, discipline_id) == 0) {
			return &disciplines[i];
		}
	}

	return NULL;
}
