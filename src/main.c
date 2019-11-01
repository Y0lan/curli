#include "include/main.h"
int main(int argc, char ** argv)
{
    char * configPath = malloc(sizeof(char) * 180);
    char * configFilePath = malloc(sizeof(char) * 180);
    getConfigPath(configPath);
    getConfigFilePath(configFilePath);
    getOptions(argc, argv);
    FILE * configurationFile = NULL;
    if(initApp(configPath, configFilePath) == 1) return 1; /* could not initialize the app */
    //daemon(0,0);
    while (1) {
        configurationFile = openConfigurationFile(configFilePath); /* open with r+ */

        if(configurationFile == NULL) return 1; /* There have been a problem opening the file */
        task * tasks = NULL;
        action * actions = NULL;
        readConfigurationFile(configurationFile, tasks, actions);
//        readConfigurationFile(configurationFile);
        //char ** strConf = confToStr(configurationFile); /* get all lines from the config files */
        //removeAllComments(strConf); /* remove the comments from strConf */


        //int nbOfTasks = countNbTask(strConf);
        //int nbOfActions = countNbAction(strConf);
        //task * task = malloc(sizeof(task) * nbOfTasks);
        //action * action = malloc(sizeof(action) * nbOfActions);




        //freeStrConf(strConf);




        fclose(configurationFile);
        return 0;
    }

}
