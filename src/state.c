#include "thekey.h"


void state_init() {
	key.state.cur_state = THEKEY_STATE_DUMMY;
	key.state.new_state = THEKEY_STATE_INGAME;

	return;
}
