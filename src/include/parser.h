#ifndef CURLI_PARSER_H
#define CURLI_PARSER_H

#include "main.h"

char ** confToStr(FILE *);
void freeStrConf(char **);
void removeAllComments(char **);
int countNbTask(char ** conf);
int countNbAction(char ** conf);
void readConfigurationFile(FILE *);
void checkFileForSyntaxError(FILE * f, task *, action *);

#endif //CURLI_PARSER_H
