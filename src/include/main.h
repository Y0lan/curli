#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <pwd.h>
#include <string.h>
#include <stdlib.h>
#include <dirent.h>
#include <errno.h>
#include <sys/stat.h>
#include "helper.h"
#include "init.h"
#include "parser.h"
#include "struct.h"
#define CONFIG_PATH "/.config/curli"
#define CONFIGURATION_FILE "/.config/curli/conf.sconf"
#define OK == 0 /* function is true */
#define NOTOK !=  0  /* function is false */
#define TASK 2
#define ACTION 1

