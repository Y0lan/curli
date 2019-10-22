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
#define CONFIG_PATH "/home/yolan/.config/curli"
#define CONFIGURATION_FILE "/home/yolan/.config/curli/conf.sconf"
#define OK == 0 /* function is true */
#define NOTOK !=  0  /* function is false */
void showMan(){
    printf("CURLI"
           "\n\nNAME"
           "\n\tcurli - Curl, improved"
           "\n\nSYNOPSIS"
           "\n\tcurli [-c]"
           "\n\tOpen configuration file in $EDITOR (do this the first time it runs)"
           "\n\nDESCRIPTION"
           "\n\tWhen you invoke curli, it normally read a configuration file and follow the instruction in it to"
           "\tscrawl data from specific sites. You can specify in the configuration file multiple websites to be scrawled."
           "\n\tYou can choose to run each tasks once or specify when it should run (every h hours, m minutes...)."
           "\n\tYou can specify what datatype you want to scrawl."
           "\n\tYou can specify how deep in the website you want to scrawl."
           "\n\nOPTIONS"
           "\n\tHow to write in the config file"
           "\n\tYou have to first write action at the top of the config file, and you can add option "
           "\n\tto each action (optionnal)."
           "\n\tThen you need to write tasks. Tasks are one or multiple actions."
           "\n\tYou have to specify when the tasks should run."
           "\n\n\tYou can write a comment with : \t #"
           "\n\tExample : # Action to grab google.com"
           "\n\n\tYou can add option or attribute with : \t {options/attributes name->value}"
           "\n\n\tExample : {name->get google}\n\t{url->www.google.com}"
           "\n\n\tYou should begin each task with : \t ="
           "\n\n\tYou should give a name, and an url to your task"
           "\n\n\tExample:"
           "\n\t\t# Task 1 to get google"
           "\n\t\t="
           "\n\t\t{name->get google}"
           "\n\t\t{url->www.google.com}"
           "\n\n\tYou have different option that you can add to your tasks"
           "\n\tTo add options to your tasks, you should write: \t +"
           "\n\tList and description of options available for tasks :"
           "\n\n\tMAX-DEPTH"
           "\n\t\tmax-depth [number]"
           "\n\tExample : "
           "\n\t\t{max-depth->6}"
           "\n\tSpecify how deep curli is allowed to go following links from the base url."
           "\n\t\t0 = no link followed. "
           "\n\t\tmax = no limit "
           "\n\n\tVERSIONING : "
           "\n\t\tversioning on/off"
           "\n\t\tExample : {versioning->on}"
           "\n\t\t" //TODO comprendre le versioning et l'expliquer ici
           "\n\nTYPE"
           "\n\t\ttype (MIME type1, MIME type2,...)"
           "\n\t\tExample:"
           "\n\t\ttype->[text/html,image/jpeg]"
           "\n\tWill only scrawl the text and the image of the website."
           "\n\n\tFull example of a task: "
           "\n\t\t# Task 1 to get only image and video from imgur"
           "\n\t\t="
           "\n\t\t{name->get img and video from imgur}"
           "\n\t\t{url->imgur.com/AeZ1dje"
           "\n\t\t+"
           "\n\t\t{max->1}"
           "\n\t\t{type->(image/jpeg,image/gif,image/png,video/mpeg,video/ogg,video/webm)"
           "\n\n\tThis is a task, but nothing will happen if you run curli, because curli runs ACTIONS"
           "\n\tAn action is a list of multiple tasks."
           "\n\tYou can add option to actions."
           "\n\\ntHere is the list of options available for action:"
           "\n\n\t\t[month,week,day,hour,minute,second] numbers"
           "\n\n\tExample of an action ran every 4 hours: "
           "\n\t\t{hour->4}"
           "\n\n\tExample of an action ran every 2 days and 15 minutes: "
           "\n\t\t{day->2}"
           "\n\t\t{minute->15}"
           "\n\n\tTo differenciate action (one or multiple tasks) from tasks, we use == before action. "
           "\n\tThe name of the tasks in action should match EXACTLY the name of the task(s) requested."
           "\n\n\tExample:"
           "\n\t\t=="
           "\n\t\t{name->my actions with my random name that run every 16 minutes}"
           "\n\t\tminute->16"
           "\n\t\t+"
           "\n\t\t(get img and video from imgur, get google)"
           "\n\nCURLI\t\t\t2019\n\n");
}
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
    if(ENOENT == errno){
        debug("Not able to open configuration directory");
        return -1;
    }
    FILE * file = fopen(CONFIGURATION_FILE,"r"); /* open the file in r mode so that it only check if it exists without making it*/
    if(file == NULL){
        debug("not able to open configuration file");
        return 1;
    } /* file does not exist */
    return 0; /* file does exist */
}
void openEditorForConfigurationFile(){
    system("clear");
    if(getenv("EDITOR") == NULL) system("nano ~/.config/curli/conf.sconf");
    else system("$EDITOR ~/.config/curli/conf.sconf");
}
void writeConfigurationFirstTime(){
    char choice;
    printf("\nDo you want to write your first config file? (Y/n)");
    choice = (char) fgetc(stdin);
    if(choice == 'Y' || choice == 'y'){
        openEditorForConfigurationFile();
    }
    else {
        return;
    }
}
int createConfigurationFile(){
    /* check if directory for file configuration */
    DIR * dir = opendir(CONFIG_PATH);
    if(dir){/* directory for the config file exist */
        debug("directory for the config file exists");
        closedir(dir);
    }
    else if(ENOENT == errno) {
        debug("config path does not exist, making it");
        mkdir(CONFIG_PATH,  S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH); /* read/write/search permissions for owner and group, and with read/search permissions for others */
    }
    else return -1; /* mkdir failed for other reason */

    /* put file configuration in directory */
    FILE * file = fopen(CONFIGURATION_FILE, "w"); /* write : create the file if it does not exist */
    printf("\nconfig created...");
    if(file == NULL) { /* there have been an error while opening the file */
        debug("A problem happened while opening the configuration file");
        return 1;
    }
    fclose(file);
    showMan();
    writeConfigurationFirstTime();
    return 0; /* no errors happened */
}
FILE * openConfigurationFile(){
    return fopen(CONFIGURATION_FILE,"w");
}
int main(int argc, char ** argv){
    if(argc > 1) {
        if(strcmp(argv[1],"--help") == 0){
            showMan();
            return 0;
        }
    }
    FILE * configurationFile;
    //daemon(0,0);
    while (1){
        if(checkConfigurationExists() NOTOK){
            if(createConfigurationFile() NOTOK) return 1;
        }
        configurationFile = openConfigurationFile();
        if(configurationFile == NULL) return 1; /* There have been a problem opening the file */
        else{
            return 0;
        }
    }
}
