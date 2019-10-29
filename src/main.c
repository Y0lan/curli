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
        char ** strConf = confToStr(configurationFile); /* get all lines from the config files */
        removeAllComments(strConf); /* remove the comments from strConf */

        int nbOfTasks = countNbTask(strConf);
        printf("%d", nbOfTasks);



        freeStrConf(strConf);




        fclose(configurationFile);
        return 0;
    }
}
