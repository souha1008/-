#pragma once

#define SE_01	1
#define SE_02	2
#define SE_03	3

typedef struct {
	const char* fname;
	int	sound_id;
}sound_t;

enum sound_m {
	SOUND_KETTEI,
	SOUND_TITLEBGM,
	SOUND_BGM01,
	//ÉäÉUÉãÉgSE
	RESULT_SSS,
	RESULT_SS_S,
	RESULT_AB,
	RESULT_CD,
	RESULT_EF,
	//ÉQÅ[ÉÄSE
	SE_1,
	SE_2,
	SE_3,
	SE_4,
	SE_5,
	SE_6,
	SE_7,
	SE_8,
	SE_9,
	SE_10,
	SE_11,
	SE_12,
	SE_13,
	SE_14
};

void SoundInit(void);
void SoundEnd(void);
void SoundPlayOnce(int sound);
void SoundPlayRepeet(int sound);
void SoundStop(int sound);
void parSEplay(float PAR);
void g_parSEplay(float G_PAR);

