#include "draw.h"
short int button_create(struct spos butpos, char **sarr /* Array of C strings */,
	size_t arrlen, short int w, short int h)
{
	w += 2;
	h += 1;

	struct spos orig_cpos = _gls->cpos;
	short int id;
	struct button cbut;
	char tmp[4];

	id = ++_gls->but_idmax;
	if (id > MAX_BUTTONS) return -1; /* Error! */

	for (int i = 1; i <= h; i++) {
		curs_mov(MKSPOS(butpos.r + i, butpos.c));
		buf_putstr("|");
		curs_mov(MKSPOS(butpos.r + i, butpos.c + w - 1));
		buf_putstr("|");
	}

	curs_mov(butpos);
	for (int i = 0; i < w; i++)
		buf_putstr("-");
	curs_mov(MKSPOS(butpos.r + h, butpos.c));
	for (int i = 0; i < w; i++)
		buf_putstr("-");

	for (int i = 0; i < arrlen && i < h; i++) {
		curs_mov(MKSPOS(butpos.r + i + 1, butpos.c + 1));
		buf_putstr(sarr[i]);
	}

	/* Put button id there */
	curs_mov(butpos);
	sprintf(tmp, "%d", id);
	buf_putstr(tmp);

	cbut.id = id;
	cbut.action = NULL;

	__vector_pushback(_gls->buttons, &cbut);
	curs_mov(orig_cpos);
	return id;
}

void button_bind(short int id, void_fnptr action)
{
	vector_getptr(_gls->buttons, id - 1, struct button)->action = action;
	return;
}

void button_call(short int id)
{
	vector_get(_gls->buttons, id - 1, struct button).action();
	return;
}
