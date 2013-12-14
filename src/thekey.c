#include "thekey.h"


int main(int argc, char **argv) {
	d_init("The key", "thekey", NULL);
	d_fs_mount_self();
	character_init();
	map_init();
	state_init();

	for (;;) {
		d_render_begin();


		d_render_end();
		d_loop();
	}

	d_quit();
}
