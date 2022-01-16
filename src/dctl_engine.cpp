#include "dctl_engine.h"

ServerEngine::ServerEngine(const State &initial_state, const Settings &settings)
    : state_(initial_state),
      sequence_(1),
      players_in_game_(GetPlayers(initial_state)),
      settings_(settings) {}

State ServerEngine::GetState() const { return state_; }

void ServerEngine::ProcessInput(const Input &inp) {
  if ((inp.sequence >= sequence_) &&
      (players_in_game_.find(inp.player_id) != players_in_game_.end()) &&
      (input_buffer_[inp.sequence].find(inp.player_id) ==
       input_buffer_[inp.sequence].end())) {
    input_buffer_[inp.sequence][inp.player_id] = inp;
    if (inp.sequence == sequence_) {
      for (auto &i : players_in_game_) {
        if (input_buffer_.at(sequence_).find(i) ==
            input_buffer_.at(sequence_).end()) {
          return;
        }
      }
      state_ = NextState(state_, input_buffer_.at(sequence_), settings_.dt,
                         settings_.speed, settings_.max_length);
      state_ = CheckCollisions(state_);
      state_ = CheckBounds(state_, settings_.map_width, settings_.map_height);
      players_in_game_ = GetPlayers(state_);
      sequence_++;
      input_buffer_.erase(inp.sequence);
    }
  }
}
