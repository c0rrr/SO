#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

int main ()
{
    int fds[2];
    pid_t pid;
    pipe (fds);
    perror("pipe");
    pid = fork ();
    perror("fork");
    if (pid == (pid_t) 0) {
	int filefd = open("sample.txt", O_WRONLY, 0666);
        perror("open");
	close (fds[1]);
        dup2 (filefd, STDOUT_FILENO);
	dup2 (fds[0], STDIN_FILENO);
        execlp ("sort", "sort", NULL);
	perror("execlp");
	close(filefd);
    } else {
        FILE* stream;
        close (fds[0]);
        stream = fdopen (fds[1], "w");
	perror("fdopen");
        fprintf (stream, "This is a test.\n");
        fprintf (stream, "Hello, world.\n");
        fprintf (stream, "My dog has fleas.\n");
        fprintf (stream, "This program is great.\n");
        fprintf (stream, "One fish, two fish.\n");
        fflush (stream);
        close (fds[1]);
        waitpid (pid, NULL, 0);
    }
    return 0;
}
