#include <boost/array.hpp>
#include <boost/asio.hpp>
#include <chrono>
#include <cmath>
#include <cstddef>
#include <deque>
#include <iostream>
#include <list>
#include <vector>

#include "dctl-common/src/dctl_common.h"
#include "dctl-common/src/dctl_input_generated.h"
#include "dctl-common/src/dctl_state_generated.h"
#include "dctl_engine.h"
#include "raylib.h"
#include "raymath.h"

using boost::asio::ip::udp;

const size_t kMapWidth = 107;
const size_t kMapHeight = 54;
const size_t kScale = 15;
const float kSpeed = (float)58 / 6;

int main() {
  SetConfigFlags(FLAG_MSAA_4X_HINT);
  InitWindow((kMapWidth + 1) * kScale, (kMapHeight + 1) * kScale, "snake");
  SetTargetFPS(100);

  uint32_t sequence{0};
  double t = 0.0;
  double dt = 0.01;
  auto current_time = std::chrono::system_clock::now();
  double accumulator = 0.0;

  State st;
  st.sequence = sequence;
  sequence++;

  Vector2 p1{3, ((float)kMapHeight / 2)};
  Snake s1{0,
           {p1,p1},
           Dir::kRight,
           (Color){0, 255, 255, 255}};  // CYAN
  Vector2 p2{kMapWidth - 3, (float)kMapHeight / 2};
  Snake s2{1, {p2, p2}, Dir::kLeft, (Color){255, 0, 255, 255}};  // MAGENTA
  Vector2 p3{(float)kMapWidth / 2, 3};
  Snake s3{2,
           {{p2.x - 10, p2.y - 10}, {p2.x - 10, p2.y - 10}},
           Dir::kDown,
           (Color){0, 255, 0, 255}};  // GREEN
  Vector2 p4{10 + (float)kMapWidth / 2, kMapHeight - 3};
  Snake s4{3, {p4, p4}, Dir::kRight, (Color){255, 255, 0, 255}};  // YELLOW

  st.snakes.push_back(s1);
  // st.snakes.push_back(s2);
  // st.snakes.push_back(s3);
  // st.snakes.push_back(s4);

  DCTLEngine game(st, kMapWidth, kMapHeight, kSpeed, dt, 60);

  boost::asio::io_service io_service_;
  udp::socket socket_(io_service_, udp::endpoint(udp::v4(), 7777));

  while (!WindowShouldClose())  // Detect window close button or ESC key
  {
    boost::array<char, 64000> recv_buffer_;
    while(socket_.available()){
      boost::asio::ip::udp::endpoint ep;
      auto sz = socket_.receive_from(boost::asio::buffer(recv_buffer_),ep);
      std::vector<char> buf(sz);
      std::copy(recv_buffer_.begin(), recv_buffer_.begin()+sz, buf.begin());
      auto inp =UnpackInput(buf);
      // std::cout << inp.player_id << " " << inp.sequence << inp.left << std::endl;
      game.ProcessInput(inp);
      auto flat = PackState(game.GetState());
      socket_.send_to(boost::asio::buffer(flat.data(), flat.size()),ep);
    }
    BeginDrawing();

    Draw(game.GetState(), kMapWidth, kMapHeight, kScale);

    DrawFPS(10, 10);
    EndDrawing();
  }

  CloseWindow();

  return 0;
}
