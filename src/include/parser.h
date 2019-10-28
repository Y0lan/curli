#ifndef CURLI_PARSER_H
#define CURLI_PARSER_H
void getActions(FILE *);
char ** confToStr(FILE *);
void freeStrConf(char **);
void removeComment(char **);
#endif //CURLI_PARSER_H
