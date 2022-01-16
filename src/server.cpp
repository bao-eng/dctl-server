#include "server.h"

Server::Server(const Settings& settings, int port)
    : max_clients_(settings.max_players),
      udp_server(port),
      client_connected_(settings.max_players),
      client_endpoint_(settings.max_players) {
  State st;
  Vec2 p1{3, (settings.map_height / 2)};
  Snake s1{0, {p1, p1}, Dir::kRight, (Col){0, 255, 255, 255}};  // CYAN
  Vec2 p2{settings.map_width - 3, settings.map_height / 2};
  Snake s2{1, {p2, p2}, Dir::kLeft, (Col){255, 0, 255, 255}};  // MAGENTA
  Vec2 p3{settings.map_width / 2, 3};
  Snake s3{2,
           {{p2.x - 10, p2.y - 10}, {p2.x - 10, p2.y - 10}},
           Dir::kDown,
           (Col){0, 255, 0, 255}};  // GREEN
  Vec2 p4{10 + settings.map_width / 2, settings.map_height - 3};
  Snake s4{3, {p4, p4}, Dir::kRight, (Col){255, 255, 0, 255}};  // YELLOW
  switch (max_clients_) {
    case 1:
      st.snakes.push_back(s1);
      break;
    case 2:
      st.snakes.push_back(s1);
      st.snakes.push_back(s2);
      break;
    case 3:
      st.snakes.push_back(s1);
      st.snakes.push_back(s2);
      st.snakes.push_back(s3);
      break;
    case 4:
      st.snakes.push_back(s1);
      st.snakes.push_back(s2);
      st.snakes.push_back(s3);
      st.snakes.push_back(s4);
      break;
    default:
      throw std::invalid_argument("1-4 players");
      break;
  }

  engine = std::make_shared<ServerEngine>(st, settings);
}

// Which lets the server lookup a free slot for a client to join (if any are
// free):
int Server::FindFreeClientIndex() const {
  for (int i = 0; i < max_clients_; ++i) {
    if (!client_connected_[i]) return i;
  }
  return -1;
}

// Find the client index corresponding to an IP address and port:
int Server::FindExistingClientIndex(
    const boost::asio::ip::udp::endpoint& endpoint) const {
  for (int i = 0; i < max_clients_; ++i) {
    if (client_connected_[i] && client_endpoint_[i] == endpoint) return i;
  }
  return -1;
}

// Check if a client is connected to a given slot:
bool Server::IsClientConnected(int clientIndex) const {
  return client_connected_[clientIndex];
}

// … and retrieve a client’s IP address and port by client index:
const boost::asio::ip::udp::endpoint& Server::GetClientEndpoint(
    int client_index) const {
  return client_endpoint_[client_index];
}

int Server::AddClient(const boost::asio::ip::udp::endpoint& endpoint) {
  auto index = FindFreeClientIndex();
  if (index != -1) {
    client_endpoint_[index] = endpoint;
    client_connected_[index] = true;
    num_connected_clients_++;
  }
  return index;
}

void Server::Run() {
  while (num_connected_clients_ != max_clients_) {
    std::vector<char> buf;
    boost::asio::ip::udp::endpoint ep;
    udp_server.ReceiveBlocking(buf, ep);
    auto msg = UnpackMessage(buf);
    if(std::holds_alternative<Request>(msg)){
      auto req = std::get<Request>(msg);
      std::cout << req.name << " trying to connect" << std::endl;
      if (FindExistingClientIndex(ep) == -1) {
        auto i = AddClient(ep);
        std::cout << "Added client id" << i << " " << ep << std::endl; 
      }
    }
  }
  // for(auto ){

  // }
  std::cout << "all clients connected!" << std::endl;
}
