#include <iostream>

#include "server.h"

int main(int argc, char** argv) {
  Settings settings;
  settings.max_players = 2;
  settings.map_width = 107;
  settings.map_height = 54;
  settings.speed = 58.0f / 6;
  settings.dt = 0.01;
  settings.max_length = 60;
  settings.head_diameter = 1;
  settings.tail_width = 0.65;

  // InputPack ininpp;
  // ininpp.vec.emplace_back(0,0,false,false,false,false);
  // ininpp.vec.emplace_back(1,1,false,false,false,false);

  // auto p = PackInputPack(ininpp);
  // auto r = UnpackMessage(p);
  // if(std::holds_alternative<InputPack>(r)){
  //   auto inpp = std::get<InputPack>(r);
  //   std::cout << "inpp" << std::endl;
  // }

  // Request req;
  // req.name="test";

  // auto p = PackRequest(req);
  // auto r = UnpackMessage(p);
  // if(std::holds_alternative<Request>(r)){
  //   auto inpp = std::get<Request>(r);
  //   std::cout << "req" << std::endl;
  // }

  while (1) {
    Server srv(settings, 7777);
    std::cout << "Server running" << std::endl;
    srv.Run();
  }
  return 0;
}

//   uint32_t sequence{0};
//   double t = 0.0;
//   double dt = 0.01;
//   auto current_time = std::chrono::system_clock::now();
//   double accumulator = 0.0;

//   State st;
//   st.sequence = sequence;
//   sequence++;

//   Vec2 p1{3, ((float)kMapHeight / 2)};
//   Snake s1{0, {p1, p1}, Dir::kRight, (Col){0, 255, 255, 255}};  // CYAN
//   Vec2 p2{kMapWidth - 3, (float)kMapHeight / 2};
//   Snake s2{1, {p2, p2}, Dir::kLeft, (Col){255, 0, 255, 255}};  // MAGENTA
//   Vec2 p3{(float)kMapWidth / 2, 3};
//   Snake s3{2,
//            {{p2.x - 10, p2.y - 10}, {p2.x - 10, p2.y - 10}},
//            Dir::kDown,
//            (Col){0, 255, 0, 255}};  // GREEN
//   Vec2 p4{10 + (float)kMapWidth / 2, kMapHeight - 3};
//   Snake s4{3, {p4, p4}, Dir::kRight, (Col){255, 255, 0, 255}};  // YELLOW

//   st.snakes.push_back(s1);
//   // st.snakes.push_back(s2);
//   // st.snakes.push_back(s3);
//   // st.snakes.push_back(s4);

//   DCTLEngine game(st, kMapWidth, kMapHeight, kSpeed, dt, 60, kHeadDiameter,
//                   kTailWidth);

//   boost::asio::io_service io_service_;
//   udp::socket socket_(io_service_, udp::endpoint(udp::v4(), 7777));

//   // while (!WindowShouldClose())  // Detect window close button or ESC key
//   std::set<boost::asio::ip::udp::endpoint> eps;
//   while(1)
//   {
//     socket_.wait(boost::asio::ip::udp::socket::wait_read);
//     boost::array<char, 64000> recv_buffer_;
//     while (socket_.available()) {
//       boost::asio::ip::udp::endpoint ep;
//       auto sz = socket_.receive_from(boost::asio::buffer(recv_buffer_), ep);
//       eps.insert(ep);
//       // if(eps.size()==2){
//       std::vector<char> buf(sz);
//       std::copy(recv_buffer_.begin(), recv_buffer_.begin() + sz,
//       buf.begin()); auto inp_vec = UnpackInput(buf);
//       // std::cout << "------------" << std::endl;
//       // std::cout << inp_vec.size() << std::endl;
//       // std::cout << "input" << inp_vec.back().player_id << " " <<
//       inp_vec.back().sequence << std::endl; for(auto &i : inp_vec){
//         game.ProcessInput(i);
//         // auto finp = i;
//         // finp.player_id=1;
//         // game.ProcessInput(finp);
//       }
//       auto state_to_send = game.GetState();
//       std::cout << "ts: " << state_to_send.sequence << "
//       state_to_send.snakes.size(): " << state_to_send.snakes.size() <<
//       std::endl; const auto flat = PackState(state_to_send); for(auto& i:
//       eps){
//         socket_.send_to(boost::asio::buffer(flat.data(), flat.size()), i);
//         // std::cout << i << " " << flat.size() << std::endl;
//       }
//       // }
//     }
//     // BeginDrawing();

//     // Draw(game.GetState(), kMapWidth, kMapHeight, kScale, kHeadDiameter,
//     //      kTailWidth);

//     // DrawFPS(10, 10);
//     // EndDrawing();
//   }

//   // CloseWindow();

//   return 0;
// }
