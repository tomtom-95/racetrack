#ifndef RACETRACK_HPP
#define RACETRACK_HPP

typedef boost::multi_array<double, 6> policy_array;
typedef boost::multi_array<int, 2> state_mask_array;

const int MAX_X_POS = 16;
const int MAX_Y_POS = 31;
const int MAX_VEL = 5;

const int MIN_ACTION = -1;
const int MAX_ACTION = 1;
const int NUM_ACTION = -MIN_ACTION + MAX_ACTION + 1;

const double eps = 0.01;

struct racetrack_state {
  int x_pos;
  int y_pos;
  int x_vel;
  int y_vel;
};


struct racetrack_action {
  int x_act;
  int y_act;
};

struct racetrack_state_reward {
  struct racetrack_state state;
  struct racetrack_action action;
};

#endif // RACETRACK_HPP
