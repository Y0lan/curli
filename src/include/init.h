#ifndef CURLI_INIT_H
#define CURLI_INIT_H

void writeTemplateConfiguration(FILE * configuration);
void showMan();
int checkConfigurationExists(char *, char *);
void openEditorForConfigurationFile();
void writeConfigurationFirstTime();
int createConfigurationFile(char *, char *);
FILE * openConfigurationFile(char *);
void getOptions(int argc, char ** argv);
int initApp(char *, char *);

#endif //CURLI_INIT_H
