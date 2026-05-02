#ifndef SERVER_HPP
#define SERVER_HPP

#include "tcp_connection.hpp"
#include <boost/asio.hpp>
#include <boost/noncopyable.hpp>

namespace http {
namespace server {

class server : private boost::noncopyable {
public:
  explicit server(boost::asio::ip::tcp::endpoint &endpoint,
                  boost::asio::io_context &io_context);
  // run server's io_service loop
  void run();

private:
  // init an async accept operation
  void start_accept();

  // handle completion of an async accept operation
  void handle_accept(tcp_connection::pointer new_connection,
                     const boost::system::error_code &e);

  // handle a request to stop server
  void handle_stop();

  // the io_service used to perform async operation
  boost::asio::io_context &io_context_;

  // listen for incoming connections
  boost::asio::ip::tcp::acceptor acceptor_;
};
} // namespace server
} // namespace http

#endif
