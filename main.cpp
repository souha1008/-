///////////////////////////////////////////
//				ゲーム概要				 //
///////////////////////////////////////////

//これはタイピングゲームです。60秒間で、ランダムにでてくる料理の工程と材料をタイピングして料理を作り、高いスコアを出すゲームです。。
//リゾート→海→海の家　という形で連想し、海の家で食べれそうな料理を用意します。
//このタイピングゲームには「正確度」が実装されており、打った文字列と正解の文字列を比較し、正確に打てているかがパーセンテージで可視化されます。
//各工程の「正確度」によって料理の質が決まり、スコアが上下します。

//スコア計算	各工程(パーセント（小数点切り捨て）×１０)　＋　料理の出来(パーセント（小数点切り捨て）×１００)　＝　プレイヤースコア

#define _CRT_SECURE_NO_WARNINGS
#include <string.h>
#include <time.h>
#include "MYconioex.h"
#include "Title.h"
#include "Tutorial.h"
#include "CHAR.h"
#include "Result.h"
#include "SOUND.h"
#include "BMP.h"

//-------------------------------------------------------------------
// マクロ設定
//-------------------------------------------------------------------
#define MENU_01		1
#define MENU_02		2
#define MENU_03		3
#define MENU_04		4
#define MENU_05		5
#define MENU_06		6
#define MENU_07		7
#define MENU_08		8
#define MENU_09		9

//タイマー表示時間
#define TIME_GREEN	30000
#define TIME_ORANGE 11000
#define TIME_RED	0

//キーの数
#define EN_CHAR		26

//BMP画像左上の位置
#define BMP_POSX	45
#define BMP_POSY	8

//入力するキーのテーブル
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

static const char* count3_bmp[]
{
	"Assets/img/3_1.bmp",
	"Assets/img/3_2.bmp",
	"Assets/img/3_3.bmp",
	"Assets/img/3_4.bmp"
};

static const char* count2_bmp[]
{
	"Assets/img/2_1.bmp",
	"Assets/img/2_2.bmp",
	"Assets/img/2_3.bmp",
	"Assets/img/2_4.bmp"
};

static const char* count1_bmp[]
{
	"Assets/img/1_1.bmp",
	"Assets/img/1_2.bmp",
	"Assets/img/1_3.bmp",
	"Assets/img/1_4.bmp"
};

//プレイヤースコア
extern int player_score;

//ランダム生成用
int rdm = 0;

//タイマー＆ゲーム終了フラグ
double REmaining;
bool end;

//プロトタイプ宣言
static DWORD WINAPI ThreadProc(LPVOID lpParameter);
void IsTime(HANDLE hthread, DWORD Result);
void PlayerScoreView();
void WindowCreate();
bool IsEnd(void);
void Refreshend(void);
void CountDown();
void GameInit();

