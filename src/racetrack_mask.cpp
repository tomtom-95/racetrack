/* initialize the racetrack map 
the racetrack is 1 for in boundary position and 0 for out of boundary position */

#include "racetrack.hpp"


void state_mask_init(state_mask_array &state_mask) {
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
}

void state_mask_read(state_mask_array &state_mask) {
  for (state_mask_array::index y_pos = 0; y_pos < MAX_Y_POS + 1; ++y_pos) {
    for (state_mask_array::index x_pos = 0; x_pos < MAX_X_POS + 1; ++x_pos) {
      std::cout << state_mask[x_pos][MAX_Y_POS - y_pos];
    }
    std::cout << std::endl;
  }
}
