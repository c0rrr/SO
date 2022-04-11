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

void print_directory (char* dir_path)
{
	DIR* dir;
	struct dirent* entry;
	char entry_path[PATH_MAX + 1];
	size_t path_len;

	strncpy (entry_path, dir_path, sizeof (entry_path));
	path_len = strlen (dir_path);
	if (entry_path[path_len - 1] != '/') {
		entry_path[path_len] = '/';
		entry_path[path_len + 1] = '\0';
		++path_len;
	}
	printf("\nPrinted directory path : %s\n", entry_path);
	dir = opendir (dir_path);
	while ((entry = readdir (dir)) != NULL) {
		const char* type;
		strncpy (entry_path + path_len, entry->d_name,
		sizeof (entry_path) - path_len);
		type = get_file_type (entry_path);
		printf ("%-18s: %s\n", type, entry_path);
	}
	closedir (dir);
}

int main (int argc, char* argv[])
{
	char* dir_path;
	int n = argc-1;
	do
	{
		if (argc >= 2)
			dir_path = argv[argc-n];
		else
			dir_path = ".";

		print_directory(dir_path);
		n--;
	}while(n>0);
	return 0;
}
