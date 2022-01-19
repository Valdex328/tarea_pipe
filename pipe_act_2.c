
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>

#define READ  0
#define WRITE 1

int main() {

  pid_t pid;
  int   fd[2];
  char *const vector_hijo[]={"sort", NULL};
  char *const vector_padre[]={"cat", "/etc/hosts", NULL};
  if (pipe(fd) == -1) {
	perror("Creating pipe");
	exit(EXIT_FAILURE);
  }

  pid = fork();
  if (pid == -1) {
	perror("fork() failed)");
	exit(EXIT_FAILURE);
  } else if (pid == 0) {
	close(fd[WRITE]);
	// Redirect STDIN to read from the pipe.
	dup2(fd[READ], STDIN_FILENO);
	execvp(vector_hijo[0], vector_hijo);
  } else {
	// Close the pipe read descriptor.
	close(fd[READ]);
	// Redirect STDOUT to write to the pipe.
	dup2(fd[WRITE], STDOUT_FILENO);
	execvp(vector_padre[0], vector_padre);
  }
}


