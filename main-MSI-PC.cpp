#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include "MYconioex.h"

#define EN_CHAR 24

const int pk_tbl[]
{
	PK_A,
	PK_B,
	PK_C,
	PK_D,
	PK_E,
	PK_F,
	PK_G,
	PK_H,
	PK_I,
	PK_J,
	PK_K,
	PK_L,
	PK_M,
	PK_N,
	PK_O,
	PK_P,
	PK_Q,
	PK_R,
	PK_S,
	PK_T,
	PK_U,
	PK_V,
	PK_W,
	PK_X,
	PK_Y,
	PK_Z,
};

static const char* menu1[]
{
	"yakisoba",
	NULL
};

int main(void)
{
	char type[30];
	char answard[30];
	int anslen;
	int score = 0;
	int a = 0;
	float par = 0.0f;
	int moji = 0;
	bool max = false;

	for (int i = 0; menu1[i] != NULL; i++)
	{
		score = 0;
		anslen = strlen(menu1[i]);
		strcpy(answard, menu1[i]);
		printf("%s\n>>", answard);
		while (!inport(PK_ENTER) || !max)
		{
			for (; moji < EN_CHAR; moji++)
			{
				if (inport(pk_tbl[moji]))
				{
					reinport();
					type[a] = pk_tbl[moji];
					a++;
					if (a > 30)
					{
						max = true;
					}
					break;
				}
				else
				{
					;
				}
			}
			moji = 0;
		}
	}

	printf("%s", type);

	rewind(stdin);
	getchar();
	return 0;
}