int main(void)
{
	char type[30];
	int anslen;
	int score = 0;
	int a = 0;
	int g = 0;
	int i = 0;
	int moji = 0;
	float par[10] = {};
	float g_par = 0;
	bool typeend = false;
	bool typeenter = false;
	
	//ゲーム開始処理
	GameInit();

	while (1)
	{
		//タイマー用
		HANDLE hThread;			// スレッド生成するためのハンドル値
		DWORD dwThreadId;		// CreateThread(スレッド生成)関数の引数用

		DWORD	data = 60000; //10000で10秒
		DWORD	result = 0;

		//タイトル表示
		Title_view();

		//チュートリアル表示
		Tutorial_view();

		//カウントダウン開始
		CountDown();

		//タイマーセット
		hThread = CreateThread(NULL, 0, ThreadProc, &data, 0, &dwThreadId); 

		end = false;

		SoundPlayRepeet(SOUND_BGM01);
		while (!end)
		{
			srand((unsigned int)time(NULL));
			rdm = rand() % 5 + 1;	//ランダムに決める
			g_par = 0;
			//スイッチ文にて、表示されるメニューが違う
			switch (rdm)
			{
			case MENU_01:
				for (i = 0; menu1[i] != NULL; i++)
				{
					//初期化
					typeend = false;
					typeenter = false;
					score = 0;
					a = 0;

					//タイムチェック
					IsTime(hThread, result);
					//文字数格納
					anslen = strlen(menu1[i]);
					//画面更新
					clrscr();
					//画面枠表示
					WindowCreate();
					//UI表示
					PlayerScoreView();
					//画像表示　引数（bmpファイル名、ｘ位置、ｙ位置）
					Bmp_view(menu1_bmp[i], BMP_POSX, BMP_POSY);	
					gotoxy(60, 4);
					printf("%s", menu00[MENU_01]);
					gotoxy(62, 42);
					printf("%s", menu1_hira[i]);
					gotoxy(62, 43);
					printf("%s", menu1[i]);
					//スコア表示
					for (int g = 0; g < i; g++)
					{
						gotoxy(4, 25 + g);
						printf("%s : %.1f", menu1_hira[g], par[g]);
					}
					gotoxy(60, 45);
					printf(">>");
					//入力開始
					while (!typeend)
					{
						for (; moji < EN_CHAR; moji++)	//キーの数分繰り返し
						{
							//タイムチェック
							IsTime(hThread, result);
							if (!IsEnd())
							{
								if (inport(pk_tbl[moji]))
								{
									reinport();
									type[a] = tolower(pk_tbl[moji]);	//入力された際、大文字で入るため小文字化させて格納
									printf("%c", type[a]);
									a++;
									if (a > 30)	//３０文字制限
									{
										typeend = true;
									}
									break;
								}
								else if (inport(PK_ENTER))
								{
									reinport();
									typeend = true;
									typeenter = true;
									break;
								}
							}
							else
							{
								typeend = true;
								break;
							}
						}
						moji = 0;
					} 
					//工程のスコア計算
					if (typeenter)
					{
						for (int j = 0; j < a; j++)
						{
							if (type[j] == menu1[i][j])
							{
								score++;
							}
						}
						printf("\n");
						par[i] = ((float)score / (float)anslen) * 100;	//パーセンテージの計算
						parSEplay(par[i]);
						player_score += (int)par[i] * 10;	//スコア計算
					}
				}
				//合計パーセント計算
				if (typeenter)
				{
					for (g = 0; g < i; g++)
					{
						g_par += par[g];
					}
					g_par = ((float)g_par / (float)(i * 100)) * 100;
					player_score += (int)g_par * 100;	//ボーナススコア計算
					msleep(500); //ディレイ
					clrscr();
					WindowCreate();
					PlayerScoreView();
					g_parSEplay(g_par);
					Bmp_view(menu1_bmp[i], BMP_POSX, BMP_POSY);
					gotoxy(60, 4);
					printf("%s　：完成度　%.1f％", menu00[MENU_01], g_par);
					msleep(1400);
				}
				break;
				//以下同じ流れ

			case MENU_02:
				for (i = 0; menu2[i] != NULL; i++)
				{
					//初期化
					typeend = false;
					typeenter = false;
					score = 0;
					a = 0;

					IsTime(hThread, result);
					anslen = strlen(menu2[i]);
					clrscr();
					WindowCreate();
					PlayerScoreView();
					//画像表示　引数（bmpファイル名、ｘ位置、ｙ位置）
					Bmp_view(menu2_bmp[i], BMP_POSX, BMP_POSY);
					gotoxy(60, 4);
					printf("%s", menu00[MENU_02]);
					gotoxy(62, 42);
					printf("%s", menu2_hira[i]);
					gotoxy(62, 43);
					printf("%s\n", menu2[i]);
					for (int g = 0; g < i; g++)
					{
						gotoxy(4, 25 + g);
						printf("%s : %.1f", menu2_hira[g], par[g]);
					}
					gotoxy(60, 45);
					printf(">>");
					while (!typeend)
					{
						for (; moji < EN_CHAR; moji++)
						{
							IsTime(hThread, result);
							if (!IsEnd())
							{
								if (inport(pk_tbl[moji]))
								{
									reinport();
									type[a] = tolower(pk_tbl[moji]);
									printf("%c", type[a]);
									a++;
									if (a > 30)
									{
										typeend = true;
									}
									break;
								}
								else if (inport(PK_ENTER))
								{
									reinport();
									typeend = true;
									typeenter = true;
									break;
								}
							}
							else
							{
								typeend = true;
								break;
							}
						}
						moji = 0;
					}
					//工程のスコア計算
					if (typeenter)
					{
						for (int j = 0; j < a; j++)
						{
							if (type[j] == menu2[i][j])
							{
								score++;
							}
						}
						printf("\n");
						par[i] = ((float)score / (float)anslen) * 100;	//パーセンテージの計算
						parSEplay(par[i]);
						player_score += (int)par[i] * 10;	//スコア計算
					}
				}
				//合計パーセント計算
				if (typeenter)
				{
					for (g = 0; g < i; g++)
					{
						g_par += par[g];
					}
					g_par = ((float)g_par / (float)(i * 100)) * 100;
					player_score += (int)g_par * 100;	//ボーナススコア計算
					msleep(500); //ディレイ
					clrscr();
					WindowCreate();
					PlayerScoreView();
					Bmp_view(menu2_bmp[i], BMP_POSX, BMP_POSY);
					g_parSEplay(g_par);
					gotoxy(60, 4);
					printf("%s　：完成度　%.1f％", menu00[MENU_02], g_par);
					msleep(1400);
				}
				break;

			case MENU_03:
				for (i = 0; menu3[i] != NULL; i++)
				{
					//初期化
					typeend = false;
					score = 0;
					a = 0;

					IsTime(hThread, result);
					anslen = strlen(menu3[i]);
					clrscr();
					WindowCreate();
					PlayerScoreView();
					//画像表示　引数（bmpファイル名、ｘ位置、ｙ位置）
					Bmp_view(menu3_bmp[i], BMP_POSX, BMP_POSY);
					gotoxy(60, 4);
					printf("%s", menu00[MENU_03]);
					gotoxy(62, 42);
					printf("%s", menu3_hira[i]);
					gotoxy(62, 43);
					printf("%s\n", menu3[i]);
					for (int g = 0; g < i; g++)
					{
						gotoxy(4, 25 + g);
						printf("%s : %.1f", menu3_hira[g], par[g]);
					}
					gotoxy(60, 45);
					printf(">>");
					while (!typeend)
					{
						for (; moji < EN_CHAR; moji++)
						{
							IsTime(hThread, result);
							if (!IsEnd())
							{
								if (inport(pk_tbl[moji]))
								{
									reinport();
									type[a] = tolower(pk_tbl[moji]);
									printf("%c", type[a]);
									a++;
									if (a > 30)
									{
										typeend = true;
									}
									break;
								}
								else if (inport(PK_ENTER))
								{
									reinport();
									typeend = true;
									typeenter = true;
									break;
								}
							}
							else
							{
								typeend = true;
								break;
							}
						}
						moji = 0;
					}
					//工程のスコア計算
					if (typeenter)
					{
						for (int j = 0; j < a; j++)
						{
							if (type[j] == menu3[i][j])
							{
								score++;
							}
						}
						printf("\n");
						par[i] = ((float)score / (float)anslen) * 100;	//パーセンテージの計算
						parSEplay(par[i]);
						player_score += (int)par[i] * 10;	//スコア計算
					}
				}
				//合計パーセント計算
				if (typeenter)
				{
					for (g = 0; g < i; g++)
					{
						g_par += par[g];
					}
					g_par = ((float)g_par / (float)(i * 100)) * 100;
					player_score += (int)g_par * 100;	//ボーナススコア計算
					msleep(500); //ディレイ
					clrscr();
					WindowCreate();
					PlayerScoreView();
					Bmp_view(menu3_bmp[i], BMP_POSX, BMP_POSY);
					g_parSEplay(g_par);
					gotoxy(60, 4);
					printf("%s　：完成度　%.1f％", menu00[MENU_03], g_par);
					msleep(1400);
				}
				break;

			case MENU_04:
				for (i = 0; menu4[i] != NULL; i++)
				{
					//初期化
					typeend = false;
					score = 0;
					a = 0;

					IsTime(hThread, result);
					anslen = strlen(menu4[i]);
					clrscr();
					WindowCreate();
					PlayerScoreView();
					//画像表示　引数（bmpファイル名、ｘ位置、ｙ位置）
					Bmp_view(menu4_bmp[i], BMP_POSX, BMP_POSY);
					gotoxy(60, 4);
					printf("%s", menu00[MENU_04]);
					gotoxy(62, 42);
					printf("%s", menu4_hira[i]);
					gotoxy(62, 43);
					printf("%s\n", menu4[i]);
					for (int g = 0; g < i; g++)
					{
						gotoxy(4, 25 + g);
						printf("%s : %.1f", menu4_hira[g], par[g]);
					}
					gotoxy(60, 45);
					printf(">>");
					while (!typeend)
					{
						for (; moji < EN_CHAR; moji++)
						{
							IsTime(hThread, result);
							if (!IsEnd())
							{
								if (inport(pk_tbl[moji]))
								{
									reinport();
									type[a] = tolower(pk_tbl[moji]);
									printf("%c", type[a]);
									a++;
									if (a > 30)
									{
										typeend = true;
									}
									break;
								}
								else if (inport(PK_ENTER))
								{
									reinport();
									typeend = true;
									typeenter = true;
									break;
								}
							}
							else
							{
								typeend = true;
								break;
							}
						}
						moji = 0;
					}
					//工程のスコア計算
					if (typeenter)
					{
						for (int j = 0; j < a; j++)
						{
							if (type[j] == menu4[i][j])
							{
								score++;
							}
						}
						printf("\n");
						par[i] = ((float)score / (float)anslen) * 100;	//パーセンテージの計算
						parSEplay(par[i]);
						player_score += (int)par[i] * 10;	//スコア計算
					}
				}
				//合計パーセント計算
				if (typeenter)
				{
					for (g = 0; g < i; g++)
					{
						g_par += par[g];
					}
					g_par = ((float)g_par / (float)(i * 100)) * 100;
					player_score += (int)g_par * 100;	//ボーナススコア計算
					msleep(500); //ディレイ
					clrscr();
					WindowCreate();
					PlayerScoreView();
					Bmp_view(menu4_bmp[i], BMP_POSX, BMP_POSY);
					g_parSEplay(g_par);
					gotoxy(60, 4);
					printf("%s　：完成度　%.1f％", menu00[MENU_04], g_par);
					msleep(1400);
				}
				break;

			 case MENU_05:
				for (i = 0; menu5[i] != NULL; i++)
				{
					//初期化
					typeend = false;
					score = 0;
					a = 0;

					IsTime(hThread, result);
					anslen = strlen(menu5[i]);
					clrscr();
					WindowCreate();
					PlayerScoreView();
					//画像表示　引数（bmpファイル名、ｘ位置、ｙ位置）
					Bmp_view(menu5_bmp[i], BMP_POSX, BMP_POSY);
					gotoxy(60, 4);
					printf("%s", menu00[MENU_05]);
					gotoxy(62, 42);
					printf("%s", menu5_hira[i]);
					gotoxy(62, 43);
					printf("%s\n", menu5[i]);
					for (int g = 0; g < i; g++)
					{
						gotoxy(4, 25 + g);
						printf("%s : %.1f", menu5_hira[g], par[g]);
					}
					gotoxy(60, 45);
					printf(">>");
					while (!typeend)
					{
						for (; moji < EN_CHAR; moji++)
						{
							IsTime(hThread, result);
							if (!IsEnd())
							{
								if (inport(pk_tbl[moji]))
								{
									reinport();
									type[a] = tolower(pk_tbl[moji]);
									printf("%c", type[a]);
									a++;
									if (a > 30)
									{
										typeend = true;
									}
									break;
								}
								else if (inport(PK_ENTER))
								{
									reinport();
									typeend = true;
									typeenter = true;
									break;
								}
							}
							else
							{
								typeend = true;
								break;
							}
						}
						moji = 0;
					}
					//工程のスコア計算
					if (typeenter)
					{
						for (int j = 0; j < a; j++)
						{
							if (type[j] == menu5[i][j])
							{
								score++;
							}
						}
						printf("\n");
						par[i] = ((float)score / (float)anslen) * 100;	//パーセンテージの計算
						parSEplay(par[i]);
						player_score += (int)par[i] * 10;	//スコア計算
					}
				}
				//合計パーセント計算
				if (typeenter)
				{
					for (g = 0; g < i; g++)
					{
						g_par += par[g];
					}
					g_par = ((float)g_par / (float)(i * 100)) * 100;
					player_score += (int)g_par * 100;	//ボーナススコア計算
					msleep(500); //ディレイ
					clrscr();
					WindowCreate();
					PlayerScoreView();
					Bmp_view(menu5_bmp[i], BMP_POSX, BMP_POSY);
					g_parSEplay(g_par);
					gotoxy(60, 4);
					printf("%s　：完成度　%.1f％", menu00[MENU_05], g_par);
					msleep(1400);
				}
				break;

			case MENU_06:
				for (i = 0; menu6[i] != NULL; i++)
				{
					//初期化
					typeend = false;
					score = 0;
					a = 0;

					IsTime(hThread, result);
					anslen = strlen(menu6[i]);
					clrscr();
					WindowCreate();
					PlayerScoreView();
					//画像表示　引数（bmpファイル名、ｘ位置、ｙ位置）
					Bmp_view(menu6_bmp[i], BMP_POSX, BMP_POSY);
					gotoxy(60, 4);
					printf("%s", menu00[MENU_06]);
					gotoxy(62, 42);
					printf("%s", menu6_hira[i]);
					gotoxy(62, 43);
					printf("%s\n", menu6[i]);
					for (int g = 0; g < i; g++)
					{
						gotoxy(4, 25 + g);
						printf("%s : %.1f", menu6_hira[g], par[g]);
					}
					gotoxy(60, 45);
					printf(">>");
					while (!typeend)
					{
						for (; moji < EN_CHAR; moji++)
						{
							IsTime(hThread, result);
							if (!IsEnd())
							{
								if (inport(pk_tbl[moji]))
								{
									reinport();
									type[a] = tolower(pk_tbl[moji]);
									printf("%c", type[a]);
									a++;
									if (a > 30)
									{
										typeend = true;
									}
									break;
								}
								else if (inport(PK_ENTER))
								{
									reinport();
									typeend = true;
									typeenter = true;
									break;
								}
							}
							else
							{
								typeend = true;
								break;
							}
						}
						moji = 0;
					}
					//工程のスコア計算
					if (typeenter)
					{
						for (int j = 0; j < a; j++)
						{
							if (type[j] == menu6[i][j])
							{
								score++;
							}
						}
						printf("\n");
						par[i] = ((float)score / (float)anslen) * 100;	//パーセンテージの計算
						parSEplay(par[i]);
						player_score += (int)par[i] * 10;	//スコア計算
					}
				}
				//合計パーセント計算
				if (typeenter)
				{
					for (g = 0; g < i; g++)
					{
						g_par += par[g];
					}
					g_par = ((float)g_par / (float)(i * 100)) * 100;
					player_score += (int)g_par * 100;	//ボーナススコア計算
					msleep(500); //ディレイ
					clrscr();
					WindowCreate();
					PlayerScoreView();
					Bmp_view(menu6_bmp[i], BMP_POSX, BMP_POSY);
					g_parSEplay(g_par);
					gotoxy(60, 4);
					printf("%s　：完成度　%.1f％", menu00[MENU_06], g_par);
					msleep(1400);
				}
				break;

			case MENU_07:
				for (i = 0; menu7[i] != NULL; i++)
				{
					//初期化
					typeend = false;
					score = 0;
					a = 0;

					IsTime(hThread, result);
					anslen = strlen(menu7[i]);
					clrscr();
					WindowCreate();
					PlayerScoreView();
					//画像表示　引数（bmpファイル名、ｘ位置、ｙ位置）
					Bmp_view(menu7_bmp[i], BMP_POSX, BMP_POSY);
					gotoxy(60, 4);
					printf("%s", menu00[MENU_07]);
					gotoxy(62, 42);
					printf("%s", menu7_hira[i]);
					gotoxy(62, 43);
					printf("%s\n", menu7[i]);
					for (int g = 0; g < i; g++)
					{
						gotoxy(4, 25 + g);
						printf("%s : %.1f", menu7_hira[g], par[g]);
					}
					gotoxy(60, 45);
					printf(">>");
					while (!typeend)
					{
						for (; moji < EN_CHAR; moji++)
						{
							IsTime(hThread, result);
							if (!IsEnd())
							{
								if (inport(pk_tbl[moji]))
								{
									reinport();
									type[a] = tolower(pk_tbl[moji]);
									printf("%c", type[a]);
									a++;
									if (a > 30)
									{
										typeend = true;
									}
									break;
								}
								else if (inport(PK_ENTER))
								{
									reinport();
									typeend = true;
									typeenter = true;
									break;
								}
							}
							else
							{
								typeend = true;
								break;
							}
						}
						moji = 0;
					}
					//工程のスコア計算
					if (typeenter)
					{
						for (int j = 0; j < a; j++)
						{
							if (type[j] == menu7[i][j])
							{
								score++;
							}
						}
						printf("\n");
						par[i] = ((float)score / (float)anslen) * 100;	//パーセンテージの計算
						parSEplay(par[i]);
						player_score += (int)par[i] * 10;	//スコア計算
					}
				}
				//合計パーセント計算
				if (typeenter)
				{
					for (g = 0; g < i; g++)
					{
						g_par += par[g];
					}
					g_par = ((float)g_par / (float)(i * 100)) * 100;
					player_score += (int)g_par * 100;	//ボーナススコア計算
					msleep(500); //ディレイ
					clrscr();
					WindowCreate();
					PlayerScoreView();
					Bmp_view(menu7_bmp[i], BMP_POSX, BMP_POSY);
					g_parSEplay(g_par);
					gotoxy(60, 4);
					printf("%s　：完成度　%.1f％", menu00[MENU_07], g_par);
					msleep(1400);
				}
				break;

			case MENU_08:
				for (i = 0; menu8[i] != NULL; i++)
				{
					//初期化
					typeend = false;
					score = 0;
					a = 0;

					IsTime(hThread, result);
					anslen = strlen(menu8[i]);
					clrscr();
					WindowCreate();
					PlayerScoreView();
					//画像表示　引数（bmpファイル名、ｘ位置、ｙ位置）
					Bmp_view(menu8_bmp[i], BMP_POSX, BMP_POSY);
					gotoxy(60, 4);
					printf("%s", menu00[MENU_08]);
					gotoxy(62, 42);
					printf("%s", menu8_hira[i]);
					gotoxy(62, 43);
					printf("%s\n", menu8[i]);
					for (int g = 0; g < i; g++)
					{
						gotoxy(4, 25 + g);
						printf("%s : %.1f", menu8_hira[g], par[g]);
					}
					gotoxy(60, 45);
					printf(">>");
					while (!typeend)
					{
						for (; moji < EN_CHAR; moji++)
						{
							IsTime(hThread, result);
							if (!IsEnd())
							{
								if (inport(pk_tbl[moji]))
								{
									reinport();
									type[a] = tolower(pk_tbl[moji]);
									printf("%c", type[a]);
									a++;
									if (a > 30)
									{
										typeend = true;
									}
									break;
								}
								else if (inport(PK_ENTER))
								{
									reinport();
									typeend = true;
									typeenter = true;
									break;
								}
							}
							else
							{
								typeend = true;
								break;
							}
						}
						moji = 0;
					}
					//工程のスコア計算
					if (typeenter)
					{
						for (int j = 0; j < a; j++)
						{
							if (type[j] == menu8[i][j])
							{
								score++;
							}
						}
						printf("\n");
						par[i] = ((float)score / (float)anslen) * 100;	//パーセンテージの計算
						parSEplay(par[i]);
						player_score += (int)par[i] * 10;	//スコア計算
					}
				}
				//合計パーセント計算
				if (typeenter)
				{
					for (g = 0; g < i; g++)
					{
						g_par += par[g];
					}
					g_par = ((float)g_par / (float)(i * 100)) * 100;
					player_score += (int)g_par * 100;	//ボーナススコア計算
					msleep(500); //ディレイ
					clrscr();
					WindowCreate();
					PlayerScoreView();
					Bmp_view(menu8_bmp[i], BMP_POSX, BMP_POSY);
					g_parSEplay(g_par);
					gotoxy(60, 4);
					printf("%s　：完成度　%.1f％", menu00[MENU_08], g_par);
					msleep(1400);
				}
				break;

			case MENU_09:
				for (i = 0; menu9[i] != NULL; i++)
				{
					//初期化
					typeend = false;
					score = 0;
					a = 0;

					IsTime(hThread, result);
					anslen = strlen(menu9[i]);
					clrscr();
					WindowCreate();
					PlayerScoreView();
					//画像表示　引数（bmpファイル名、ｘ位置、ｙ位置）
					Bmp_view(menu9_bmp[i], BMP_POSX, BMP_POSY);
					gotoxy(60, 4);
					printf("%s", menu00[MENU_09]);
					gotoxy(62, 42);
					printf("%s", menu9_hira[i]);
					gotoxy(62, 43);
					printf("%s\n", menu9[i]);
					for (int g = 0; g < i; g++)
					{
						gotoxy(4, 25 + g);
						printf("%s : %.1f", menu9_hira[g], par[g]);
					}
					gotoxy(60, 45);
					printf(">>");
					while (!typeend)
					{
						for (; moji < EN_CHAR; moji++)
						{
							IsTime(hThread, result);
							if (!IsEnd())
							{
								if (inport(pk_tbl[moji]))
								{
									reinport();
									type[a] = tolower(pk_tbl[moji]);
									printf("%c", type[a]);
									a++;
									if (a > 30)
									{
										typeend = true;
									}
									break;
								}
								else if (inport(PK_ENTER))
								{
									reinport();
									typeend = true;
									typeenter = true;
									break;
								}
							}
							else
							{
								typeend = true;
								break;
							}
						}
						moji = 0;
					}
					//工程のスコア計算
					if (typeenter)
					{
						for (int j = 0; j < a; j++)
						{
							if (type[j] == menu9[i][j])
							{
								score++;
							}
						}
						printf("\n");
						par[i] = ((float)score / (float)anslen) * 100;	//パーセンテージの計算
						parSEplay(par[i]);
						player_score += (int)par[i] * 10;	//スコア計算
					}
				}
				//合計パーセント計算
				if (typeenter)
				{
					for (g = 0; g < i; g++)
					{
						g_par += par[g];
					}
					g_par = ((float)g_par / (float)(i * 100)) * 100;
					player_score += (int)g_par * 100;	//ボーナススコア計算
					msleep(500); //ディレイ
					clrscr();
					WindowCreate();
					PlayerScoreView();
					Bmp_view(menu9_bmp[i], BMP_POSX, BMP_POSY);
					g_parSEplay(g_par);
					gotoxy(60, 4);
					printf("%s　：完成度　%.1f％", menu00[MENU_09], g_par);
					msleep(1400);
				}
				break;
			}
			printf("\n");
		}
		//リザルト表示
		Result(hThread);
	}
	SoundEnd();
	return 0;
}

