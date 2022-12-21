#include "Title.h"
#include "CHAR.h"
#include "SOUND.h"
#include "BMP.h"

bool t = false;
int n = 1;

static const char* Title_BMP[]
{
	"Assets/img/Title_0.bmp",
	"Assets/img/Title_1.bmp",
	"Assets/img/Title_2.bmp",
	"Assets/img/Title_3.bmp",
	NULL
};

void Title_view()
{
	SoundPlayRepeet(SOUND_TITLEBGM);
	Waku_View();

	while (!inport(PK_SP))
	{
		Title_Animation1();
		msleep(200);

		Title_Animation2();
		msleep(200);
	}
	reinport();
	SoundPlayOnce(SOUND_KETTEI);
	msleep(2000);
	n = 1;
	normvideo();
	clrscr();
}

void Title_pl(int no)
{
	Bmp_view(Title_BMP[no], 1, 1);
	gotoxy(60, 44);
	textbackground(LIGHTGRAY);
	textcolor(BLACK);
	printf("スペース押してスタート");
}

void Title_Animation1()
{
	if (n < 4 && !t)
	{
		Title_pl(n);
		n++;
		if (n >= 4)
		{
			t = true;
			n -= 2;
		}
	}
}

void Title_Animation2()
{
	if (n > 0 && t)
	{
		Title_pl(n);
		n--;
		if (n <= 0)
		{
			t = false;
		}
	}
}