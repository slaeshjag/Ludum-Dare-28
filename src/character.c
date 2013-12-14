#include "thekey.h"

#define	abs(x)		((x) < 0 ? (x) * -1 : (x))


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


int character_move(int i, int dx, int dy) {
	/* dx, dy = -1 .. 1 */
	int c, hx, hy, hw, hh, l, ti, rx, ry, col;
	
	col = 0;
	d_sprite_hitbox(key.chr.entry[i].sprite, &hx, &hy, &hw, &hh);
	l = key.chr.entry[i].l;

	/* X-axis */
	rx = key.chr.entry[i].x / 1000 + hx;
	ry = key.chr.entry[i].y / 1000 + hy;
	if (dx < 0) {
		c = (key.chr.entry[i].x + dx) / 1000 + hx;
		if (c != rx) {
			if (c < 0) /* ILLEGAL */
				return 1;
			ti = c / key.map.map->layer[l].tile_w;
			if (ti != rx / key.map.map->layer[l].tile_w) {
				ti += (ry / key.map.map->layer[l].tile_h) * key.map.map->layer[l].tilemap->w;
				if (key.map.map->layer[l].tilemap->data[ti] & MAP_COLLIDE_LEFT)		/* Collision! */
					col = 1;
				else if ((ry + hh) / key.map.map->layer[l].tile_h != ry / key.map.map->layer[l].tile_h && (key.map.map->layer[l].tilemap->data[ti + key.map.map->layer[l].tilemap->w] & MAP_COLLIDE_LEFT))	/* Collision! */
					col = 1;
				else
					key.chr.entry[i].x += dx;
			} else
				key.chr.entry[i].x += dx;
		} else
			key.chr.entry[i].x += dx;
	} else if (dx > 0) {
		rx -= hw;
		c = (key.chr.entry[i].x + dx) / 1000 + hx + hw;
		if (c != rx) {
			if (c / key.map.map->layer[l].tile_w >= key.map.map->layer[l].tilemap->w) /* ILLEGAL */
				return 1;
			ti = c / key.map.map->layer[l].tile_w;
			if (ti != rx / key.map.map->layer[l].tile_w) {
				ti += (ry / key.map.map->layer[l].tile_h) * key.map.map->layer[l].tilemap->w;
				if (key.map.map->layer[l].tilemap->data[ti] & MAP_COLLIDE_RIGHT)	/* Collision! */
					col = 1;
				else if ((ry + hh) / key.map.map->layer[l].tile_h != ry / key.map.map->layer[l].tile_h && (key.map.map->layer[l].tilemap->data[ti + key.map.map->layer[l].tilemap->w] & MAP_COLLIDE_LEFT))	/* Collision! */
					col = 1;
				else
					key.chr.entry[i].x += dx;
			} else
				key.chr.entry[i].x += dx;
		} else
			key.chr.entry[i].x += dx;
	}

	/* Y-axis */
	rx = key.chr.entry[i].x / 1000 + hx;
	ry = key.chr.entry[i].y / 1000 + hy;
	if (dy < 0) {
		c = (key.chr.entry[i].y + dy) / 1000 + hy;
		if (c != ry) {
			if (c < 0) /* ILLEGAL */
				return 1;
			ti = c / key.map.map->layer[l].tile_h;
			if (ti != ry / key.map.map->layer[l].tile_h) {
				ti *= key.map.map->layer[l].tilemap->w;
				ti += (rx / key.map.map->layer[l].tile_w);
				if (key.map.map->layer[l].tilemap->data[ti] & MAP_COLLIDE_UP)	/* Collision! */
					col = 1;
				else if ((rx + hw) / key.map.map->layer[l].tile_w != rx / key.map.map->layer[l].tile_w && (key.map.map->layer[l].tilemap->data[ti + 1] & MAP_COLLIDE_UP))	/* Collision! */
					col = 1;
				else
					key.chr.entry[i].y += dy;
			} else
				key.chr.entry[i].y += dy;
		} else
			key.chr.entry[i].y += dy;
	} else if (dy > 0) {
		ry += hh;
		c = (key.chr.entry[i].y + dy) / 1000 + hy + hh;
		if (c != ry) {
			if (c / key.map.map->layer[l].tile_h >= key.map.map->layer[l].tilemap->h) /* ILLEGAL */
				return 1;
			ti = c / key.map.map->layer[l].tile_h;
			if (ti != ry / key.map.map->layer[l].tile_h) {
				ti *= key.map.map->layer[l].tilemap->w;
				ti += rx / key.map.map->layer[l].tile_w;
				if (key.map.map->layer[l].tilemap->data[ti] & MAP_COLLIDE_DOWN)		/* Collision! */
					col = 1;
				else if ((rx + hw) / key.map.map->layer[l].tile_w != rx / key.map.map->layer[l].tile_w && (key.map.map->layer[l].tilemap->data[ti + 1] & MAP_COLLIDE_DOWN))	/* Collision! */
					col = 1;
				else
					key.chr.entry[i].y += dy;
			} else
				key.chr.entry[i].y += dy;
		} else
			key.chr.entry[i].y += dy;
	}

	return col;
}


