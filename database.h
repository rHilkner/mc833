#ifndef DATABASE_H
#define DATABASE_H

// Gets the list of all discipline ids with its titles
typedef struct disc {
   char* id;
   char* title;
   char* menu;
   char* schedule;
   char* commentary;
} discipline;

extern discipline* disciplines;

#endif
