#include <iostream>
#include <vector>
#include <cstdlib>
#include <random>
#include <array>

#include "boost/multi_array.hpp"
#include <cassert>

#include "racetrack.hpp"
#include "racetrack_mask.cpp"
#include "racetrack_policy.cpp"


struct racetrack_state 
move_car(struct racetrack_state current, 
         int x_action, 
         int y_action, 
         int state_mask[MAX_X_POS + 1][MAX_Y_POS + 1]) 
{
  current.x_vel += x_action;
  current.y_vel += y_action;
  current.x_pos += current.x_vel;
  current.y_pos += current.y_vel;

  if (26 >= current.y_pos && current.y_pos <= MAX_Y_POS) {
    if (current.x_pos >= MAX_X_POS) {
      return current;
    }
  }

  if (current.x_pos < 0 || current.y_pos < 0 || current.x_pos > MAX_X_POS || current.y_pos > MAX_Y_POS || state_mask[current.x_pos][current.y_pos] == 0) {
    current.x_vel = 0;
    current.y_vel = 0;
    current.x_pos = rand() % 6 + 3;
    current.y_pos = 0;
  }

  return current;
}


int main(void) {

  std::default_random_engine generator;

  policy_array policy(boost::extents[MAX_X_POS+1][MAX_Y_POS+1][MAX_VEL+1][MAX_VEL+1][NUM_ACTION][NUM_ACTION]);
  policy_init(policy);

  state_mask_array state_mask(boost::extents[MAX_X_POS+1][MAX_Y_POS+1]);
  state_mask_init(state_mask);

  struct racetrack_state initial_state = {.x_pos = 3, .y_pos = 0};
  struct racetrack_action action = generate_action(policy, initial_state);
  std::cout << action.x_act << "  " << action.y_act << std::endl;


  return 0;
}

