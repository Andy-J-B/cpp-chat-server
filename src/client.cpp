#include <array>
#include <boost/asio.hpp>
#include <exception>
#include <iostream>

int main(int argc, char *argv[]) {
  if (argc < 3) {
    perror("Was expecting arguments <server host address> <port>");
    exit(EXIT_FAILURE);
  }

  try {
    boost::asio::io_context io_context;

    // convert server name to tcp endpoint
    boost::asio::ip::tcp::resolver resolver(io_context);
    boost::asio::ip::tcp::resolver::results_type endpoints =
        resolver.resolve(argv[1], argv[2]);

    // try both ipv4 and ipv6
    boost::asio::ip::tcp::socket socket(io_context);
    boost::asio::connect(socket, endpoints);

    // read input
    for (;;) {
      std::array<char, 128> buf;
      boost::system::error_code error;

      size_t len = socket.read_some(boost::asio::buffer(buf), error);
      if (error == boost::asio::error::eof) {
        break;
      } else if (error) {
        throw boost::system::system_error(error);
      }
      std::cout.write(buf.data(), len);
    }
  } catch (std::exception &err) {
    std::cerr << err.what() << std::endl;
    return EXIT_FAILURE;
  }
  return 0;
}
