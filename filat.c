
#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
    struct stat attributes;
    if(argc != 2){
        printf ("Usage: filat path");
        return 1;
    }
    lstat(argv[1],&attributes);
    fprintf(stdout, "%s\n",argv[1]);
    switch (attributes.st_mode & S_IFMT) {
        case S_IFBLK:  printf("Block special file\n");            break;
        case S_IFCHR:  printf("Character special file\n");        break;
        case S_IFIFO:  printf("FIFO special file\n");               break;
        case S_IFLNK:  printf("Symbolic link file\n");                 break;
        case S_IFREG:  printf("Regular file\n");            break;
        default:       printf("unknown\n");                break;
    }
    fprintf(stdout, "Access privileges\t");
    printf( (S_ISDIR(attributes.st_mode)) ? "d" : "-");
    printf( (attributes.st_mode & S_IRUSR) ? "r" : "-");
    printf( (attributes.st_mode & S_IWUSR) ? "w" : "-");
    printf( (attributes.st_mode & S_IXUSR) ? "x" : "-");
    printf( (attributes.st_mode & S_IRGRP) ? "r" : "-");
    printf( (attributes.st_mode & S_IWGRP) ? "w" : "-");
    printf( (attributes.st_mode & S_IXGRP) ? "x" : "-");
    printf( (attributes.st_mode & S_IROTH) ? "r" : "-");
    printf( (attributes.st_mode & S_IWOTH) ? "w" : "-");
    printf( (attributes.st_mode & S_IXOTH) ? "x" : "-");
    printf("\n");
    fprintf(stdout, "inode-Number\t%ld\n",(long)attributes.st_ino);
    fprintf(stdout, "Device numbers\t%ld\n",attributes.st_rdev);
    fprintf(stdout, "Links Count\t%ld\n",(long)attributes.st_nlink);
    fprintf(stdout, "UID\t%ld\n",(long)attributes.st_uid);
    fprintf(stdout, "GID\t%ld\n",(long)attributes.st_gid);
    fprintf(stdout, "File size\t%lld\n",(long long)attributes.st_size);
    fprintf(stdout, "Last access\t%s",ctime(&attributes.st_atime));
    fprintf(stdout, "Last modification\t%s",ctime(&attributes.st_mtime));
    fprintf(stdout, "Last inode change\t%s",ctime(&attributes.st_ctime));
