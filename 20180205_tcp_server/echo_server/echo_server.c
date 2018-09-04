# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <err.h>
# include <sys/types.h>
# include <sys/socket.h>
# include <netdb.h>
# include <string.h>
# include <signal.h>


// register an fd or get it
// call with -1 if you just want the fd
int fdaccept_register(int fd) {
  static int fdaccept = -1;
  if (fdaccept == -1 && fd != -1) {
    fdaccept = fd;
  }
  return fdaccept;
}

// signal handler for SIGINT
void sigint_handler(int sig) {
  (void)sig;
  int fd = fdaccept_register(-1);
  if (fd != -1)
    close(fd);
  _exit(0);
}

void echo(int fdin, int fdout)
{
  char buffer[2048];
  while (read(fdin, buffer, 1) != 0)
  {
    if(write(fdout, buffer, 1) == -1)
    {
      errx(EXIT_FAILURE, "Unable to write in the output provided");
    }
  }
  if(read(fdin, buffer, 1) == -1)
  {
    errx(EXIT_FAILURE, "Unable to read from the input provided");
  }
}

void server(const char *portname)
{
  int info_err = 0;
  struct addrinfo hints, *resinfo = NULL;

  // setup hints and get local info
  memset(&hints, 0, sizeof (struct addrinfo));
  hints.ai_family = AF_UNSPEC;                 // IPv4 or IPv6
  hints.ai_socktype = SOCK_STREAM;             // TCP
  hints.ai_protocol = 0;
  hints.ai_flags = AI_PASSIVE | AI_ADDRCONFIG; // server mode
  // let's go !
  info_err = getaddrinfo(NULL, portname, &hints, &resinfo);

  // Error management
  if (info_err != 0) {
    errx(EXIT_FAILURE, "Server setup fails on port %s: %s", portname,
	                     gai_strerror(info_err));
  }

  int cnx = socket(resinfo->ai_family,
                   resinfo->ai_socktype,
                   resinfo->ai_protocol);
  if (cnx != -1)
  {
    printf("Succesfully created the socket !\n");
    int socketFD = fdaccept_register(cnx);
    if (bind(socketFD, resinfo->ai_addr, resinfo->addrlen) == -1)
    {
      close(cnx);
      errx(EXIT_FAILURE, "Serveur wasn't able to connect.");
    }
    else
    {
      printf("Succesfully connected !\n");
      int reuse_err;
      int reuse = 1;
      reuse_err = setsockopt(cnx,
                             SOL_SOCKET,
                             SO_REUSEADDR,
                             &reuse,
                             sizeof (reuse));

      // Error management
      if (reuse_err == -1)
        err(EXIT_FAILURE, "Failed to set socket options");

      listen(socketFD, 5);
      // Infinite loop to accept incoming connections.
      for(;;)
      {
        int fdcnx = accept(socketFD, NULL, NULL);
        if (fdncnx != -1) {
          echo(fdcnx, fdcnx);
          close(fdcnx);
        }
        else {
          err(EXIT_FAILURE, "Failed to accept the incoming connection.");
        }
      }
    }
  }

  freeaddrinfo(resinfo);
}



int main(int argc, char *argv[])
{
  if (argc == 1)
  {
    struct sigaction sigint;

    // Handle terminaison through Ctrl-C
    memset(&sigint, 0, sizeof (struct sigaction));
    sigint.sa_handler = sigint_handler;
    sigfillset(&sigint.sa_mask);
    sigint.sa_flags = SA_NODEFER;
    if ( sigaction(SIGINT, &sigint, NULL) == -1)
      err(EXIT_FAILURE, "can't change SIGINT behavior");

    struct sigaction sigchld;

    // Avoid zombies and don't get notify about children
    memset(&sigchld, 0, sizeof (struct sigaction));
    sigchld.sa_handler = SIG_DFL;
    sigemptyset(&sigchld.sa_mask);
    sigchld.sa_flags = SA_NOCLDSTOP | SA_NOCLDWAIT;
    if ( sigaction(SIGCHLD, &sigchld, NULL) == -1 )
      err(EXIT_FAILURE, "can't change SIGCHLD behavior");

    server(argv[1]);
  }
  else {
    err(EXIT_FAILURE, "Invalid arguments : pass a port to listen to");
  }
}
