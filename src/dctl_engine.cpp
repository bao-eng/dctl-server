#include "dctl_engine.h"

DCTLEngine::DCTLEngine(const State &initial_state, float map_width,
                       float map_height, float speed, double dt,
                       size_t max_length)
    : state_(initial_state),
      sequence_(1),
      players_in_game_(GetPlayers(initial_state)),
      map_width_(map_width),
      map_height_(map_height),
      speed_(speed),
      dt_(dt),
      max_length_(max_length) {}

State DCTLEngine::GetState() const { return state_; }

void DCTLEngine::ProcessInput(const Input &inp) {
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
      state_ = NextState(state_, input_buffer_.at(sequence_), dt_, speed_,
                         max_length_);
      state_ = CheckCollisions(state_);
      state_ = CheckBounds(state_, map_width_, map_height_);
      players_in_game_ = GetPlayers(state_);
      sequence_++;
      input_buffer_.erase(inp.sequence);
    }
  }
}
