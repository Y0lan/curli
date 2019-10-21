#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <pwd.h>
#include <string.h>
#include <stdlib.h>
#include <dirent.h>
#include <errno.h>
#include <sys/stat.h>
#include "main.h"
char * now();
char * home();
#define HOMEPATH "/home/yolan"
#define CONFIG_PATH "/home/yolan/.config/curli"
#define CONFIGURATION_FILE "/home/yolan/.config/curli/conf.sconf"
#define OK == 0 /* function is true */
#define NOTOK !=  0  /* function is false */

char * now(){
    time_t now;
    time(&now);
    return ctime(&now);
}
char * getHomePath(){
    char * homedir;

    if ((homedir = getenv("HOME")) == NULL) {
        homedir = getpwuid(getuid())->pw_dir;
    }
    return homedir;
}
void debug(char * message){
    fprintf(stderr,"\n%s",message);
}
int checkConfigurationExists() {
    DIR * dir = opendir(CONFIG_PATH);
    if(dir NOTOK){
        debug("Not able to open configuration directory");
        return -1;
    }
    FILE * file = fopen(CONFIGURATION_FILE,"a");
    if(file NOTOK){
        debug("not open to open configuration file");
        return 1;
    } /* file does not exist */
    return 0; /* file does exist */
}
int createConfigurationFile(){
    /* check if directory for file configuration */
    DIR * dir = opendir(CONFIG_PATH);
    if(dir){
        debug("directory for the config file exists");
        closedir(dir);
    }/* directory for the config file exist */
    else if(ENOENT == errno) {
        debug("config path does not exist, making it");
        mkdir(CONFIG_PATH, 666); /* directory does not exists, so create it */
    }
    else { return -1; } /* mkdir failed for other reason */

    /* put file configuration in directory */
    FILE * file = fopen(CONFIGURATION_FILE, "w"); /* write : create the file if it does not exist */
    if(file == NULL) { /* there have been an error while opening the file */
        debug("A problem happened while opening the configuration file");
        return 1;
    }
    fclose(file);
    return 0; /* no errors happened */
}
FILE * openConfigurationFile(){
    return fopen(CONFIGURATION_FILE,"w");
}
int main(int argc, char ** argv){
    FILE * configurationFile;
    //daemon(0,0);
    while (1){
        debug(HOMEPATH);
        debug(CONFIG_PATH);
        debug(CONFIGURATION_FILE);
        if(checkConfigurationExists() NOTOK){
            if(createConfigurationFile() NOTOK) return 1;
        }
        configurationFile = openConfigurationFile();
        if(configurationFile == NULL) printf("problem creating file");
        else printf("no problem");
        break;
    }
    return 0;
}
