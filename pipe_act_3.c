
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <time.h>
#include <sys/wait.h>
#include <fcntl.h>

#define READ  0
#define WRITE 1

int main() {
  pid_t pid;
  int   fd[2];
  srand(time(NULL));
  int numero_random = rand()%1001 + 1;

  if (pipe(fd) == -1) {
	perror("Creating pipe");
	exit(EXIT_FAILURE);
  }
  pid = fork();
  if (pid == -1) {
	perror("fork() failed)");
	exit(EXIT_FAILURE);


  } else if (pid == 0) {
	// Close the pipe write descriptor.
	close(fd[WRITE]);
	// Redirect STDIN  read from the pipe.
	dup2(fd[READ], STDIN_FILENO);

	printf("Numero: %d \n", numero_random);
	if (numero_random < 500){
	   	 printf("menor que 500 \n");
	} else if(numero_random >= 500) {
	 	 printf("mayor o igual que 500 \n");
	}

   } else if (pid > 0) {
	// Close the pipe read descriptor.
	close(fd[READ]);
	// Redirect STDOUT write from the pipe.
	dup2(fd[WRITE], STDOUT_FILENO);
  }
}
