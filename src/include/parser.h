#ifndef CURLI_PARSER_H
#define CURLI_PARSER_H

#include "main.h"


void readConfigurationFile(FILE *, struct_tasks *, struct_actions *);
int isKeyActionValid(char *, int);
int long long isNumber(char * s);
int countElementBetweenParenthesis(char * line);
#endif //CURLI_PARSER_H
