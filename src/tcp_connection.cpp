#include "tcp_connection.hpp"
#include <boost/asio.hpp>
#include <memory.h>
#include <netinet/tcp.h>

std::string make_daytime_string() {
  using namespace std;
  time_t now = time(0);
  return ctime(&now);
}

namespace http {
namespace server {

typedef std::shared_ptr<tcp_connection> pointer;

pointer tcp_connection::create(boost::asio::io_context &io_context) {
  return pointer(new tcp_connection(io_context));
}

boost::asio::ip::tcp::socket &tcp_connection::socket() { return socket_; }

void tcp_connection::start() {
  message_ = make_daytime_string();
  boost::asio::async_write(
      socket_, boost::asio::buffer(message_),
      std::bind(&tcp_connection::handle_write, shared_from_this(),
                boost::asio::placeholders::error,
                boost::asio::placeholders::bytes_transferred));
}

tcp_connection::tcp_connection(boost::asio::io_context &io_context)
    : socket_(io_context) {
  // Empty
}

void tcp_connection::handle_write(const boost::system::error_code &ec,
                                  size_t bytes_transferred) {}

} // namespace server
} // namespace http
