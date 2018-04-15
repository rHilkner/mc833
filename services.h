#ifndef SERVICES_H
#define SERVICES_H

// Gets the list of all discipline ids with its titles
extern char* getAllDisciplinesList();

// Gets discipline informartion for all disciplines
extern char* getAllDisciplinesInfos();

// Gets all information of discipline with given id
extern char* getDisciplineInfo(char discipline_id[]);

// Gets title of discipline with given id
extern char* getDisciplineTitle(char discipline_id[]);

// Gets menu of discipline with given id
extern char* getDisciplineMenu(char discipline_id[]);

// Gets schedule of discipline with given id
extern char* getDisciplineSchedule(char discipline_id[]);

// Gets commentary of discipline with given id
extern char* getDisciplineCommentary(char discipline_id[]);

// Sets commentary of discipline with given id
extern char* setDisciplineCommentary(char discipline_id[]);


#endif
