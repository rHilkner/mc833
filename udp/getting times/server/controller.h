#ifndef CONTROLLER_H
#define CONTROLLER_H

// Parses given request of type "request_prefix request_type <user_permission> <commentary>",
// in which request_prefix may be "All" or the id of a single discipline and <> are optional
extern char* getRequest(char request[]);


#endif
