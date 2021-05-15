#include<linux/kernel.h>
#include<linux/syscalls.h>
#include<linux/time.h>
#include<unistd.h>
#include<linux/fs.h>
#include<linux/fs_struct.h>
#include<linux/stat.h>
#include<linux/types.h>
#include<linux/fcntl.h>
#include<linux/path.h>
#include<linux/namei.h>
#include<linux/dirent.h>
#include<linux/string.h>
#include<linux/time64.h>

struct folder_info
{
    char    name[128];
    mode_t  permission;
    uid_t   uid;
    gid_t   gid;
    long    size;
    time_t  atime;
};

struct folder_stat
{
    long                student_ID;
    struct folder_info  folder;
    struct folder_info  parent_folder;
    struct folder_info  last_access_child_folder;
};

SYSCALL_DEFINE2(get_folder_stat, char*, path, struct folder_stat *, stat)
{
    struct folder_stat  *info;
    info = kmalloc(sizeof(struct folder_stat), GFP_KERNEL);
    copy_from_user(info, stat, sizeof(struct folder_stat));
    info -> student_ID  = 1913254;
    copy_to_user(stat, info, sizeof(struct folder_stat));

    struct folder_info  folder;
    struct folder_info  parent_folder;
    struct folder_info  last_access_child_folder;
    struct file         *current_fi;

    if (path == NULL)           path ="/home";
    current_fi                  = kmalloc(sizeof(struct file), GFP_KERNEL);
    current_fi                  = filp_open(path, O_RDONLY, 0);
    if (IS_ERR(current_fi))     return EINVAL;
    
    struct inode        *current_fi_inode;
    current_fi_inode    = kmalloc(sizeof(struct inode), GFP_KERNEL);
    current_fi_inode    = current_fi -> f_inode;
    struct dentry       *current_fi_dentry;
    current_fi_dentry   = current_fi->f_path.dentry;

    struct dentry       *current_dentry;

    folder.size = 0;
    strcpy(folder.name, current_fi_dentry->d_name.name);
    folder.permission   = current_fi_inode->i_node;
    folder.atime        = current_fi_dentry->d_inode->i_atime.tv_sec;
    folder.uid          = current_fi_dentry -> d_inode -> i_uid.val;
    folder.gid          = current_fi_dentry -> d_inode -> i_gid.val;
    time_t newest_access;
    newest_access = 0;

    // LOOP
    list_for_each_entry(current_dentry, &current_fi_dentry -> d_subdirs, d_child)
    {
        if (current_dentry == NULL)                 break;
    
        if (strlen(current_dentry->d_iname) == 0)   continue;
        
        if (current_dentry->d_inode == NULL)        continue;
        

        if (S_ISDIR(current_dentry->d_inode->inode)) {
            struct dentry *sub_dir;
            time_t current_access = current_dentry->d_inode->i_atime.tv_sec;

            if (current_access > newest_access) {
                newest_access = current_access;
            last_access_child_folder.size = 0;
            strcpy(last_access_child_folder.name, current_dentry->d_name.name);
            last_access_child_folder.permission = current_dentry->d_inode->i_mode;
            last_access_child_folder.atime      = current_dentry->d_inode->i_atime.tv_sec;
            last_access_child_folder.uid        = current_dentry -> d_inode -> i_uid.val;
            last_access_child_folder.gid        = current_dentry -> d_inode -> i_gid.val;
            }

            list_for_each_entry (sub_dir, &current_dentry->d_subdirs, d_chid)
            {
                if (strlen(sub_dir->d_iname) == 0)      continue;
                if (sub_dir->d_inode == NULL)           continue;
                if (sub_dir -> d_inode ->i_size > 0)
                    last_access_child_folder.size = last_access_child_folder.size + sub_dir ->d_inode->i_size;
    
            }
        }

        if (current_dentry ->d_inode->i_size < 0) {
        } else {
            folder.size = folder.size + current_dentry -> d_inode ->i_size;
        }
    }


    parent_folder.size = 0;
    strcpy(parent_folder.name, current_fi_dentry->d_parent->d_name.name);
    parent_folder.atime         = current_fi_dentry->d_parent->d_inode->i_atime.tv_sec;
    parent_folder.gid           = current_fi_dentry->d_parent->d_inode->i_gid_val;
    parent_folder.uid           = current_fi_dentry->d_parent->d_inode->i_uid_val;
    parent_folder.permission    = current_fi_dentry->d_parent->d_inode->i_mode;

    //get size of parent folder 

    list_for_each_entry(current_dentry, &current_fi_dentry->d_child, d_child)
    {
        if (current_dentry == NULL)                 break;
        if (strlen(current_dentry->d_iname) == 0)   continue;
        if (current_dentry -> d_name.name == NULL)  continue;
        if (current_dentry ->d_inode == NULL)       continue;
        if (current_dentry ->d_inode->i_size >0)
            parent_folder.size = parent_folder.size + current_dentry->d_inode->i_size;
    }

    //close opened path
    filp_close(current_fi,0);
    info->folder                    = folder;
    info->parent_folder             = parent_folder;
    info->last_access_child_folder  = last_access_child_folder;

    copy_to_user(stat, info, sizeof(struct folder_stat));
    return 0;
}
