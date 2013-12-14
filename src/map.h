#ifndef __MAP_H__
#define	__MAP_H__

#define	MAP_COLLIDE_UP		0x10000
#define	MAP_COLLIDE_RIGHT	0x20000
#define	MAP_COLLIDE_DOWN	0x40000
#define	MAP_COLLIDE_LEFT	0x80000


struct map {
	int			camera_x;
	int			camera_y;
	int			character_follow;

	DARNIT_MAP		*map;
};

void map_init();
void map_load(const char *fname);
void map_draw();


#endif
