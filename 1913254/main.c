#include <get_folder_stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/stat.h>
#include <stdint.h>
#include <time.h>

void printTime(time_t time)
{
    char buff[26];
    struct tm *tm_info;
    tm_info = localtime(&time);
    strftime(buff, 26, "%Y-%m-%d %H:%M:%S", tm_info);
    printf("Last access time: %s\n", buff);
}

void prinfPermission(mode_t per)
{
    if (per & S_IRUSR)
    {
        printf("r");
    }
    else printf("-");
    if (per & S_IWUSR)
    {
        printf("w");
    }
    else
        printf("-");
    if (per & S_IXUSR)
    {
        printf("e");
    }
    else
        printf("-");
    printf(" ");
    // Group permission
    if (per & S_IRGRP)
    {
        printf("r");
    }
    else
        printf("-");
    if (per & S_IWGRP)
    {
        printf("w");
    }
    else
        printf("-");
    if (per & S_IXGRP)
    {
        printf("e");
    }
    else
        printf("-");
    printf(" ");
    if (per & S_IROTH)
    {
        printf("r");
    }
    else
        printf("-");
    if (per & S_IWOTH)
    {
        printf("w");
    }
    else
        printf("-");
    if (per & S_IXOTH)
    {
        printf("e");
    }
    else
        printf("-");
    printf(" \n");
}

int main()
{
    char *path = NULL;
    struct folder_stat stat;

    if (get_folder_stat(path, &stat) == 0)
    {
        printf("\nCurrent folder:\n");
        printf("Folder name: %s\n", stat.folder.name);
        printf("Permission: ");
        prinfPermission(stat.folder.permission);
        printf("UID: %d\n", stat.folder.uid);
        printf("GID: %d\n", stat.folder.gid);
        printTime(stat.folder.atime);

        printf("\nParent folder:\n");
        printf("Parent Folder name: %s\n", stat.parent_folder.name);
        printf("Permission: ");
        prinfPermission(stat.parent_folder.permission);
        printf("UID: %d\n", stat.parent_folder.uid);
        printf("GID: %d\n", stat.parent_folder.gid);
        printTime(stat.parent_folder.atime);
	
        printf("\nLast access child folder:\n");
	if(stat.last_access_child_folder.uid != 0){
        printf("Folder name: %s\n", stat.last_access_child_folder.name);
        printf("Permission: ");
        prinfPermission(stat.last_access_child_folder.permission);
        printf("UID: %d\n", stat.last_access_child_folder.uid);
        printf("GID: %d\n", stat.last_access_child_folder.gid);
        printTime(stat.last_access_child_folder.atime);
	}
	else printf("Have no child folder\n");
    }
    else
        printf("Cannot get information from the folder %s\n", path);
}
