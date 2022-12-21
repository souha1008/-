#include "CHAR.h"

void Waku_View()
{
	setcursortype(NOCURSOR);
	for (int i = 0; waku[i] != NULL; i++)
	{
		printf("%s\n", waku[i]);
	}
}