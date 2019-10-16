#include <stdio.h>
#include <time.h>
#include "main.h"
char * now(){
    time_t now;
    time(&now);
    return ctime(&now);
}
int main(int argc, char ** argv){
    printf("%s",now());
    return 0;
}
