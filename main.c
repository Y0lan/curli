#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include "main.h"
char * now(){
    time_t now;
    time(&now);
    return ctime(&now);
}
int main(int argc, char ** argv){
    daemon(0,0);
    while (1){
        sleep(200);
        break;
    }
    return 0;
}
