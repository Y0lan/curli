#include "include/main.h"
int main(int argc, char ** argv){
    getOptions(argc, argv);
    FILE * configurationFile = NULL;
    //daemon(0,0);
    while (1){
    if(initApp(configurationFile) == 1) return 1;

    return 0;
    }
}
