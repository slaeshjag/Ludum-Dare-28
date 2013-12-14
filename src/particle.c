#include "thekey.h"


void particle_init() {
	key.p.p = NULL;
	key.p.particles = 0;
	key.p.used = 0;

	return;
}


void particle_new_pulse(DARNIT_PARTICLE *p, int x, int y) {
	int i, k;

	if (key.p.used == key.p.particles) {
		key.p.particles += 8;
		key.p.p = realloc(key.p.p, sizeof(*key.p.p) * key.p.particles);
		for (i = key.p.used; i < key.p.particles; i++)
			key.p.p[i].p = NULL;
		k = key.p.used++;
	} else for (i = 0; i < key.p.particles; i++)
		if (!key.p.p[i].p)
			k = i;
	key.p.p[k].p = p;
	key.p.p[k].x = x;
	key.p.p[k].y = y;
	d_particle_pulse(p);
}


void particle_loop() {
	int i;

	for (i = 0; i < key.p.particles; i++) {
		if (!key.p.p[i].p)
			continue;
		
		d_render_offset(-key.p.p[i].x - key.map.camera_x, -key.p.p[i].y - key.map.camera_y);
		d_particle_draw(key.p.p[i].p);
		if (!d_particle_used(key.p.p[i].p)) {	/* Particle is done pulsing */
			key.p.p[i].p = d_particle_free(key.p.p[i].p);
			key.p.used--;
		}
	}

	return;
}


void particle_destroy_all() {
	int i;

	for (i = 0; i < key.p.particles; i++)
		if (key.p.p[i].p)
			d_particle_free(key.p.p[i].p);
	free(key.p.p);
	key.p.p = NULL;
	key.p.particles = key.p.used = 0;

	return;
}
