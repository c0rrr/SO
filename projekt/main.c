#include <assert.h>
#include <dirent.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#include "copy.h"

const char* get_file_type (const char* path)
{
	struct stat st;
	lstat (path, &st);
	if (S_ISLNK (st.st_mode))
		return "symbolic link";
	else if (S_ISDIR (st.st_mode))
		return "directory";
	else if (S_ISCHR (st.st_mode))
		return "character device";
	else if (S_ISBLK (st.st_mode))
		return "block device";
	else if (S_ISFIFO (st.st_mode))
		return "fifo";
	else if (S_ISSOCK (st.st_mode))
		return "socket";
	else if (S_ISREG (st.st_mode))
		return "regular file";
	else
		assert (0);
}

void print_directory (char* src_dir_path, char* dest_dir_path)
{
	DIR* dir;
	struct dirent* entry;
	char entry_path[PATH_MAX + 1];
	size_t path_len;
	char* temp_src, temp_dest;

	strncpy (entry_path, src_dir_path, sizeof (entry_path));
	path_len = strlen (src_dir_path);
	if (entry_path[path_len - 1] != '/') {
		entry_path[path_len] = '/';
		entry_path[path_len + 1] = '\0';
		++path_len;
	}

	dir = opendir (src_dir_path);
	while ((entry = readdir (dir)) != NULL) {
		temp_src = src_dir_path;
		temp_dest = dest_dir_path;

		const char* type;
		strncpy (entry_path + path_len, entry->d_name,
		sizeof (entry_path) - path_len);
		type = get_file_type (entry_path);

		temp_src = malloc(strlen(src_dir_path) + strlen(entry_path) + 1);
		temp_dest = malloc(strlen(dest_dir_path) + strlen(entry_path) + 1);

		strcat(temp_src, entry_path);
		strcat(temp_dest, entry_path);
		//CpFile(temp_src, temp_dest);
	}
	closedir (dir);
}

int main (int argc, char* argv[])
{
	print_directory(argv[2], argv[3]);

	return 0;
}
