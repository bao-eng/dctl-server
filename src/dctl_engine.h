#pragma once

#include <map>
#include <set>
#include <unordered_set>
#include <unordered_map>

#include "dctl-common/src/dctl_common.h"

class DCTLEngine {
 public:
  DCTLEngine(float map_width, float map_height, float scale, float speed,
             double dt, size_t max_length);
  void ProcessInput(const Input &inp);
  State NextState(const State &st, const std::unordered_map<int, Input> &);
  State CheckCollisions(const State &st);

 private:
  float map_width_;
  float map_height_;
  float speed_;
  size_t max_length_;

  uint32_t sequence_{0};
  double t_;            // = 0.0;
  double dt_;           // = 0.01;
  double current_time;  // = std::chrono::system_clock::now();
  double accumulator;   // = 0.0;
  State state_;
  std::set<int> players_in_game_;
  std::unordered_map<uint32_t, std::unordered_map<int, Input>> input_buffer_;
};