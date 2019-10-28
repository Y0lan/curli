#ifndef CURLI_PARSER_H
#define CURLI_PARSER_H
void getActions(FILE *);
char ** confToStr(FILE *);
void freeStrConf(char **);
void removeAllComments(char **);
#endif //CURLI_PARSER_H
