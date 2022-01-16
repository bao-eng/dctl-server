#pragma once

#include <boost/array.hpp>
#include <boost/asio.hpp>
#include <vector>

#include "dctl_engine.h"
#include "udp_server.h"

class Server {
 public:
  explicit Server(const Settings& settings, int port);
  void Run();

 private:
  int FindFreeClientIndex() const;
  int FindExistingClientIndex(
      const boost::asio::ip::udp::endpoint& address) const;
  bool IsClientConnected(int clientIndex) const;
  const boost::asio::ip::udp::endpoint& GetClientEndpoint(
      int client_index) const;
  int AddClient(const boost::asio::ip::udp::endpoint& endpoint);

  int max_clients_;
  UDPServer udp_server;
  int num_connected_clients_{0};
  std::vector<bool> client_connected_;
  std::vector<boost::asio::ip::udp::endpoint> client_endpoint_;
  std::shared_ptr<ServerEngine> engine;
};
