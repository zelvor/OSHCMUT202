#include "get_folder_stat.h"
#include <linux/kernel.h>
#include <sys/syscall.h>
#include <unistd.h>

long get_folder_stat(char * path, struct folder_stat * info){
	return syscall(548, path, info);
}
