#include "thekey.h"


void map_init() {
	key.map.map = NULL;
	key.map.camera_x = key.map.camera_y = 0;

	return;
}


void map_load(const char *fname) {
	if (!fname)
		return;
	if (key.map.map)
		key.map.map = d_map_unload(key.map.map);
	key.map.map = d_map_load(fname);

	/* TODO: Spawn characters */

	return;
}

