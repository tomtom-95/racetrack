#include <cstdlib>
#include <time.h>

#include "racetrack.hpp"


struct racetrack_state
return_to_start()
{
  srand(time(0));
  
  struct racetrack_state start_state = {
    .x_pos = (rand() % 6) + 3,
    .y_pos = 0,
    .x_vel = 0,
    .y_vel = 0
  };

  return start_state;
}


/* transition from current_state to next_state when a certain action is made */
struct racetrack_state 
state_transition(struct racetrack_state &current_state, 
                 struct racetrack_action &action, 
                 state_mask_array &state_mask) 
{

  struct racetrack_state next_state = {
    .x_pos = current_state.x_pos + current_state.x_vel,
    .y_pos = current_state.y_pos + current_state.y_vel,
    .x_vel = current_state.x_vel + action.x_act,
    .y_vel = current_state.y_vel + action.y_act
  };

  if (next_state.x_vel > MAX_VEL) {
    next_state.x_vel = MAX_VEL;
  }

  if (next_state.y_vel > MAX_VEL) {
    next_state.y_vel = MAX_VEL;
  }

  if (next_state.x_pos < 0 || next_state.y_pos < 0) {
    next_state = return_to_start();
  }

  if (next_state.y_pos > MAX_Y_POS) {
    next_state = return_to_start();
  }

  if (state_mask[next_state.x_pos][next_state.y_pos] == 0) {
    next_state = return_to_start();
  }


  return next_state;
}
