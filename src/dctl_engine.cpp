#include "dctl_engine.h"

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

void DCTLEngine::ProcessInput(const Input &inp) {
  if (input_buffer_[inp.sequence].find(inp.player_id) ==
      input_buffer_[inp.sequence].end()) {
    input_buffer_[inp.sequence][inp.player_id] = inp;
    if (inp.sequence == sequence_) {
      for (auto &i : players_in_game_) {
        if (input_buffer_.at(sequence_).find(i) ==
            input_buffer_.at(sequence_).end()) {
          return;
        }
      }
      state_ = NextState(state_, input_buffer_.at(sequence_));

      input_buffer_.erase(inp.sequence);
    }
  }
}

State CheckCollisions(const State &st) {
  State ns;
  ns.sequence = st.sequence;
  std::unordered_set<int> valid;
  for(auto& i: st.snakes){
    if(!IsSelfIntersecting(i)){
      valid.insert(i.player_id);
    }
  }
  
}


