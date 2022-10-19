#include "racetrack.hpp"

#include <iostream>
#include <iomanip>
#include <map>
#include <random>


void policy_init(policy_array &policy) {
  for (policy_array::index x_pos = 0; x_pos < MAX_X_POS + 1; ++x_pos) {
    for (policy_array::index y_pos = 0; y_pos < MAX_Y_POS + 1; ++y_pos) {
      for (policy_array::index x_vel = 0; x_vel < MAX_VEL + 1; ++x_vel) {
        for (policy_array::index y_vel = 0; y_vel < MAX_VEL + 1; ++y_vel) {
          for (policy_array::index x_act = 0; x_act < NUM_ACTION; ++x_act) {
            for (policy_array::index y_act = 0; y_act < NUM_ACTION; ++y_act) {
              policy[x_pos][y_pos][x_vel][y_vel][x_act][y_act] = 1.0 / (NUM_ACTION * NUM_ACTION);
            }
          }
        }
      }
    }
  }
}


void policy_read(policy_array &policy) {
  for (policy_array::index x_pos = 0; x_pos < MAX_X_POS + 1; ++x_pos) {
    for (policy_array::index y_pos = 0; y_pos < MAX_Y_POS + 1; ++y_pos) {
      for (policy_array::index x_vel = 0; x_vel < MAX_VEL + 1; ++x_vel) {
        for (policy_array::index y_vel = 0; y_vel < MAX_VEL + 1; ++y_vel) {
          for (policy_array::index x_act = 0; x_act < NUM_ACTION; ++x_act) {
            for (policy_array::index y_act = 0; y_act < NUM_ACTION; ++y_act) {
              std::cout << policy[x_pos][y_pos][x_vel][y_vel][x_act][y_act] << std::endl;
            }
          }
        }
      }
    }
  }
}

// ora: devo costruire un metodo capace di decidere quale azione compiere (scegliere un numero compreso tra -1 ed 1)
// basandosi sulle probabilità che trova nella sub-matrice [x_act][y_act]
// I must pick the greedy action 
// when I am in a certain state, pos and velocity, I must be able to generate a trajectory that follows the current policy
// that end up in one of the terminal states
struct racetrack_action
generate_action(policy_array &policy,
                struct racetrack_state prev_state)
{
  typedef boost::multi_array<double, 2> prob_array;

  prob_array prob = policy[prev_state.x_pos][prev_state.y_pos][prev_state.x_vel][prev_state.y_vel];

  std::random_device rd;
  std::mt19937 gen(rd());
  std::discrete_distribution<> prob_dist({prob[0][0], prob[0][1], prob[0][2],
                                          prob[1][0], prob[1][1], prob[1][2],
                                          prob[2][0], prob[2][1], prob[2][2]});

  int act = prob_dist(gen);
  int x_act = (act / NUM_ACTION) + MIN_ACTION;
  int y_act = (act % NUM_ACTION) + MIN_ACTION;

  struct racetrack_action action = {.x_act = x_act, .y_act = y_act};

  return action;
}
