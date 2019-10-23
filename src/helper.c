#include "../include/main.h"
char * now(){
    time_t now;
    time(&now);
    return ctime(&now);
}
char * getHomePath(){
    char * homedir;

    if ((homedir = getenv("HOME")) == NULL) {
        homedir = getpwuid(getuid())->pw_dir;
    }
    return homedir;
}
void debug(char * message){
    fprintf(stderr,"\n%s",message);
}
