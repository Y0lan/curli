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
