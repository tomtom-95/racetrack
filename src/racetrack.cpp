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

  generate_episode(policy, state_mask);


  return 0;
}

