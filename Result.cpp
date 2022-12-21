#include "Result.h"
#include "CHAR.h"
#include "SOUND.h"

//�v���C���[�X�R�A
int player_score = 0;

void Result(HANDLE hthraed)
{
	SoundStop(SOUND_BGM01);
	clrscr();
	Waku_View();

	GotoxyPrintf(60, 6, "�ŏI�X�R�A�F%d", player_score);
	//�X�R�A�����N�\��
	if (player_score >= SSS)
	{
		GotoxyPrintf(60, 8, "�X�R�A�����N�FSSS");
		GotoxyPrintf(30, 10, "%s", Result_word[SSS_word]);
		SoundPlayOnce(RESULT_SSS);
	}
	else if (player_score >= SS)
	{
		GotoxyPrintf(60, 8, "�X�R�A�����N�FSS");
		GotoxyPrintf(30, 10, "%s", Result_word[S_SS_word]);
		SoundPlayOnce(RESULT_SS_S);
	}
	else if (player_score >= S)
	{
		GotoxyPrintf(60, 8, "�X�R�A�����N�FS");
		GotoxyPrintf(30, 10, "%s", Result_word[S_SS_word]);
	}
	else if (player_score >= A)
	{
		GotoxyPrintf(60, 8, "�X�R�A�����N�FA");
		GotoxyPrintf(30, 10, "%s", Result_word[A_B_word]);
		SoundPlayOnce(RESULT_AB);
	}
	else if (player_score >= B)
	{
		GotoxyPrintf(60, 8, "�X�R�A�����N�FB");
		GotoxyPrintf(30, 10, "%s", Result_word[A_B_word]);
		SoundPlayOnce(RESULT_AB);
	}
	else if (player_score >= C)
	{
		GotoxyPrintf(60, 8, "�X�R�A�����N�FC");
		GotoxyPrintf(30, 10, "%s", Result_word[C_D_word]);
		SoundPlayOnce(RESULT_CD);
	}
	else if (player_score >= D)
	{
		GotoxyPrintf(60, 8, "�X�R�A�����N�FD");
		GotoxyPrintf(30, 10, "%s", Result_word[C_D_word]);
		SoundPlayOnce(RESULT_CD);
	}
	else if (player_score >= E)
	{
		GotoxyPrintf(60, 8, "�X�R�A�����N�FE");
		GotoxyPrintf(30, 10, "%s", Result_word[E_F_word]);
		SoundPlayOnce(RESULT_EF);
	}
	else
	{
		GotoxyPrintf(60, 8, "�X�R�A�����N�FF");
		GotoxyPrintf(30, 10, "%s", Result_word[E_F_word]);
		SoundPlayOnce(RESULT_EF);
	}
	
	msleep(5000);
	while (!inport(PK_SP));
	reinport();
	if (hthraed != NULL) {
		CloseHandle(hthraed);	// CloseHandle��hThread�����.
	}
	clrscr();
}