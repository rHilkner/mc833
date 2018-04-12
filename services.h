#ifndef SERVICES_H
#define SERVICES_H

/*** Prototypes for the functions ***/

// Gets the list of all discipline ids with its titles
char* getAllDisciplinesList();

// Gets discipline informartion for all disciplines
char* getAllDisciplinesInfos();

// Gets all information of discipline with given id
char* getDisciplineInfo(char discipline_id[]);

// Gets title of discipline with given id
char* getDisciplineTitle(char discipline_id[]);

// Gets menu of discipline with given id
char* getDisciplineMenu(char discipline_id[]);

// Gets schedule of discipline with given id
char* getDisciplineSchedule(char discipline_id[]);

// Gets commentary of discipline with given id
char* getDisciplineCommentary(char discipline_id[]);

// Sets commentary of discipline with given id
char* setDisciplineCommentary(char discipline_id[]);


#endif
