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

	key.chr.entry[i].sprite = d_sprite_free(key.chr.entry[i].sprite);
	key.chr.used--;
}


void character_add(void *handler, int x, int y, const char *fname) {
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
	key.chr.entry[k].x_rest = 0;
	key.chr.entry[k].y_rest = 0;
	key.chr.entry[k].x_vel = 0;
	key.chr.entry[k].y_vel = 0;
	key.chr.entry[k].sprite = d_sprite_load(fname, 0, DARNIT_PFORMAT_RGB5A1);
	
	return;
}


void character_loop() {
	int i;

	for (i = 0; i < key.chr.entries; i++) {
		if (!key.chr.entry[i].handler)
			continue;
		/* TODO: Do stuff */
	}

	return;
}


void character_draw() {
	int i;
	
	for (i = 0; i < key.chr.entries; i++) {
		if (!key.chr.entry[i].handler)
			continue;
		d_sprite_draw(key.chr.entry[i].sprite);
	}

	return;
}
