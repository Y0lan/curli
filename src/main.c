#include "include/main.h"
int main(int argc, char ** argv)
{
    getOptions(argc, argv);
    FILE * configurationFile = NULL;
    if(initApp(configurationFile) == 1) return 1; /* could not initialize the app */
    //daemon(0,0);
    while (1) {
        configurationFile = openConfigurationFile(); /* open with r+ */
        if(configurationFile == NULL) return 1; /* There have been a problem opening the file */
        char ** strConf = confToStr(configurationFile);
        freeStrConf(strConf);




        fclose(configurationFile);
        return 0;
    }
}
