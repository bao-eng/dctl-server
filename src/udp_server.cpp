#include "udp_server.h"

UDPServer::UDPServer(int port)
    : io_service_(),
      socket_(io_service_, boost::asio::ip::udp::endpoint(
                               boost::asio::ip::udp::v4(), port)) {}

size_t UDPServer::ReceiveBlocking(std::vector<char>& buf,
                                  boost::asio::ip::udp::endpoint& ep) {
  socket_.wait(boost::asio::ip::udp::socket::wait_read);
  boost::array<char, 64000> recv_buffer_;
  auto sz = socket_.receive_from(boost::asio::buffer(recv_buffer_), ep);
  buf.resize(sz);
  std::copy(recv_buffer_.begin(), recv_buffer_.begin() + sz, buf.begin());
  return sz;
}

void UDPServer::Send(const std::vector<char>& buf,
                     const boost::asio::ip::udp::endpoint& ep) {
  socket_.send_to(boost::asio::buffer(buf.data(), buf.size()), ep);
}
