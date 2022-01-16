#pragma once

#include <boost/array.hpp>
#include <boost/asio.hpp>
#include <vector>

class UDPServer {
 public:
  explicit UDPServer(int port);
  size_t ReceiveBlocking(std::vector<char>& buf,
                         boost::asio::ip::udp::endpoint& ep);
  void Send(const std::vector<char>& buf,
            const boost::asio::ip::udp::endpoint& ep);

 private:
  boost::asio::io_service io_service_;
  boost::asio::ip::udp::socket socket_;
};
