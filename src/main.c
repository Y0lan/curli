#include "include/main.h"

int main(int argc, char ** argv)
{
    char *configPath = malloc(sizeof(char) * 180);
    char *configFilePath = malloc(sizeof(char) * 180);
    getConfigPath(configPath);
    getConfigFilePath(configFilePath);
    getOptions(argc, argv);
    FILE *configurationFile = NULL;
    if (initApp(configPath, configFilePath) == 1) {
        free(configFilePath);
        free(configPath);
        return 1; /* could not initialize the app */
    }
    //daemon(0,0);
    configurationFile = openConfigurationFile(configFilePath); /* open with r+ */
    if (configurationFile == NULL) {
        free(configFilePath);
        free(configPath);
        return 1; /* There have been a problem opening the file */
    }
    struct_tasks tasks = {0};
    struct_actions actions = {0};
    actions.action = malloc(sizeof(struct_action));
    readConfigurationFile(configurationFile, &tasks, &actions);
    fclose(configurationFile);
    /* work here */
    //printf("total number of actions : %d", actions.numberOfActions);

    /* THREADS */

    u_int i, j, z;
    int ret;
    for(i = 0; i < tasks.numberOfTasks; i++) {
        pthread_t threadTask;
        ret = pthread_create(&threadTask, NULL, threadTaskFunc,&tasks.task[i]);
        if(ret == 0) pthread_join(threadTask,NULL);
    }

    /* DEBUGGING */
    /*
    for (i = 0; i < tasks.numberOfTasks; i++) {
        printf("\nseconds of tasks %d : %lld", i+1, tasks.task[i].second);
        printf("\nnumber of actions for tasks %d : %d", i+1, tasks.task[i].numberOfActions);
        for( j = 0 ; j < tasks.task[i].numberOfActions; j++) {
            printf("\ntask : %d have action: \n",i,j);
            printf("\nname: %s", tasks.task[i].actions[j].name);
            printf("\nurl: %s",tasks.task[i].actions[j].url);
            printf("\nversioning : %d", tasks.task[i].actions[j].versioning);
            printf("\nmax-depth : %d", tasks.task[i].actions[j].max_depth);
            for( z = 0; z < tasks.task[i].actions[j].numberOfTypes; z++) {
                printf("\ntype: %s",tasks.task[i].actions[j].type[z]);
            }

        }
    }
     */

    for (i = 0; i < actions.numberOfActions; i++) {
        free(actions.action[i].name);
        free(actions.action[i].url);
        for (u_int j = 0; j < actions.action[i].numberOfTypes; j++) {
            free(actions.action[i].type[j]);
        }
    }

    return 0;
}
