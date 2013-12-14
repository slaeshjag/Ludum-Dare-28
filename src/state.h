#ifndef __STATE_H__
#define	__STATE_H__

enum THEKEY_STATE {
	THEKEY_STATE_DUMMY,
	THEKEY_STATE_MAINMENU,
	THEKEY_STATE_INGAME,
};


struct state {
	enum THEKEY_STATE		cur_state;
	enum THEKEY_STATE		new_state;
};


void state_init();

#endif
