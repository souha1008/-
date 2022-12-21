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
	//�H���J�߂�SE
	{"Assets/Audio/SE/��������Ȃ����I.mp3", 0},	//SE_1
	{"Assets/Audio/SE/���ȁI.mp3", 0},			//SE_2
	{"Assets/Audio/SE/���̒��q���I.mp3", 0},		//SE_3
	//�����J�߂�SE
	{"Assets/Audio/SE/���q��������ł邼.mp3", 0},	//SE_4
	{"Assets/Audio/SE/�ǂ��o���h�����I.mp3", 0},		//SE_5
	//�H���܂��܂�SE
	{"Assets/Audio/SE/�y��_����.mp3", 0},			//SE_6
	{"Assets/Audio/SE/�܂��܂�����.mp3", 0},		//SE_7
	//�����܂��܂�SE
	{"Assets/Audio/SE/�܂��ǂ��Ƃ��悤.mp3", 0},	//SE_8
	{"Assets/Audio/SE/�Ȃ��Ȃ��̏o������.mp3", 0},	//SE_9
	//�H���_��SE
	{"Assets/Audio/SE/�܂��܂�����.mp3", 0},		//SE_10
	{"Assets/Audio/SE/��������.mp3", 0},			//SE_11
	{"Assets/Audio/SE/�ł�񂶂�Ȃ�.mp3", 0},		//SE_12
	//�����_��SE
	{"Assets/Audio/SE/�����Ɍ��������������Ă���.mp3", 0},	//SE_13
	{"Assets/Audio/SE/���q����ɂ�����o���̂�.mp3", 0},	//SE_14
	{ NULL,0},
};


// �T�E���h�e�[�u���̏�������(�܂Ƃ߂ăI�[�v��)
void SoundInit(void)
{
	for (int i = 0; MenuSound[i].fname != NULL; i++) {
		if (MenuSound[i].sound_id == 0) {
			MenuSound[i].sound_id = opensound((char*)MenuSound[i].fname);
			if (MenuSound[i].sound_id == 0) {
				gotoxy(1, 1), clreol(), printf("%s�̃I�[�v�����s", MenuSound[i].fname);
				while (!(reinport(), inport(PK_ENTER)));	// ENTER�L�[���͑҂�
			}
		}
	}
}
// �T�E���h�e�[�u���̏I������(�܂Ƃ߂ăN���[�Y)
void SoundEnd(void)
{
	for (int i = 0; MenuSound[i].fname != NULL; i++) {
		if (MenuSound[i].sound_id != 0) {
			closesound(MenuSound[i].sound_id);
		}
	}
}
// �T�E���h��炷�i�P�񂾂��Đ��j
void SoundPlayOnce(int sound)
{
	if (MenuSound[sound].sound_id != 0) {
		playsound(MenuSound[sound].sound_id, 0);
	}
}
// �T�E���h��炷�i���[�v�Đ��j
void SoundPlayRepeet(int sound)
{
	if (MenuSound[sound].sound_id != 0) {
		playsound(MenuSound[sound].sound_id, 1);
	}
}
// �T�E���h���~�߂�
void SoundStop(int sound)
{
	if (MenuSound[sound].sound_id != 0) {
		stopsound(MenuSound[sound].sound_id);
	}
}

//par�̒l�ɂ���Ė炷SE��ς���
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


