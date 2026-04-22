#ifndef TCP_CONNECTION_HPP
#define TCP_CONNECTION_HPP

#include <boost/asio.hpp>
#include <memory>
#include <netinet/tcp.h>

namespace http {
namespace server {

class tcp_connection : public std::enable_shared_from_this<tcp_connection> {
public:
  typedef std::shared_ptr<tcp_connection> pointer;

  static pointer create(boost::asio::io_context &io_context);

  boost::asio::ip::tcp::socket &socket();

  void start();

private:
  tcp_connection(boost::asio::io_context &io_context);

  void handle_write(const boost::system::error_code &);

  boost::asio::ip::tcp::socket socket_;
  std::string message_;
};

} // namespace server
} // namespace http

#endif
