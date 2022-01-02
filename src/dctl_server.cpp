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

// using boost::asio::ip::udp;

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

  Vector2 p1{3, ((float)kMapHeight / 2) + 10};
  Snake s1{0,
           {p1,
            {p1.x + 10, p1.y},
            {p1.x + 10, p1.y + 10},
            {p1.x + 5, p1.y + 10},
            {p1.x + 5, p1.y + 10}},
           Dir::kUp,
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
  st.snakes.push_back(s2);
  st.snakes.push_back(s3);
  st.snakes.push_back(s4);

  DCTLEngine game(kMapWidth, kMapHeight, kSpeed, dt, 60);
  game.SetState(st);

  while (!WindowShouldClose())  // Detect window close button or ESC key
  {
    Input inp{sequence, 0, false, false, false, false};
    game.ProcessInput(inp);
    inp.player_id = 1;
    game.ProcessInput(inp);
    inp.player_id = 2;
    game.ProcessInput(inp);
    inp.player_id = 3;
    game.ProcessInput(inp);
    sequence++;
    BeginDrawing();

    Draw(game.GetState(), kMapWidth, kMapHeight, kScale);

    DrawFPS(10, 10);
    EndDrawing();
  }

  CloseWindow();

  return 0;
}
