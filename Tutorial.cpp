#include "Tutorial.h"
#include "CHAR.h"
#include "SOUND.h"

void Tutorial_view()
{
	Waku_View();

	gotoxy(4, 3);
	textbackground(LIGHTGRAY);
	textcolor(MAGENTA);
	printf("☆☆☆");
	textcolor(BLACK);
	printf("チュートリアル");
	textcolor(MAGENTA);
	printf("☆☆☆");
	normvideo();
	GotoxyPrintf(5, 5, "あなたはとあるビーチにある、超人気でご飯が美味い海の家「タイプシーサイドリゾート」にアルバイトをしに来ました。");
	GotoxyPrintf(5, 6, "ですが・・・ここの海の家は少し特殊。");
	textbackground(LIGHTGRAY);
	textcolor(RED);
	printf("タイピング");
	normvideo();
	printf("で料理を作るお店でした。");
	GotoxyPrintf(5, 7, "各工程を間違えないようにタイピングして、６０秒間で１００％の料理をたくさん作りましょう！");

	gotoxy(4, 10);
	textbackground(LIGHTGRAY);
	textcolor(YELLOW);
	printf("☆☆☆");
	textcolor(BLACK);
	printf("操作方法");
	textcolor(YELLOW);
	printf("☆☆☆");
	normvideo();
	GotoxyPrintf(5, 12, "表示されている文字「A～Zキー」で打ったら「エンターキー」を押す！！");

	gotoxy(4, 15);
	textbackground(LIGHTGRAY);
	textcolor(GREEN);
	printf("☆☆☆");
	textcolor(BLACK);
	printf("画面の見方");
	textcolor(GREEN);
	printf("☆☆☆");
	normvideo();

	//タイマーについて
	GotoxyPrintf(4, 17, "・タイマーの見方");

	//グリーン表示
	textcolor(GREEN);
	GotoxyPrintf(6, 19, "■■■");
	GotoxyPrintf(6, 20, "■　■");
	GotoxyPrintf(6, 21, "■■■");

	//オレンジ表示
	textcolor(BROWN);
	GotoxyPrintf(14, 19, "■■■");
	GotoxyPrintf(14, 20, "■　■");
	GotoxyPrintf(14, 21, "■■■");

	//レッド表示
	textcolor(RED);
	GotoxyPrintf(22, 19, "■■■");
	GotoxyPrintf(22, 20, "■　■");
	GotoxyPrintf(22, 21, "■■■");

	normvideo();
	GotoxyPrintf(5, 23, "経過時間で枠の色が変わります。残り時間の目安にしてください。***残り10秒で赤色の枠に変わります***");

	//スコア表示について
	GotoxyPrintf(4, 25, "・スコア表示");
	GotoxyPrintf(4, 26, "枠内右上に現在のスコアを表示しています。");

	GotoxyPrintf(4, 28, "・各工程の達成度");
	GotoxyPrintf(4, 29, "枠内左側に料理の達成した工程を表示しています。達成度はパーセントで表示されています。");

	//作る料理
	GotoxyPrintf(4, 31, "・作る料理と現在の工程");
	GotoxyPrintf(4, 32, "作る料理は枠内上部に文字が表示されています。また、現在の工程は枠内中央に絵が表示され枠内下部に文字が表示されます。");

	gotoxy(60, 44);
	textbackground(LIGHTGRAY);
	textcolor(BLACK);
	printf("スペース押してスタート\n");
	normvideo();

	while (!inport(PK_SP))
	{
		;
	}
	reinport();
	SoundStop(SOUND_TITLEBGM);
	SoundPlayOnce(SOUND_KETTEI);
	msleep(2000);
	clrscr();
}