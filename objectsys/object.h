#ifndef INC_BASE
#include "../base.h"
#endif
short int object_create(char rep, struct spos pos);
void object_del(short int id);
void object_mov(short int id, struct spos newpos);