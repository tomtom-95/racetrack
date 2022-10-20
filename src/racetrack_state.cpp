#ifndef RACETRACK_STATE_CPP
#define RACETRACK_STATE_CPP

#include <cstdlib>
#include <time.h>

#include "racetrack.hpp"


struct racetrack_state
pick_start()
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

  /* when the car is in a not allowed state it jumps back to the start */
  if (next_state.x_vel > MAX_VEL || next_state.y_vel > MAX_VEL) {
    return pick_start();
  }

  if (next_state.x_vel < 0 || next_state.y_vel < 0) {
    return pick_start();
  }

  if (next_state.x_vel == 0 && next_state.y_vel == 0) {
    return pick_start();
  }

  if (next_state.x_pos < 0 || next_state.y_pos < 0) {
    return pick_start();
  }

  if (next_state.y_pos > MAX_Y_POS) {
    return pick_start();
  }

  if (next_state.y_pos < 26) {
    if (state_mask[next_state.x_pos][next_state.y_pos] == 0) {
      return pick_start();
    }
  }


  return next_state;
}

bool is_terminal(struct racetrack_state &state) {
  return (state.y_pos >= 26 && state.x_pos >= MAX_X_POS) ? true : false;
}

void state_read(struct racetrack_state &state) {
  std::cout << state.x_pos << " " << state.y_pos << " " << state.x_vel << " " << state.y_vel;
}


void action_read(struct racetrack_action &action) {
  std::cout << action.x_act << " " << action.y_act;
} 


void state_action_read(struct racetrack_state_action &state_action) {
  state_read(state_action.state);
  std::cout << '\n';
  action_read(state_action.action);
}


bool operator==(struct racetrack_state &lhs, struct racetrack_state &rhs) {
  return (lhs.x_pos == rhs.x_pos &&
          lhs.y_pos == rhs.y_pos &&
          lhs.x_vel == rhs.x_vel &&
          lhs.y_vel == rhs.y_vel);
}

bool operator==(struct racetrack_action &lhs, struct racetrack_action &rhs) {
  return (lhs.x_act == rhs.x_act &&
          lhs.y_act == rhs.y_act);
}

bool operator==(struct racetrack_state_action &lhs, struct racetrack_state_action &rhs) {
  return (lhs.state == rhs.state && 
          lhs.action == rhs.action);
}

// action and velocity conversion to the indices in the arrays
int action_to_index(int action) {
  return action + 1;
}

int index_to_action(int index) {
  return index - 1;
}



#endif // RACETRACK_STATE_CPP
