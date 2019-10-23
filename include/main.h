#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <pwd.h>
#include <string.h>
#include <stdlib.h>
#include <dirent.h>
#include <errno.h>
#include <sys/stat.h>
#include "../include/helper.h"
#include "../include/init.h"
#include "../include/parser.h"
#define CONFIG_PATH "/home/yolan/.config/curli"
#define CONFIGURATION_FILE "/home/yolan/.config/curli/conf.sconf"
#define OK == 0 /* function is true */
#define NOTOK !=  0  /* function is false */

