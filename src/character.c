#include "thekey.h"


void character_init() {
	key.chr.entry = NULL;
	key.chr.entries = 0;
	key.chr.used = 0;

	return;
}


void character_delete(int i) {
	if (key.chr.entries <= i) {
		fprintf(stderr, "This will go bad: character_delete\n");
		return;
	}

	if (key.map.character_follow == i)
		key.map.character_follow = -1;

	key.chr.entry[i].sprite = d_sprite_free(key.chr.entry[i].sprite);
	key.chr.used--;
}


void character_add(void *handler, int x, int y, int l, const char *fname) {
	int i, k;

	if (key.chr.entries == key.chr.used) {
		key.chr.entries += 8;
		key.chr.entry = realloc(key.chr.entry, sizeof(*key.chr.entry) * key.chr.entries);
		for (i = key.chr.used; i < key.chr.entries; i++) 
			key.chr.entry[i].handler = NULL;
		k = key.chr.used++;
	} else
		for (i = 0; i < key.chr.entries; i++)
			if (!key.chr.entry[i].handler)
				k = i;

	key.chr.entry[k].handler = handler;
	key.chr.entry[k].x = x * 1000;
	key.chr.entry[k].y = y * 1000;
	key.chr.entry[k].l = l;
	key.chr.entry[k].x_rest = 0;
	key.chr.entry[k].y_rest = 0;
	key.chr.entry[k].x_vel = 0;
	key.chr.entry[k].y_vel = 0;
	key.chr.entry[k].sprite = d_sprite_load(fname, 0, DARNIT_PFORMAT_RGB5A1);
	d_sprite_animate_start(key.chr.entry[k].sprite);
	
	return;
}


void character_move(int i, int dx, int dy) {
	/* dx, dy = -1 .. 1 */
	int c, hx, hy, hw, hh, l, ti, rx, ry;
	
	d_sprite_hitbox(key.chr.entry[i].sprite, &hx, &hy, &hw, &hh);
	l = key.chr.entry[i].l;

	/* X-axis */
	rx = key.chr.entry[i].x / 1000 - hx;
	ry = key.chr.entry[i].x / 1000 - hy;
	if (dx < 0) {
		c = (key.chr.entry[i].x + dx) / 1000 - hx;
		if (c != rx) {
			ti = c / key.map.map->layer[l].tile_w;
			if (ti != rx / key.map.map->layer[l].tile_w) {
				ti += (ry / key.map.map->layer[l].tile_h) * key.map.map->layer[l].tilemap->w;
				if (key.map.map->layer[l].tilemap->data[ti] & MAP_COLLIDE_LEFT);	/* Collision! */
				else
					key.chr.entry[i].x += dx;
			} else
				key.chr.entry[i].x += dx;
		} else
			key.chr.entry[i].x += dx;
	} else if (dx > 0) {
		rx -= hw;
		c = (key.chr.entry[i].x + dx) / 1000 - hx - hw;
		if (c != rx) {
			ti = c / key.map.map->layer[l].tile_w;
			if (ti != rx / key.map.map->layer[l].tile_w) {
				ti += (ry / key.map.map->layer[l].tile_h) * key.map.map->layer[l].tilemap->w;
				if (key.map.map->layer[l].tilemap->data[ti] & MAP_COLLIDE_RIGHT);	/* Collision! */
				else
					key.chr.entry[i].x += dx;
			} else
				key.chr.entry[i].x += dx;
		} else
			key.chr.entry[i].x += dx;
	}

	return;
}


void character_loop() {
	int i;

	for (i = 0; i < key.chr.entries; i++) {
		if (!key.chr.entry[i].handler)
			continue;
		d_sprite_move(key.chr.entry[i].sprite, key.chr.entry[i].x / 1000, key.chr.entry[i].y / 1000);
		/* TODO: Do stuff */
	}

	return;
}


void character_draw(int layer) {
	int i;
	
	for (i = 0; i < key.chr.entries; i++) {
		if (!key.chr.entry[i].handler)
			continue;
		d_sprite_draw(key.chr.entry[i].sprite);
	}

	return;
}
