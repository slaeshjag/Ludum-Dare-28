#ifndef __PARTICLE_H__
#define	__PARTICLE_H__

struct particle_entry {
	DARNIT_PARTICLE			*p;
	int				x;
	int				y;
};


struct particle {
	struct particle_entry		*p;
	int				particles;
	int				used;
};


void particle_init();
void particle_new_pulse(DARNIT_PARTICLE *p, int x, int y);
void particle_loop();
void particle_destroy_all();


#endif
