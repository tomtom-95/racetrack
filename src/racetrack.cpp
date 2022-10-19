#include <iostream>

#include "boost/multi_array.hpp"
#include <cassert>

#include "racetrack.hpp"
#include "racetrack_mask.cpp"
#include "racetrack_policy.cpp"
#include "racetrack_state.cpp"


int main(void) {

  std::default_random_engine generator;

  policy_array policy(boost::extents[MAX_X_POS+1][MAX_Y_POS+1][MAX_VEL+1][MAX_VEL+1][NUM_ACTION][NUM_ACTION]);
  policy_init(policy);

  state_mask_array state_mask(boost::extents[MAX_X_POS+1][MAX_Y_POS+1]);
  state_mask_init(state_mask);

  struct racetrack_state initial_state = {.x_pos = 3, .y_pos = 0};
  struct racetrack_action action = generate_action(policy, initial_state);

  struct racetrack_state next_state = state_transition(initial_state, action, state_mask);
  std::cout << next_state.x_pos << " " << next_state.y_pos << " " << next_state.x_vel << " " << next_state.y_vel << std::endl;
  action = generate_action(policy, next_state);
  next_state = state_transition(next_state, action, state_mask);
  std::cout << next_state.x_pos << " " << next_state.y_pos << " " << next_state.x_vel << " " << next_state.y_vel << std::endl;

  return 0;
}

