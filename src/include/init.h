#ifndef CURLI_INIT_H
#define CURLI_INIT_H

void writeTemplateConfiguration(FILE * configuration);
void showMan();
int checkConfigurationExists();
void openEditorForConfigurationFile();
void writeConfigurationFirstTime();
int createConfigurationFile();
FILE * openConfigurationFile();
void getOptions(int argc, char ** argv);
int initApp();
#endif //CURLI_INIT_H
