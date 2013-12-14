#include "thekey.h"


int main(int argc, char **argv) {
	d_init("The key", "thekey", NULL);
	key.platform = d_platform_get();
	d_fs_mount_self();
	character_init();
	map_init();
	state_init();

	for (;;) {
		d_render_begin();

		state_loop();

		d_render_end();
		d_loop();
	}

	d_quit();
}
