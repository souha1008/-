#pragma once
#define CONIOEX
#include "MYconioex.h"

//スコアランクマクロ
#define SSS 100000
#define SS	90000
#define S	85000
#define A	75000
#define B	60000
#define C	45000
#define D	30000
#define E	20000

#define SSS_word	1
#define S_SS_word	2
#define A_B_word	3
#define C_D_word	4
#define E_F_word	5


void Result(HANDLE hthraed);

static const char* Result_word[]
{
	"",
	"店主からのおことば「おいおい、俺よりすごいんじゃないか？今日は給料を倍にしてやるよ！次もよろしくな！」",
	"店主からのおことば「もう一人前だな！今日の売上はお前さんのおかげだ！ありがとな！」",
	"店主からのおことば「まあこれぐらいはやってもらわないとな。次回もよろしく！」",
	"店主からのおことば「おいおい、もう少し頑張って欲しかったな。」",
	"店主からのおことば「まさか、この結果に給料を払えと言わないよな？」"
};