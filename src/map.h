#ifndef __MAP_H__
#define	__MAP_H__


struct map {
	int			camera_x;
	int			camera_y;

	DARNIT_MAP		*map;
};

void map_init();


#endif
