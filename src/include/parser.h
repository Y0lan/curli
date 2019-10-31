#ifndef CURLI_PARSER_H
#define CURLI_PARSER_H
char ** confToStr(FILE *);
void freeStrConf(char **);
void removeAllComments(char **);
int countNbTask(char ** conf);
int countNbAction(char ** conf);
void readConfigurationFile(FILE *);
void checkFileForSyntaxError(FILE * f);
typedef struct action {
    char * name;
    char * url;
    unsigned int max_depth;
    unsigned short versioning;
    char ** type;
} action;

typedef struct task {
    action * actions;
    unsigned long  second; /* Let's say that we will count the time before each action in second */
} task;

#endif //CURLI_PARSER_H
