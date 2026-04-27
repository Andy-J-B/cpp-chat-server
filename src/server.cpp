#include "server.hpp"
#include "tcp_connection.hpp"
#include <boost/asio.hpp>
#include <cstdlib>
#include <iostream>
#include <string>
#include <system_error>

namespace http {
namespace server {

server::server(boost::asio::ip::tcp::endpoint &endpoint,
               boost::asio::io_context &io_context)
    : io_context_(), acceptor_(io_context_, endpoint) {

  start_accept();
}

void server::start_accept() {
  tcp_connection::pointer new_connection = tcp_connection::create(io_context_);

  acceptor_.async_accept(new_connection->socket(),
                         std::bind(&server::handle_accept, this, new_connection,
                                   boost::asio::placeholders::error));
}

// handle completion of an async accept operation
void server::handle_accept(tcp_connection::pointer new_connection,
                           const boost::system::error_code &e) {
  if (!e) {
    new_connection->start();
  }
  start_accept();
}

// handle a request to stop server
void handle_stop();
} // namespace server
} // namespace http

int main(int argc, char *argv[]) {
  // argument layout : port, how many clients
  if (argc < 4) {
    perror("Was expecting arguments <address> <port> <number of clients>");
    exit(EXIT_FAILURE);
  }

  const std::string address_str = argv[1];

  const unsigned short port = atoi(argv[2]);

  const int numberOfClients = atoi(argv[3]);

  try {
    auto address = boost::asio::ip::make_address(address_str);
    boost::asio::ip::tcp::endpoint endpoint(address, port);

    boost::asio::io_context io_context;
    http::server::server server(endpoint, io_context);
    std::cout << "Starting HTTP server listening on port : " << port
              << " and address : " << address << std::endl;

    io_context.run();

  } catch (std::exception &err) {

    std::cerr << err.what() << std::endl;
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}
