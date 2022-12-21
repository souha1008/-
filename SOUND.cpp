#define CONIOEX
#include "MYconioex.h"
#include "SOUND.h"
#include <time.h>

static sound_t MenuSound[] = {
	{"Assets/Audio/SE/kettei.mp3", 0},
	{"Assets/Audio/BGM/TitleBGM.mp3", 0},
	{"Assets/Audio/BGM/GameBGM01ver3.mp3", 0},
	{"Assets/Audio/BGM/ResultBGM_SSS.mp3", 0},
	{"Assets/Audio/BGM/ResultBGM_SS_S.mp3", 0},
	{"Assets/Audio/BGM/ResultBGM_AB.mp3", 0},
	{"Assets/Audio/BGM/ResultBGM_CD.mp3", 0},
	{"Assets/Audio/BGM/ResultBGM_EF.mp3", 0},
	//工程褒めるSE
	{"Assets/Audio/SE/いいじゃないか！.mp3", 0},	//SE_1
	{"Assets/Audio/SE/やるな！.mp3", 0},			//SE_2
	{"Assets/Audio/SE/その調子だ！.mp3", 0},		//SE_3
	//完成褒めるSE
	{"Assets/Audio/SE/お客さんも喜んでるぞ.mp3", 0},	//SE_4
	{"Assets/Audio/SE/良い出来栄えだ！.mp3", 0},		//SE_5
	//工程まあまあSE
	{"Assets/Audio/SE/及第点だな.mp3", 0},			//SE_6
	{"Assets/Audio/SE/まあまあだな.mp3", 0},		//SE_7
	//完成まあまあSE
	{"Assets/Audio/SE/まあ良しとしよう.mp3", 0},	//SE_8
	{"Assets/Audio/SE/なかなかの出来だな.mp3", 0},	//SE_9
	//工程ダメSE
	{"Assets/Audio/SE/まだまだだな.mp3", 0},		//SE_10
	{"Assets/Audio/SE/おいおい.mp3", 0},			//SE_11
	{"Assets/Audio/SE/焦るんじゃない.mp3", 0},		//SE_12
	//完成ダメSE
	{"Assets/Audio/SE/給料に見合う働きをしてくれ.mp3", 0},	//SE_13
	{"Assets/Audio/SE/お客さんにそれを出すのか.mp3", 0},	//SE_14
	{ NULL,0},
};


// サウンドテーブルの初期処理(まとめてオープン)
void SoundInit(void)
{
	for (int i = 0; MenuSound[i].fname != NULL; i++) {
		if (MenuSound[i].sound_id == 0) {
			MenuSound[i].sound_id = opensound((char*)MenuSound[i].fname);
			if (MenuSound[i].sound_id == 0) {
				gotoxy(1, 1), clreol(), printf("%sのオープン失敗", MenuSound[i].fname);
				while (!(reinport(), inport(PK_ENTER)));	// ENTERキー入力待ち
			}
		}
	}
}
// サウンドテーブルの終了処理(まとめてクローズ)
void SoundEnd(void)
{
	for (int i = 0; MenuSound[i].fname != NULL; i++) {
		if (MenuSound[i].sound_id != 0) {
			closesound(MenuSound[i].sound_id);
		}
	}
}
// サウンドを鳴らす（１回だけ再生）
void SoundPlayOnce(int sound)
{
	if (MenuSound[sound].sound_id != 0) {
		playsound(MenuSound[sound].sound_id, 0);
	}
}
// サウンドを鳴らす（ループ再生）
void SoundPlayRepeet(int sound)
{
	if (MenuSound[sound].sound_id != 0) {
		playsound(MenuSound[sound].sound_id, 1);
	}
}
// サウンドを止める
void SoundStop(int sound)
{
	if (MenuSound[sound].sound_id != 0) {
		stopsound(MenuSound[sound].sound_id);
	}
}

//parの値によって鳴らすSEを変える
void parSEplay(float PAR)
{
	int soundrand = 0;
	if (PAR >= 80.0)
	{
		srand((unsigned int)time(NULL));
		soundrand = rand() % 3 + 1;
		switch (soundrand)
		{
		case SE_01:
			SoundPlayOnce(SE_1);
			break;
		case SE_02:
			SoundPlayOnce(SE_2);
			break;
		case SE_03:
			SoundPlayOnce(SE_3);
			break;
		}
	}
	else if (PAR >= 50.0)
	{
		srand((unsigned int)time(NULL));
		soundrand = rand() % 2 + 1;
		switch (soundrand)
		{
		case SE_01:
			SoundPlayOnce(SE_6);
			break;
		case SE_02:
			SoundPlayOnce(SE_7);
			break;
		}
	}
	else if (PAR >= 0.0)
	{
		srand((unsigned int)time(NULL));
		soundrand = rand() % 3 + 1;
		switch (soundrand)
		{
		case SE_01:
			SoundPlayOnce(SE_10);
			break;
		case SE_02:
			SoundPlayOnce(SE_11);
			break;
		case SE_03:
			SoundPlayOnce(SE_12);
			break;
		}
	}
}

void g_parSEplay(float G_PAR)
{
	int soundrand = 0;
	if (G_PAR >= 80.0)
	{
		srand((unsigned int)time(NULL));
		soundrand = rand() % 2 + 1;
		switch (soundrand)
		{
		case SE_01:
			SoundPlayOnce(SE_4);
			break;
		case SE_02:
			SoundPlayOnce(SE_5);
			break;
		}
	}
	else if (G_PAR >= 50.0)
	{
		srand((unsigned int)time(NULL));
		soundrand = rand() % 2 + 1;
		switch (soundrand)
		{
		case SE_01:
			SoundPlayOnce(SE_8);
			break;
		case SE_02:
			SoundPlayOnce(SE_9);
			break;
		}
	}
	else if (G_PAR >= 0.0)
	{
		srand((unsigned int)time(NULL));
		soundrand = rand() % 3 + 1;
		switch (soundrand)
		{
		case SE_01:
			SoundPlayOnce(SE_13);
			break;
		case SE_02:
			SoundPlayOnce(SE_14);
			break;
		}
	}
}


