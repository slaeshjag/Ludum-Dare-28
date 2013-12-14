/* No fancy message system. Nobody aint got time for that! */
#include "thekey.h"
#include <string.h>


void ai_dummy(int i, enum AI_MSG msg) {
	return;
}


void ai_bullet(int id, enum AI_MSG msg) {
	DARNIT_PARTICLE *p;
	switch (msg) {
		case AI_MSG_INIT:
			break;
		case AI_MSG_DESTROY:
			p = d_particle_new(100, DARNIT_PARTICLE_TYPE_POINT);
			d_particle_emitter_move(p, 0, 0);
			d_particle_color_start(p, 220, 220, 0, 255);
			d_particle_color_target(p, 127, 0, 0, 0);
			d_particle_emitter_velocity(p, 200, 300);
			d_particle_life(p, 500);
			d_particle_mode(p, DARNIT_PARTICLE_MODE_PULSAR);
			d_particle_point_size(p, 2);
			d_particle_emitter_angle(p, 0, 3599);
			particle_new_pulse(p, key.chr.entry[id].x / 1000 + 4, key.chr.entry[id].y / 1000 + 4);
			break;
		case AI_MSG_LOOP:
			if (!key.chr.entry[id].x_vel)
				character_delete(id);
			break;
	}

	return;
}

void ai_player(int id, enum AI_MSG msg) {
	int n;
	DARNIT_KEYS k;

	d_keys_zero();

	if (msg == AI_MSG_INIT) {
		key.map.character_follow = id;
		return;
	}

	if (d_keys_get().left) {
		key.chr.entry[id].x_vel = -200;
		key.chr.entry[id].dir = 0;
	} else if (d_keys_get().right) {
		key.chr.entry[id].dir = 1;
		key.chr.entry[id].x_vel = 200;
	} else 
		key.chr.entry[id].x_vel = 0;
	if (d_keys_get().x)
		key.chr.entry[id].y_vel = -300000;
	
	if (d_keys_get().y) {
		k.y = 1;
		d_keys_set(k);
		if (key.chr.entry[id].dir) {	/* Looking right */
			n = character_add(ai_bullet, key.chr.entry[id].x / 1000, key.chr.entry[id].y / 1000, key.chr.entry[id].l, "res/bullet.spr");
			key.chr.entry[n].x_vel = 500;
		} else {			/* Looking left */
			n = character_add(ai_bullet, key.chr.entry[id].x / 1000, key.chr.entry[id].y / 1000, key.chr.entry[id].l, "res/bullet.spr");
			key.chr.entry[n].x_vel = -500;
		}
	}
		
}


void *ai_lookup(const char *str) {
	if (!strcmp(str, "dummy")) return ai_dummy;
	if (!strcmp(str, "player")) return ai_player;

	fprintf(stderr, "Unimplemented AI %s\n", str);
	return ai_dummy;
}
