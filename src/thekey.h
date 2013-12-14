#ifndef __THEKEY_H__
#define	__THEKEY_H__


#include <darnit/darnit.h>
#include "ai.h"
#include "character.h"
#include "particle.h"
#include "map.h"
#include "state.h"


struct thekey {
	struct character		chr;
	struct particle			p;
	struct map			map;
	struct state			state;

	DARNIT_PLATFORM			platform;
};

struct thekey key;


#endif
