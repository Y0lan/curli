#include "include/main.h"
char * now()
{
    time_t now;
    time(&now);
    return ctime(&now);
}
char * getConfigPath(char * str)
{
    strcpy(str,getHomePath());
    strcat(str,CONFIG_PATH);
    return str;
}

char * getConfigFilePath(char * str)
{
    strcpy(str,getHomePath());
    strcat(str,CONFIGURATION_FILE);
    return str;
}

char * getHomePath()
{
    char * homedir;

    if ((homedir = getenv("HOME")) == NULL) {
        homedir = getpwuid(getuid())->pw_dir;
    }
    return homedir;
}
void debug(char * message)
{
    fprintf(stderr,"\n%s",message);
}
void showTasks(struct_tasks * tasks)
{
    uint i, j, z;
    for (i = 0; i < tasks->numberOfTasks; i++) {
        printf("\n <<< TASK >>>\n\n");
        printf("\nseconds of tasks->%d : %lld", i+1, tasks->task[i].second);
        printf("\nnumber of actions for tasks->%d : %d", i+1, tasks->task[i].numberOfActions);
        for( j = 0 ; j < tasks->task[i].numberOfActions; j++) {
            printf("\ntask : %d have action: \n",i+1,j);
            printf("\nname: %s", tasks->task[i].actions[j].name);
            printf("\nurl: %s",tasks->task[i].actions[j].url);
            printf("\nversioning : %d", tasks->task[i].actions[j].versioning);
            printf("\nmax-depth : %d", tasks->task[i].actions[j].max_depth);
            for( z = 0; z < tasks->task[i].actions[j].numberOfTypes; z++) {
                printf("\ntype: %s",tasks->task[i].actions[j].type[z]);
            }
        }
    }

}