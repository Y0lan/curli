#include "include/main.h"

void writeTemplateConfiguration(FILE * configuration)
{
    char * template = "# this is an example"
    "\n# you can comment everything to use this template as example"
    "\n# or you can delete everything and start blank"
    "\n# if you need help, you can launch the program with --help"
    "\n# have fun !"
    "\n"
    "\n# simple scrawling, depth = 0, versioning = off, every type scrawled;"
    "\n="
    "\n{name->First website}"
    "\n{url->www.website.tld}"
    "\n# advanced scrawling of only gif and text of a website following 2 links at a time"
    "\n="
    "\n{name->Second website}"
    "\n{url->www.secondwebsite.tld}"
    "\n+"
    "\n{max-depth->2}"
    "\n{type->(text/html,image/gif)"
    "\n"
    "\n# First action that run every 2 minutes"
    "\n=="
    "\n{name->my action}"
    "\n{minute->2}"
    "\n+"
    "\n(First website) # the name must be of an existing task"
    "\n"
    "\n# Second action that run every day and half"
    "\n=="
    "\n{name->my second action} # must be different from first action"
    "\n{day->1}"
    "\n{hour->12}"
    "\n+"
    "(First website, Second website)";
    if(configuration) {
        fputs(template, configuration);
    }
}
void showMan()
{
    printf("CURLI"
           "\n\nNAME"
           "\n\tcurli - Curl, improved"
           "\n\nSYNOPSIS"
           "\n\tcurli [-c]"
           "\n\tOpen configuration file in $EDITOR (do this the first time it runs)"
           "\n\nDESCRIPTION"
           "\n\tWhen you invoke curli, it normally read a configuration file and follow the "
           "\n\tinstruction in it to"
           "\n\tscrawl data from specific sites. You can specify in the configuration"
           "\n\tfile multiple websites to be scrawled."
           "\n\tYou can choose to run each tasks once or specify when it should run "
           "\n\t(every h hours, m minutes...)."
           "\n\tYou can specify what datatype you want to scrawl."
           "\n\tYou can specify how deep in the website you want to scrawl."
           "\n\nOPTIONS"
           "\n\tHow to write in the config file"
           "\n\tYou have to first write action at the top of the config file, and you can add option "
           "\n\tto each action (optionnal)."
           "\n\tThen you need to write tasks. Tasks are one or multiple actions."
           "\n\tYou have to specify when the tasks should run."
           "\n\n\tYou can write a comment with : \t #"
           "\n\tExample : # Task to grab google.com"
           "\n\n\tYou can add option or attribute with : \t {options/attributes name->value}"
           "\n\n\tExample : {name->get google}\n\t{url->www.google.com}"
           "\n\n\tYou should begin each action with : \t ="
           "\n\n\tYou should give a name, and an url to your action"
           "\n\n\tExample:"
           "\n\t\t# Action 1 to get google"
           "\n\t\t="
           "\n\t\t{name->get google}"
           "\n\t\t{url->www.google.com}"
           "\n\n\tYou have different option that you can add to your actions"
           "\n\tTo add options to your actions, you should write: \t +"
           "\n\tList and description of options available for actions :"
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
           "\n\ttype (MIME type1, MIME type2,...)"
           "\n\n\t\tExample:"
           "\n\t\ttype->[text/html,image/jpeg]"
           "\n\n\tWill only scrawl the text and the image of the website."
           "\n\n\tFull example of an action: "
           "\n\t\t# Action 1 to get only image and video from imgur"
           "\n\t\t="
           "\n\t\t{name->get img and video from imgur}"
           "\n\t\t{url->imgur.com/AeZ1dje"
           "\n\t\t+"
           "\n\t\t{max->1}"
           "\n\t\t{type->(image/jpeg,image/gif,image/png,video/mpeg,video/ogg,video/webm)"
           "\n\n\tThis is an action, but nothing will happen if you run curli, because curli runs TASKS"
           "\n\tA task is a list of multiple actions."
           "\n\tYou can add option to tasks."
           "\n\n\tHere is the list of options available for task:"
           "\n\n\t\t[month,week,day,hour,minute,second] numbers"
           "\n\n\tExample of a task ran every 4 hours: "
           "\n\t\t{hour->4}"
           "\n\n\tExample of a task ran every 2 days and 15 minutes: "
           "\n\t\t{day->2}"
           "\n\t\t{minute->15}"
           "\n\n\tTo differenciate task (one or multiple actions) from action,"
           "\n\twe use == before task. "
           "\n\tThe name of the action called in a task should match EXACTLY the name of the action(s) requested"
           "\n\tlike you declared it at the top of the file."
           "\n\n\tExample:"
           "\n\t\t=="
           "\n\t\t{name->my task with my random name that run every 16 minutes}"
           "\n\t\tminute->16"
           "\n\t\t+"
           "\n\t\t(get img and video from imgur, get google)"
           "\n\nCURLI\t\t\t2019\n\n");
}
int checkConfigurationExists(char * configFile, char * configFilePath)
{

    if(ENOENT == errno) {
        debug("Not able to open configuration directory");
        return -1;
    }
    FILE * file = fopen(configFilePath,"r"); /* open the file in r mode so that it only check if it exists without making it*/
    if(file == NULL) {
        debug("not able to open configuration file");
        return 1;
    } /* file does not exist */
    return 0; /* file does exist */
}
void openEditorForConfigurationFile()
{
    system("clear");
    if(getenv("EDITOR") == NULL) system("nano ~/.config/curli/conf.sconf");
    else system("$EDITOR ~/.config/curli/conf.sconf");
}
void writeConfigurationFirstTime()
{
    char choice;
    printf("\nDo you want to write your first config file? (Y/n)");
    choice = (char) fgetc(stdin);
    if(choice == 'Y' || choice == 'y') {
        openEditorForConfigurationFile();
    } else {
        return;
    }
}
int createConfigurationFile(char * configPath, char * configFilePath)
{
    /* check if directory for file configuration */
    DIR * dir = opendir(configPath);
    if(dir) { /* directory for the config file exist */
        debug("directory for the config file exists");
        closedir(dir);
    } else if(ENOENT == errno) {
        debug("config path does not exist, making it");
        mkdir(configPath,  S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH); /* read/write/search permissions for owner and group, and with read/search permissions for others */
    } else return -1; /* mkdir failed for other reason */

    /* put file configuration in directory */
    FILE * file = fopen(configFilePath, "w"); /* write : create the file if it does not exist */
    printf("\nconfig created...");
    if(file == NULL) { /* there have been an error while opening the file */
        debug("A problem happened while opening the configuration file");
        return 1;
    }
    writeTemplateConfiguration(file);
    fclose(file);
    showMan();
    writeConfigurationFirstTime();
    return 0; /* no errors happened */
}
FILE * openConfigurationFile(char * configurationFile)
{
    return fopen(configurationFile,"r+");
}
void getOptions(int argc, char ** argv)
{
    if(argc > 1) {
        if(strcmp(argv[1],"--help") == 0) {
            showMan();
            return;
        }
    }
}
int initApp(char * configPath, char * configFilePath)
{
    if(checkConfigurationExists(configPath, configFilePath) NOTOK) { /* the path or the file does not exist */
        printf("Path does not exist...");
        if(createConfigurationFile(configPath, configFilePath) NOTOK) return 1; /* could not make the path nor the file */
    }
    return 0;
}