static DWORD WINAPI ThreadProc(LPVOID lpParameter)
{
	DWORD	now_time, pre_time;	// 時間計測用
	DWORD	remaining = *((DWORD*)lpParameter);	// 残り時間
	bool a = true;

	timeBeginPeriod(1);
	now_time = pre_time = timeGetTime();
	while (1) {
		now_time = timeGetTime();
		REmaining = remaining;
		if (now_time - pre_time >= 100) {

			if (remaining > now_time - pre_time) {
				remaining -= (now_time - pre_time);
			}
			else {
				remaining = 0;
			}

			pre_time = now_time;

			if (remaining == 0) {
				break;
			}
		}
	}
	return 0;
}

bool IsEnd(void)
{
	return end;
}

void Refreshend(void)
{
	end = false;
}

///////////////////////////////////////////////////////////////////////

//経過時間によって枠の色を変える

///////////////////////////////////////////////////////////////////////
void WindowCreate()
{
	if (REmaining >= TIME_GREEN)
	{
		textcolor(GREEN);
	}
	else if (REmaining < TIME_GREEN && REmaining >= TIME_ORANGE)
	{
		textcolor(BROWN);
	}
	else if (REmaining < TIME_GREEN && REmaining < TIME_ORANGE && REmaining > TIME_RED)
	{
		textcolor(RED);
	}

	Waku_View();
	normvideo();
}

void IsTime(HANDLE hthread, DWORD Result)
{
	GetExitCodeThread(hthread, &Result);	//タイマー終了判定
	if (STILL_ACTIVE == Result) {
		;
	}
	else {
		end = true;
	}
}

void PlayerScoreView()
{
	gotoxy(100, 3);
	printf("%d", player_score);
}

void CountDown()
{
	for (int i = 0; i < 4; i++)
	{
		Bmp_view(count3_bmp[i], 15, 1);
		msleep(10);
		if (i < 3)
		{
			clrscr();
		}
	}
	msleep(600);
	clrscr();

	for (int i = 0; i < 4; i++)
	{
		Bmp_view(count2_bmp[i], 15, 1);
		msleep(10);
		if (i < 3)
		{
			clrscr();
		}
	}
	msleep(600);
	clrscr();

	for (int i = 0; i < 4; i++)
	{
		Bmp_view(count1_bmp[i], 15, 1);
		msleep(10);
		if (i < 3)
		{
			clrscr();
		}
	}
	msleep(600);
	clrscr();

	Bmp_view("start.bmp", 15, 1);
	msleep(1000);
}

void GameInit()
{
	SoundInit();
}