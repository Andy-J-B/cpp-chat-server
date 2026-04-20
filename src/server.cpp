#include <boost/asio.hpp>
#include <cstdlib>
#include <iostream>

int main(int argc, char *argv[]) {
  // argument layout : port, how many clients
  if (argc < 3) {
    perror("Was expecting more <port> and <number of clients>");
    exit(EXIT_FAILURE);
  }

  return 0;
}
