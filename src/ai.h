#ifndef __AI_H__
#define	__AI_H__

enum AI_MSG {
	AI_MSG_INIT,
	AI_MSG_LOOP,
	AI_MSG_DESTROY,
};


void *ai_lookup(const char *str);


#endif
