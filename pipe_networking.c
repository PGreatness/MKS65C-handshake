#include "pipe_networking.h"


/*=========================
  server_handshake
  args: int * to_client

  Performs the client side pipe 3 way handshake.
  Sets *to_client to the file descriptor to the downstream pipe.

  returns the file descriptor for the upstream pipe.
  =========================*/
int server_handshake(int *to_client) {
  int pipe_file;
  if ((pipe_file = mkfifo("waluigi", 0644)) == -1) {
    printf("Error %d: %s\n", errno, strerror(errno));     //yes error?
  }
  int fd;
  while (1) {
    fd = open("waluigi", O_RDONLY);

    char * msg = malloc(BUFFER_SIZE);
    read(fd, msg, BUFFER_SIZE);
    printf("Said by client: %s", msg);

    close(fd);

    fd = open("waluigi", O_WRONLY);
    char send_client[BUFFER_SIZE];
    fgets(send_client, BUFFER_SIZE, stdin);
    write(fd, send_client, BUFFER_SIZE);

    close(fd);
  }
  return 0;
}


/*=========================
  client_handshake
  args: int * to_server

  Performs the client side pipe 3 way handshake.
  Sets *to_server to the file descriptor for the upstream pipe.

  returns the file descriptor for the downstream pipe.
  =========================*/
int client_handshake(int *to_server) {
  int pipe_file;
  int private_pipe;
  if ((pipe_file = mkfifo("waluigi", 0644)) == -1) {
    //printf("Error %d: %s\n", errno, strerror(errno));    //not error
  }
  int fd;
  while (1) {
    fd = open("waluigi", O_WRONLY);

    char send_msg[BUFFER_SIZE];
    fgets(send_msg, BUFFER_SIZE, stdin);
    write(fd, send_msg, BUFFER_SIZE);

    close(fd);

    fd = open("waluigi", O_RDONLY);

    char * buf = malloc(BUFFER_SIZE);
    read(fd, buf, BUFFER_SIZE);
    printf("Said by server: %s", buf);

    close(fd);
  }
  return 0;
}
