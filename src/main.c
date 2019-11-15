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
        struct_tasks tasks;
        struct_tasks * p_tasks = &tasks;
        struct_actions actions;
        struct_actions * p_actions = &actions;
        p_actions = malloc(sizeof(struct_actions));
        p_actions->action = malloc(sizeof(struct_action));
        printf("\noriginal address of p_actions->action : %p",&p_actions->action[0]);

        readConfigurationFile(configurationFile, p_tasks, p_actions);
        fclose(configurationFile);
        /* work here */
        for( int i = 0; i < actions.nbActions; i++) {
            printf("actions %d : "
                   "\n\tname : %s "
                   "\n\turl :  %s "
                   "\n\tmax-depth : %d"
                   "\n\tversioning : %d"
                   "\n\ttypes : %s",i,actions.action[i].name, actions.action[i].url, actions.action[i].max_depth, actions.action[i].versioning, actions.action[i].type[0]);
        }
        return 0;
    }

}
