#include "error.h"

void error_manager(const char* message){
	printf(message);
	printf("\n");
	exit(EXIT_FAILURE);
}
