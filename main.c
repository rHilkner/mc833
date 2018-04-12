#include <stdio.h>
#include <stdlib.h>
#include "controller.h"

int main() {
	char a[] = "MC833 menu\0";
	char *request_answer = getRequest(a);

	printf("%s\n", request_answer);

	free(request_answer);

	return 0;
}
