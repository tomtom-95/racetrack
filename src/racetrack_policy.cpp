#ifndef RACETRACK_POLICY_CPP
#define RACETRACK_POLICY_CPP

#include <random>
#include <vector>

#include "racetrack.hpp"
#include "racetrack_state.cpp"


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


void policy_update(policy_array &policy,
                   struct racetrack_state &state,
                   struct racetrack_action &max_action)
{
  // typedef boost::multi_array<double, 2> sub_array;

  // sub_array::index -> int
  for (int i = 0; i < NUM_ACTION; ++i) {
    for (int j = 0; j < NUM_ACTION; ++j) {
      if (i == max_action.x_act + 1 && j == max_action.y_act + 1) {
        policy[state.x_pos][state.y_pos][state.x_vel][state.y_vel][i][j] = 1.0 - eps + eps / (NUM_ACTION * NUM_ACTION);
      }
      else {
        policy[state.x_pos][state.y_pos][state.x_vel][state.y_vel][i][j] = eps / (NUM_ACTION * NUM_ACTION);
      }
    }
  }
}


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


episode_type
generate_episode(policy_array &policy,
                 state_mask_array &state_mask) 
{
  episode_type episode = {};

  struct racetrack_state state = pick_start();  
  struct racetrack_action action = generate_action(policy,
                                                   state);

  struct racetrack_state_action state_action = {
    .state = state,
    .action = action
  };

  episode.push_back(state_action);

  while (!is_terminal(state)) {
    action = generate_action(policy,
                             state);

    state = state_transition(state,
                             action,
                             state_mask);

    state_action = {
      .state = state,
      .action = action
    };

    episode.push_back(state_action);
  }


  return episode;
}

bool is_first_visit(episode_type &episode,
                    episode_type::iterator &it)
{
  for (episode_type::iterator el = episode.begin(); el != it; ++el) {
    if (*el == *it) {
      return false;
    }
  }
  return true;
}

double vector_avg(std::vector<double> &vec) {
  if (vec.begin() == vec.end()) {
    return 0;
  }
  else {
    double avg = 0;

    for (std::vector<double>::iterator beg = vec.begin(); beg != vec.end(); ++beg) {
      avg += *beg; 
    }

    return avg / vec.size();
  }
}

struct racetrack_action
argmax_Q(Q_type &Q,
         struct racetrack_state &state)
{
  typedef boost::multi_array<double, 2> sub_array;

  sub_array
  Q_sub_mat = Q[state.x_pos][state.y_pos][state.x_vel][state.y_vel];

  double max_value = 0;
  struct racetrack_action max_action = {.x_act = 0, .y_act = 0};
  
  // sub_array::index -> int
  for (int i = 0; i < NUM_ACTION; ++i) {
    for (int j = 0; j < NUM_ACTION; ++j) {
      double value = Q_sub_mat[i][j];
      if (value > max_value) {
        max_value = value;
        max_action = {.x_act = i - 1, .y_act = j - 1};
      }
    }
  }


  return max_action;
}


#endif // RACETRACK_POLICY_CPP
