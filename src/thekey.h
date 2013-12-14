#ifndef __THEKEY_H__
#define	__THEKEY_H__


#include <darnit/darnit.h>
#include "character.h"
#include "ai.h"
#include "particle.h"


struct thekey {
	struct character		chr;
	struct particle			p;
};

struct thekey key;


#endif
