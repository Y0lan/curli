#ifndef CURLI_HELPER_H
#define CURLI_HELPER_H

#include "main.h"

char * now();
char * getHomePath();
void debug(char * message);
char * getConfigPath(char * );
char * getConfigFilePath(char * );
void showTasks(struct_tasks *);
#endif //CURLI_HELPER_H
