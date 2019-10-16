#include <stdio.h>
#include <pwd.h>
#include <zconf.h>
#include <string.h>
#include <time.h>
#include "main.h"
#define HOME getpwuid(getuid())->pw_dir
char * now(){
    time_t now;
    time(&now);
    return ctime(&now);
}
int main(int argc, char ** argv){
    printf("%s",now());
    return 0;
}
