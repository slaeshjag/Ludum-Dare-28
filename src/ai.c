/* No fancy message system. Nobody aint got time for that! */
#include "thekey.h"
#include <string.h>


void ai_dummy(int i) {
	return;
}


void ai_player(int id) {
	if (d_keys_get().left)
		key.chr.entry[id].x_vel = -200;
	else if (d_keys_get().right)
		key.chr.entry[id].x_vel = 200;
	else 
		key.chr.entry[id].x_vel = 0;
	if (d_keys_get().x)
		key.chr.entry[id].y_vel = -300000;
		
}


void *ai_lookup(const char *str) {
	if (!strcmp(str, "dummy")) return ai_dummy;
	if (!strcmp(str, "player")) return ai_player;

	fprintf(stderr, "Unimplemented AI %s\n", str);
	return ai_dummy;
}
