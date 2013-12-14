#ifndef __CHARACTER_H__
#define	__CHARACTER_H__


struct character_entry {
	int			x;
	int			y;

	int			x_rest;
	int			y_rest;

	int			x_vel;
	int			y_vel;

	void			(*handler)();

	DARNIT_SPRITE		*sprite;
};


struct character {
	struct character_entry	*entry;
	int			entries;
	int			used;
};

void character_init();
void character_delete(int i);
void character_add(void *handler, int x, int y, const char *fname);


#endif
