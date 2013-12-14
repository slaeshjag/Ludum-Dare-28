/* No fancy message system. Nobody aint got time for that! */
#include "thekey.h"
#include <string.h>


void ai_dummy() {
	return;
}


void *ai_lookup(const char *str) {
	if (!strcmp(str, "dummy")) return ai_dummy;

	fprintf(stderr, "Unimplemented AI %s\n", str);
	return ai_dummy;
}
