#pragma once

#include <unordered_map>
#include <unordered_set>

#include "dctl-common/src/dctl_common.h"

class DCTLEngine {
 public:
  DCTLEngine(const State &initial_state, float map_width, float map_height,
             float speed, double dt, size_t max_length, const float head_diameter, const float tail_width);
  State GetState() const;
  void ProcessInput(const Input &inp);

 private:
  float map_width_;
  float map_height_;
  float speed_;
  size_t max_length_;
  float head_diameter_;
  float tail_width_;
  uint32_t sequence_{0};
  double dt_;
  State state_;
  std::unordered_set<int> players_in_game_;
  std::unordered_map<uint32_t, std::unordered_map<int, Input>> input_buffer_;
};
