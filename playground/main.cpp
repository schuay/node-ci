#include <cstdio>

#include <poll.h>
#include <unistd.h>

int main(int argc, char** argv) {
  printf("Hello World\n");

  {
    int pipefd[2];
    pipe(pipefd);
    
    struct pollfd fds;
    fds.events = POLLIN | POLLOUT;

    printf("POLLIN %d\n", POLLIN);
    printf("POLLOUT %d\n", POLLOUT);

    fds.fd = pipefd[0];  // Read.
    {
      int ret = poll(&fds, 1, 0);
      printf("poll() -> ret %d, revents %d\n", ret, fds.revents);
    }

    fds.fd = pipefd[1];
    {
      int ret = poll(&fds, 1, 0);
      printf("poll() -> ret %d, revents %d\n", ret, fds.revents);
    }

    write(pipefd[1], "012", 3);

    fds.fd = pipefd[0];  // Read.
    {
      int ret = poll(&fds, 1, 0);
      printf("poll() -> ret %d, revents %d\n", ret, fds.revents);
    }

    fds.fd = pipefd[1];
    {
      int ret = poll(&fds, 1, 0);
      printf("poll() -> ret %d, revents %d\n", ret, fds.revents);
    }

    close(pipefd[0]);
    close(pipefd[1]);
  }

  return 0;
}
