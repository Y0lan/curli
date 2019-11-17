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
    while (1) {
        configurationFile = openConfigurationFile(configFilePath); /* open with r+ */
        if (configurationFile == NULL) return 1; /* There have been a problem opening the file */
        struct_tasks tasks;
        struct_tasks *p_tasks = &tasks;
        struct_actions actions;
        struct_actions *p_actions = &actions;
        p_actions->action = malloc(sizeof(struct_action));
        readConfigurationFile(configurationFile, p_tasks, p_actions);
        fclose(configurationFile);
        /* work here */
        printf("total number of actions : %d", actions.numberOfActions);
        u_int i;
        for (i = 0; i < tasks.numberOfTasks; i++) {
            printf("\nseconds of tasks %d : %lld", i+1, tasks.task[i].second);
            printf("\nnumber of actions for tasks %d : %d", i+1, tasks.task[i].numberOfActions);
        }
        for (i = 0; i < actions.numberOfActions; i++) {
            printf("\naction number %d : ", i + 1);
            //printf("\nname : %s", actions.action[i].name);
            //printf("\nurl : %s",actions.action[i].url);
            printf("\ndepth : %d",actions.action[i].max_depth);
            //printf("\nversioning : %d",actions.action[i].versioning);
            //printf("\ntype: %s",actions.action[i].type[0]);
        }
        return 0;
    }
}
