#include "pipe_networking.h"

void handle_sigint(int sig) {
  printf("Goodbye\n");
  remove("waluigi");
  exit(1);
}

int main() {

  signal(SIGINT, handle_sigint);
  int to_client;
  int from_client;

  from_client = server_handshake( &to_client );
}
