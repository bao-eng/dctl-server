#include "dctl_engine.h"

DCTLEngine::DCTLEngine(float map_width, float map_height, float speed,
                       double dt, size_t max_length)
    : map_width_(map_width),
      map_height_(map_height),
      speed_(speed),
      dt_(dt),
      max_length_(max_length) {}

State DCTLEngine::NextState(const State &st,
                            const std::unordered_map<int, Input> &inp) {
  State ns;
  for (auto &i : st.snakes) {
    auto tmp = i;
    auto newDir = NewDir(i.dir, inp.at(i.player_id));
    if (newDir != i.dir) {
      tmp.dir = newDir;
      tmp.tail.push_back(tmp.tail.back());
      if (tmp.tail.size() > max_length_) {
        tmp.tail.pop_front();
      }
    }
    tmp.tail.back() = NewPos(tmp.dir, dt_ * speed_, tmp.tail.back());
    ns.snakes.push_back(tmp);
  }
  ns.sequence = st.sequence + 1;
  return ns;
}

void DCTLEngine::SetState(const State &st) {
  state_ = st;
  sequence_ = st.sequence + 1;
  players_in_game_.clear();
  for(auto& i: state_.snakes){
    players_in_game_.insert(i.player_id);
  }
}

State DCTLEngine::GetState()const{
  return state_;
}

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
      state_ = NextState(state_, input_buffer_.at(sequence_));
      state_ = CheckCollisions(state_);
      players_in_game_.clear();
      for (auto &i : state_.snakes){
        players_in_game_.insert(i.player_id);
      }
      sequence_++;
      input_buffer_.erase(inp.sequence);
    }
  }
}

State DCTLEngine::CheckCollisions(const State &st) {
  State ns;
  ns.sequence = st.sequence;
  std::unordered_set<int> valid;
  for (auto &i : st.snakes) {
    valid.insert(i.player_id);
  }
  // for (auto &i : st.snakes) {
  //   if (!IsSelfIntersecting(i)) {
  //     valid.insert(i.player_id);
  //   }
  // }
  for (auto &i : st.snakes) {
    for (auto &j : st.snakes) {
      // if (i.player_id != j.player_id) {
      if (IsCrossing(i, j)) {
        valid.erase(i.player_id);
      }
    }
  }
  for (auto &i : st.snakes) {
    if(valid.find(i.player_id)!=valid.end()){
      ns.snakes.push_back(i);
    }
  }
  return ns;
}
