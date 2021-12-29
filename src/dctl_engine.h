struct Input {
  uint32_t sequence;
  bool left;
  bool right;
  bool up;
  bool down;
};

class DCTLEngine{
  public:
    DCTLEngine(float map_width, float map_height, float scale, float speed, double dt,
       size_t max_length);
    
  private:

};