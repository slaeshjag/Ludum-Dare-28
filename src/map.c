#include "thekey.h"


void map_init() {
	key.map.map = NULL;
	key.map.camera_x = key.map.camera_y = 0;
	key.map.character_follow = -1;

	return;
}


void map_load(const char *fname) {
	int i, x, y;
	DARNIT_MAP_OBJECT *obj;

	if (!fname)
		return;
	if (key.map.map)
		key.map.map = d_map_unload(key.map.map);
	key.map.map = d_map_load(fname);

	for (i = 0; i < key.map.map->objects; i++) {
		obj = &key.map.map->object[i];
		x = obj->x * key.map.map->layer[obj->l].tile_w;
		y = obj->y * key.map.map->layer[obj->l].tile_h;
		character_add(ai_lookup(d_map_prop(obj->ref, "handler")), x, y, obj->l, d_map_prop(obj->ref, "sprite"));
	}

	return;
}


void map_draw() {
	int i;

	if (!key.map.map)
		return;

	if (key.map.character_follow >= 0) {
		key.map.camera_x = (key.chr.entry[key.map.character_follow].x / 1000 - key.platform.screen_w / 2);
		key.map.camera_y = (key.chr.entry[key.map.character_follow].y / 1000 - key.platform.screen_h / 2);
	}


	for (i = 0; i < key.map.map->layers; i++) {
		d_tilemap_draw(key.map.map->layer[i].tilemap);
		character_draw(i);
	}

	return;
}

