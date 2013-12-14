#include "thekey.h"


void state_init() {
	key.state.cur_state = THEKEY_STATE_DUMMY;
	key.state.new_state = THEKEY_STATE_INGAME;

	return;
}


void state_loop() {
	if (key.state.cur_state != key.state.new_state) {
		switch (key.state.cur_state) {
			case THEKEY_STATE_DUMMY:
			case THEKEY_STATE_MAINMENU:
			case THEKEY_STATE_INGAME:
				break;
		}

		switch (key.state.new_state) {
			case THEKEY_STATE_DUMMY:
			case THEKEY_STATE_MAINMENU:
				break;
			case THEKEY_STATE_INGAME:
				map_load("res/testlevel.ldmz");
				break;
		}

		key.state.cur_state = key.state.new_state;
	} else {
		switch (key.state.cur_state) {
			case THEKEY_STATE_DUMMY:
			case THEKEY_STATE_MAINMENU:
				break;
			case THEKEY_STATE_INGAME:
				character_loop();

				d_render_offset(key.map.camera_x, key.map.camera_y);
				map_draw();
				particle_loop();
				break;
		}
	}

	return;
}
