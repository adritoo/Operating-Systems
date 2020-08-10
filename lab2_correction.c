#include <stdio.h>
#include <unistd.h>

int main(int argc, char **argv) {
  int pipefd[2];

  pipe(pipefd);

  if (fork() == 0) {
    // child process
    dup2(pipefd[1], STDOUT_FILENO); // redirecting stdout to write end of the pipe

    system("ps aux");
    close(pipefd[0]);
    close(pipefd[1]);
    close(STDOUT_FILENO);
  } else {
    // parent process
    dup2(pipefd[0], STDIN_FILENO);
    close(pipefd[1]);

    system("more");
  }

}
