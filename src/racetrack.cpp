#include <iostream>
#include <vector>

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

  returns_type returns(boost::extents[MAX_X_POS+1][MAX_Y_POS+1][MAX_VEL+1][MAX_VEL+1][NUM_ACTION][NUM_ACTION]);

  Q_type Q(boost::extents[MAX_X_POS+1][MAX_Y_POS+1][MAX_VEL+1][MAX_VEL+1][NUM_ACTION][NUM_ACTION]);
  
  while (true) {
    episode_type episode = generate_episode(policy, state_mask);

    double G = 0;

    for (episode_type::iterator it = --episode.end(); it != episode.begin(); --it) {

      G -= 1;

      if(is_first_visit(episode, it)) { //TODO: sta roba funziona ma è lenta come la merda: c'è un modo migliore?

        struct racetrack_state state = (*it).state;
        struct racetrack_action action = (*it).action;

        int x_index = action_to_index(action.x_act);
        int y_index = action_to_index(action.y_act);

        returns[state.x_pos][state.y_pos][state.x_vel][state.y_vel][x_index][y_index].push_back(G);

        Q[state.x_pos][state.y_pos][state.x_vel][state.y_vel][x_index][y_index] =
        vector_avg(returns[state.x_pos][state.y_pos][state.x_vel][state.y_vel][x_index][y_index]);

        struct racetrack_action max_action = argmax_Q(Q, state);

        // update the policy with the eps-soft policy update for every action in S_t
        policy_update(policy,
                      state,
                      max_action);
      }
    }

    break; // only one episode
  }


  return 0;
}

