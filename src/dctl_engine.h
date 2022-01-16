#pragma once

#include <iostream>
#include <unordered_map>
#include <unordered_set>

#include "dctl-common/src/dctl_common.h"

class ServerEngine {
 public:
  ServerEngine(const State &initial_state, const Settings &settings);
  State GetState() const;
  void ProcessInput(const Input &inp);

 private:
  Settings settings_;
  uint32_t sequence_;
  State state_;
  std::unordered_set<int> players_in_game_;
  std::unordered_map<uint32_t, std::unordered_map<int, Input>> input_buffer_;
};
