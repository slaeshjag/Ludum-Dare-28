#ifndef __CHARACTER_H__
#define	__CHARACTER_H__


#define	CHARACTER_TERMINAL_VELOCITY	500000		/* 200 piczel / second */
#define	CHARACTER_GRAVITY		500		/* 100 piczel / second^2 */


struct character_entry {
	int			x;
	int			y;
	int			l;

	int			dir;

	int			x_rest;
	int			y_rest;

	int			x_vel;
	int			y_vel;

	void			(*handler)(int id, enum AI_MSG msg);

	DARNIT_SPRITE		*sprite;
};


struct character {
	struct character_entry	*entry;
	int			entries;
	int			used;
};

void character_init();
void character_delete(int i);
int character_add(void *handler, int x, int y, int l, const char *fname);
void character_loop();
void character_draw(int layer);


#endif
