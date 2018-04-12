#ifndef CONTROLLER_H
#define CONTROLLER_H

/*** Prototypes for the functions ***/

// Gets the dicipline's identificator
char* getDisciplineID(char request[]);

// Gets the type of the request
char* getRequestType(char request[]);

/* Parses given request of type "request_prefix request_type", in which request_prefix
 * may be "All" or the id of a single discipline */
char* getRequest(char request[]);


#endif
