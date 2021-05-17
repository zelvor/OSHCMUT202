#include <linux/kernel.h>
#include <linux/syscalls.h>
#include <linux/string.h>
#include <linux/path.h>
#include <linux/dcache.h>
#include <linux/fs.h>
#include <linux/fs_struct.h>
#include <linux/namei.h>
#include <linux/stat.h>
#include <linux/list.h>
//#include <aio.h>

struct folder_info
{
	char	name[128];
	mode_t	permission;
	uid_t	uid;
	gid_t	gid;
	long	size;
	time_t	atime;
};

struct folder_stat
{
	long studentID;
	struct folder_info folder;
	struct folder_info parent_folder;
	struct folder_info last_access_child_folder;
};

SYSCALL_DEFINE2(get_folder_stat, char *, path, struct folder_stat *, stat)
{
	struct path f_path;
	// Check if path is NULL -> set path to current working dir
	int a = 0;
	if (path == NULL)
		get_fs_pwd(current->fs, &f_path);
	else a = kern_path(path, LOOKUP_JUMPED, &f_path);

	if(a != 0) return EINVAL;
 	struct dentry *d_folder = f_path.dentry;

	stat->studentID = 1913254;

	// folder
	strncpy(stat->folder.name, d_folder->d_name.name, 
		sizeof(stat->folder.name));
	stat->folder.permission = d_folder->d_inode->i_mode;
	stat->folder.uid = d_folder->d_inode->i_uid.val;
	stat->folder.gid = d_folder->d_inode->i_gid.val;	
	stat->folder.size = d_folder->d_inode->i_size;
	stat->folder.atime = d_folder->d_inode->i_atime.tv_sec;

	
	/* Parent folder */
	if (d_folder->d_parent != NULL)
	{
		strncpy(stat->parent_folder.name, d_folder->d_parent->d_name.name, 
			sizeof(stat->parent_folder.name));
		stat->parent_folder.permission = d_folder->d_parent->d_inode->i_mode;
		stat->parent_folder.uid = d_folder->d_parent->d_inode->i_uid.val;
		stat->parent_folder.gid = d_folder->d_parent->d_inode->i_gid.val;	
		stat->parent_folder.size = d_folder->d_parent->d_inode->i_size;
		stat->parent_folder.atime = d_folder->d_parent->d_inode->i_atime.tv_sec;
	}
	
	/* Last access folder */
	struct dentry *d_child_folder = NULL;
	struct dentry *check = NULL;
	time_t last_access_time = 0;
	
	list_for_each_entry(check, &(d_folder->d_subdirs), d_child)
	{
		if (check->d_inode != NULL)
			if (S_ISDIR(check->d_inode->i_mode))
			{
				if (check->d_inode->i_atime.tv_sec > last_access_time)
				{
					last_access_time = check->d_inode->i_atime.tv_sec;
					d_child_folder = check;
				}
			}
	}


	if (d_child_folder != NULL)
	{
		strncpy(stat->last_access_child_folder.name, d_child_folder->d_name.name, sizeof(stat->last_access_child_folder.name));
		stat->last_access_child_folder.permission = d_child_folder->d_inode->i_mode;
		stat->last_access_child_folder.uid = d_child_folder->d_inode->i_uid.val;
		stat->last_access_child_folder.gid = d_child_folder->d_inode->i_gid.val;	
		stat->last_access_child_folder.size = d_child_folder->d_inode->i_size;
		stat->last_access_child_folder.atime = d_child_folder->d_inode->i_atime.tv_sec;
	}

	printk("%ld\n", stat->studentID); 
	return 0;
}