void character_loop() {
	int i, d, dx, dy;

	for (i = 0; i < key.chr.entries; i++) {
		if (!key.chr.entry[i].handler)
			continue;
		/* Handle gravity */
		key.chr.entry[i].y_vel += (CHARACTER_GRAVITY * d_last_frame_time());
		if (key.chr.entry[i].y_vel > CHARACTER_TERMINAL_VELOCITY)
			key.chr.entry[i].y_vel = CHARACTER_TERMINAL_VELOCITY;
		key.chr.entry[i].y_rest += key.chr.entry[i].y_vel * d_last_frame_time() / 1000;

		/* Handle X-axis */
		key.chr.entry[i].x_rest += key.chr.entry[i].x_vel * d_last_frame_time();

		/* step through every moved piczel */
		while (abs(key.chr.entry[i].y_rest) + abs(key.chr.entry[i].x_rest) > 1000) {
			if (!key.chr.entry[i].y_rest) {			/* Only X-axis */
				if (key.chr.entry[i].x_rest < 0)
					d = (key.chr.entry[i].x_rest <= -1000) ? -1000 : key.chr.entry[i].x_rest;
				else
					d = (key.chr.entry[i].x_rest >= 1000) ? 1000 : key.chr.entry[i].x_rest;
				character_move(i, d, 0);
				key.chr.entry[i].x_rest -= d;
			} else if (!key.chr.entry[i].x_rest) {		/* Only Y-axis */
				if (key.chr.entry[i].y_rest < 0)
					d = (key.chr.entry[i].y_rest <= -1000) ? -1000 : key.chr.entry[i].y_rest;
				else
					d = (key.chr.entry[i].y_rest >= 1000) ? 1000 : key.chr.entry[i].y_rest;
				if (character_move(i, 0, d))
					key.chr.entry[i].y_vel = 0;
				key.chr.entry[i].y_rest -= d;
			} else {					/* Both X and Y */
				/* I should use trigonometry, but I don't have any integer inverse trig functions available */
				dx = key.chr.entry[i].x_rest * 1000 / (abs(key.chr.entry[i].x_rest) + abs(key.chr.entry[i].y_rest));
				dy = key.chr.entry[i].y_rest * 1000 / (abs(key.chr.entry[i].x_rest) + abs(key.chr.entry[i].y_rest));
				if (character_move(i, dx, dy)) 
					key.chr.entry[i].x_vel = key.chr.entry[i].y_vel = 0;
				key.chr.entry[i].x_rest -= dx;
				key.chr.entry[i].y_rest -= dy;
			}
		}

		d_sprite_move(key.chr.entry[i].sprite, key.chr.entry[i].x / 1000, key.chr.entry[i].y / 1000);
		key.chr.entry[i].handler(i);
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
