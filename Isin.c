#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <time.h>
#include <pwd.h>

int listDir(const char *dirName)     {
    struct dirent* currentDirectory;
    struct stat my_stat;
    struct tm lt;
    struct passwd *pwd;
    char * permOfFile(mode_t mode);
    char * typeOfFile(mode_t mode);
    DIR* directory = opendir(dirName);
    if(directory == NULL){
        printf("listDir: %s : %s \n", dirName, strerror(errno));
        return 0;
    }
    printf("Directory: %s\n", dirName);
    printf("\n");
    while( (currentDirectory = readdir(directory) ) )     {
        stat(currentDirectory->d_name, &my_stat);
        if ( (stat(currentDirectory->d_name, &my_stat) ) == 0 )    {

            pwd = getpwuid(my_stat.st_uid);
        }
        time_t t = my_stat.st_mtime;
        localtime_r(&t, &lt);
        char timebuf[80];
        strftime(timebuf, sizeof(timebuf), "%c", &lt);
        if (pwd != 0) {
            printf("%s \t %s \t %s \t %ld \t %s \t %s",permOfFile(my_stat.st_mode),typeOfFile(my_stat.st_mode),pwd->pw_name, (long)my_stat.st_size, timebuf, currentDirectory->d_name);
            printf("\n");

        } else  {
            printf("%d \t %ld \t %s \t %s", my_stat.st_uid, (long)my_stat.st_size, timebuf, currentDirectory->d_name);
            printf("\n");
        }
    }
    closedir(directory);
    return 0;
}
int main(int argc, char* argv[]){
    if ( argc == 1 )
        return listDir ( "." );
    else {
        int ret = 0;
        for (int i = 1; i < argc; i += 1 ) {
            if ( listDir ( argv[i] ) != 0 )
                ret = 1;
        }

        return ret;
    }
}
char *permOfFile(mode_t mode)
{
    char * p;
    static char perms[10];
    p = perms;
    strcpy(perms, "---------");
    for (int i = 0; i < 3; i++) {
        if (mode & (S_IREAD >> i*3))
            *p = 'r';
        p++;

        if (mode & (S_IWRITE >> i*3))
            *p = 'w';
        p++;

        if (mode & (S_IEXEC >> i*3))
            *p = 'x';
        p++;
    if ((mode & S_ISUID) != 0)
        perms[2] = 's';
    if ((mode & S_ISGID) != 0)
        perms[5] = 's';
    if ((mode & S_ISVTX) != 0)
        perms[8] = 't';
    return(perms);
}
char *typeOfFile(mode_t mode)
{
    switch (mode & S_IFMT) {
        case S_IFREG:
            return("-");
        case S_IFDIR:
            return("d");
        case S_IFCHR:
            return("c");
        case S_IFBLK:
            return("b");
        case S_IFLNK:
            return("l");
        case S_IFIFO:
            return("f");
        case S_IFSOCK:
            return("s");
    }
    return("?");
}
