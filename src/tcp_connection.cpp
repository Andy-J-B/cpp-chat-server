#include "tcp_connection.hpp"
#include <boost/asio.hpp>
#include <memory.h>
#include <netinet/tcp.h>

namespace http {
namespace server {

typedef std::shared_ptr<tcp_connection> pointer;

static pointer create(boost::asio::io_context &io_context);

boost::asio::ip::tcp::socket &socket();

void start();

tcp_connection(boost::asio::io_context &io_context);

void handle_write(const boost::system::error_code &);

} // namespace server
} // namespace http
