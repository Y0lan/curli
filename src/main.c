#include "include/main.h"

int main(int argc, char ** argv)
{
    char *configPath = malloc(sizeof(char) * 180);
    char *configFilePath = malloc(sizeof(char) * 180);
    getConfigPath(configPath);
    getConfigFilePath(configFilePath);
    getOptions(argc, argv);
    FILE *configurationFile = NULL;
    if (initApp(configPath, configFilePath) == 1) return 1; /* could not initialize the app */
    //daemon(0,0);
    configurationFile = openConfigurationFile(configFilePath); /* open with r+ */
    if (configurationFile == NULL) return 1; /* There have been a problem opening the file */
    struct_tasks tasks = {0};
    struct_actions actions = {0};
    actions.action = malloc(sizeof(struct_action));
    readConfigurationFile(configurationFile, &tasks, &actions);
    fclose(configurationFile);
    /* work here */
    printf("total number of actions : %d", actions.numberOfActions);




    /* THREADS */

    int ret;
    u_int i;

    /* create thread for the clock */
    pthread_t threadClock;
    ret = pthread_create(&threadClock,NULL, threadClock,&tasks);
    if(!ret) pthread_join(threadClock,NULL);


    /* DEBUGGING */
    /*
    for (i = 0; i < tasks.numberOfTasks; i++) {
        printf("\nseconds of tasks %d : %lld", i+1, tasks.task[i].second);
        printf("\nnumber of actions for tasks %d : %d", i+1, tasks.task[i].numberOfActions);
    }
    for (i = 0; i < actions.numberOfActions; i++) {
        printf("\naction number %d : ", i + 1);
        printf("\nname : %s", actions.action[i].name);
        printf("\nurl : %s",actions.action[i].url);
        printf("\ndepth : %d",actions.action[i].max_depth);
        printf("\nversioning : %d",actions.action[i].versioning);
        printf("\nnumber of types: %d", actions.action[i].numberOfTypes);
        for(u_int j = 0; j < actions.action[i].numberOfTypes; j++) {
            printf("\ntypes : %s", actions.action[i].type[j]);
        }
        NULL;
    }*/
    return 0;
}
