#ifndef SERVER_HPP
#define SERVER_HPP

#include <boost/asio.hpp>
#include <boost/noncopyable.hpp>
#include <string.h>

namespace http {
namespace server {

class server : private boost::noncopyable {
public:
  explicit server(const std::string &address, const std::string &port,
                  const std::string &doc_root);

  // run server's io_service loop
  void run();

private:
  // init an async accept operation
  void start_accept();

  // handle completion of an async accept operation
  void handle_accept(const boost::system::error_code &e);

  // handle a request to stop server
  void handle_stop();

  // the io_service used to perform async operation
  boost::asio::io_context io_context_;

  // listen for incoming connections
  boost::asio::ip::tcp::acceptor acceptor_;

  // connection_manager owns all live connections
  // connection_manager connection_manager_;

  // next connection to be acceptor
  // connection_ptr new_connection_;

  // handler for all incoming request
  // request_handler request_handler_;
};
} // namespace server
} // namespace http

#endif
