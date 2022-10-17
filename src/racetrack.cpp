/*
first of all I have to choose the method I will use
I'll try On policy Monte-Carlo (page 101 pseudo code)
states: position on the track and current horizontal and vertical velocity
if I go beyond the track I must start again in the initial state with zero velocity
rewards are always 0 apart from when I arrive at the end of the track (+1 reward)
velocity indicates how much square I move vertically and horizontally
actions = [x_vel_update]x[y_vel_update] : 2-values array
states = [x_pos, y_pos]x[x_vel, y_vel] : 4-values array
Q(s,a) : action-value function
policy(a|s) : policy -> it is and eps-soft policy
*/

/*
How do I represent Q(s,a)? I see a problem in state: there are a lot of state so I am afraid that store all Q(s,a)
could be too big 1-32 : 1-17
x_pos: from 0 to 31
y_pos: from 0 to 16
if x_pos < 0 or x_pos > 31 or y_pos < 0 or y_pos > 16: fail
  apart from this obviously wrong states there are other one in the space of x and y pos that must be excluded
31 * 16 * 5
*/

#include <iostream>
#include <vector>

const int MAX_X_POS = 16;
const int MAX_Y_POS = 31;
const int MAX_VEL = 5;

int main(void) {
  double Q[MAX_X_POS][MAX_Y_POS][MAX_VEL][MAX_VEL] = {};
  double policy[MAX_X_POS][MAX_Y_POS][MAX_VEL][MAX_VEL] = {}; // TODO: initialize as an eps-soft policy
  std::vector<double> returns[MAX_X_POS][MAX_Y_POS][MAX_VEL][MAX_VEL] = {};

  // this is the kind of loop that I will write a lot
  returns[0][0][0][0].push_back(2.4);
  for (int x_pos = 0; x_pos < MAX_X_POS + 1; ++x_pos) {
    for (int y_pos = 0; y_pos < MAX_Y_POS + 1; ++y_pos) {
      for (int x_vel = 0; x_vel < MAX_VEL + 1; ++x_vel) {
        for (int y_vel = 0; y_vel < MAX_VEL + 1; ++y_vel) {
          for (auto &i: returns[x_pos][y_pos][x_vel][y_vel]) {
            std::cout << i << std::endl;
          }
        }
      }
    }
  }

  // state mask initialization
  int state_mask[MAX_X_POS + 1][MAX_Y_POS + 1] = {};
  for (int i = 3; i < 9; ++i) {
    for (int j = 0; j < 3; ++j) {
      state_mask[i][j] = 1;
    }
  }
  
  for (int i = 2; i < 9; ++i) {
    for (int j = 3; j < 10; ++j) {
      state_mask[i][j] = 1;
    }
  }

  for (int i = 1; i < 9; ++i) {
    for (int j = 10; j < 18; ++j) {
      state_mask[i][j] = 1;
    }
  }

  for (int i = 0; i < 9; ++i) {
    for (int j = 18; j < 25; ++j) {
      state_mask[i][j] = 1;
    }
  }

  for (int i = 0; i < 10; ++i) {
    state_mask[i][25] = 1;
  }

  for (int i = 0; i < MAX_X_POS + 1; ++i) {
    state_mask[i][26] = 1;
    state_mask[i][27] = 1;
  }

  for (int i = 1; i < MAX_X_POS + 1; ++i) {
    state_mask[i][28] = 1;
  }

  for (int i = 2; i < MAX_X_POS + 1; ++i) {
    state_mask[i][29] = 1;
  }

  for (int i = 2; i < MAX_X_POS + 1; ++i) {
    state_mask[i][30] = 1;
  }

  for (int i = 3; i < MAX_X_POS + 1; ++i) {
    state_mask[i][31] = 1;
  }

  // end state_mask initialization

  for (int i = 0; i < MAX_Y_POS + 1; ++i) {
    for (int j = 0; j < MAX_X_POS + 1; ++j) {
      std::cout << state_mask[j][MAX_Y_POS - i];
    }
    std::cout << '\n';
  }

  // TODO: use the mask and to understand if I go off the track 


  return 0;
}
