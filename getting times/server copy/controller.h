#ifndef CONTROLLER_H
#define CONTROLLER_H

#import "server.h"

// Parses given request of type "request_prefix request_type", in which request_prefix
// may be "All" or the id of a single discipline
extern char* getRequest(char request[], skt *socket);

// Returns list of possible commands
extern char* getCommands();

// Adds commentary to a discipline
extern char* addCommentary(char *commentary, skt *socket);


#endif
