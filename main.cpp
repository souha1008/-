///////////////////////////////////////////
//				�Q�[���T�v				 //
///////////////////////////////////////////

//����̓^�C�s���O�Q�[���ł��B60�b�ԂŁA�����_���ɂłĂ��闿���̍H���ƍޗ����^�C�s���O���ė��������A�����X�R�A���o���Q�[���ł��B�B
//���]�[�g���C���C�̉Ɓ@�Ƃ����`�ŘA�z���A�C�̉ƂŐH�ׂꂻ���ȗ�����p�ӂ��܂��B
//���̃^�C�s���O�Q�[���ɂ́u���m�x�v����������Ă���A�ł���������Ɛ����̕�������r���A���m�ɑłĂĂ��邩���p�[�Z���e�[�W�ŉ�������܂��B
//�e�H���́u���m�x�v�ɂ���ė����̎������܂�A�X�R�A���㉺���܂��B

//�X�R�A�v�Z	�e�H��(�p�[�Z���g�i�����_�؂�̂āj�~�P�O)�@�{�@�����̏o��(�p�[�Z���g�i�����_�؂�̂āj�~�P�O�O)�@���@�v���C���[�X�R�A

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
// �}�N���ݒ�
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

//�^�C�}�[�\������
#define TIME_GREEN	30000
#define TIME_ORANGE 11000
#define TIME_RED	0

//�L�[�̐�
#define EN_CHAR		26

//BMP�摜����̈ʒu
#define BMP_POSX	45
#define BMP_POSY	8

//���͂���L�[�̃e�[�u��
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

//�v���C���[�X�R�A
extern int player_score;

//�����_�������p
int rdm = 0;

//�^�C�}�[���Q�[���I���t���O
double REmaining;
bool end;

//�v���g�^�C�v�錾
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
	
	//�Q�[���J�n����
	GameInit();

	while (1)
	{
		//�^�C�}�[�p
		HANDLE hThread;			// �X���b�h�������邽�߂̃n���h���l
		DWORD dwThreadId;		// CreateThread(�X���b�h����)�֐��̈����p

		DWORD	data = 60000; //10000��10�b
		DWORD	result = 0;

		//�^�C�g���\��
		Title_view();

		//�`���[�g���A���\��
		Tutorial_view();

		//�J�E���g�_�E���J�n
		CountDown();

		//�^�C�}�[�Z�b�g
		hThread = CreateThread(NULL, 0, ThreadProc, &data, 0, &dwThreadId); 

		end = false;

		SoundPlayRepeet(SOUND_BGM01);
		while (!end)
		{
			srand((unsigned int)time(NULL));
			rdm = rand() % 5 + 1;	//�����_���Ɍ��߂�
			g_par = 0;
			//�X�C�b�`���ɂāA�\������郁�j���[���Ⴄ
			switch (rdm)
			{
			case MENU_01:
				for (i = 0; menu1[i] != NULL; i++)
				{
					//������
					typeend = false;
					typeenter = false;
					score = 0;
					a = 0;

					//�^�C���`�F�b�N
					IsTime(hThread, result);
					//�������i�[
					anslen = strlen(menu1[i]);
					//��ʍX�V
					clrscr();
					//��ʘg�\��
					WindowCreate();
					//UI�\��
					PlayerScoreView();
					//�摜�\���@�����ibmp�t�@�C�����A���ʒu�A���ʒu�j
					Bmp_view(menu1_bmp[i], BMP_POSX, BMP_POSY);	
					gotoxy(60, 4);
					printf("%s", menu00[MENU_01]);
					gotoxy(62, 42);
					printf("%s", menu1_hira[i]);
					gotoxy(62, 43);
					printf("%s", menu1[i]);
					//�X�R�A�\��
					for (int g = 0; g < i; g++)
					{
						gotoxy(4, 25 + g);
						printf("%s : %.1f", menu1_hira[g], par[g]);
					}
					gotoxy(60, 45);
					printf(">>");
					//���͊J�n
					while (!typeend)
					{
						for (; moji < EN_CHAR; moji++)	//�L�[�̐����J��Ԃ�
						{
							//�^�C���`�F�b�N
							IsTime(hThread, result);
							if (!IsEnd())
							{
								if (inport(pk_tbl[moji]))
								{
									reinport();
									type[a] = tolower(pk_tbl[moji]);	//���͂��ꂽ�ہA�啶���œ��邽�ߏ������������Ċi�[
									printf("%c", type[a]);
									a++;
									if (a > 30)	//�R�O��������
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
					//�H���̃X�R�A�v�Z
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
						par[i] = ((float)score / (float)anslen) * 100;	//�p�[�Z���e�[�W�̌v�Z
						parSEplay(par[i]);
						player_score += (int)par[i] * 10;	//�X�R�A�v�Z
					}
				}
				//���v�p�[�Z���g�v�Z
				if (typeenter)
				{
					for (g = 0; g < i; g++)
					{
						g_par += par[g];
					}
					g_par = ((float)g_par / (float)(i * 100)) * 100;
					player_score += (int)g_par * 100;	//�{�[�i�X�X�R�A�v�Z
					msleep(500); //�f�B���C
					clrscr();
					WindowCreate();
					PlayerScoreView();
					g_parSEplay(g_par);
					Bmp_view(menu1_bmp[i], BMP_POSX, BMP_POSY);
					gotoxy(60, 4);
					printf("%s�@�F�����x�@%.1f��", menu00[MENU_01], g_par);
					msleep(1400);
				}
				break;
				//�ȉ���������

			case MENU_02:
				for (i = 0; menu2[i] != NULL; i++)
				{
					//������
					typeend = false;
					typeenter = false;
					score = 0;
					a = 0;

					IsTime(hThread, result);
					anslen = strlen(menu2[i]);
					clrscr();
					WindowCreate();
					PlayerScoreView();
					//�摜�\���@�����ibmp�t�@�C�����A���ʒu�A���ʒu�j
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
					//�H���̃X�R�A�v�Z
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
						par[i] = ((float)score / (float)anslen) * 100;	//�p�[�Z���e�[�W�̌v�Z
						parSEplay(par[i]);
						player_score += (int)par[i] * 10;	//�X�R�A�v�Z
					}
				}
				//���v�p�[�Z���g�v�Z
				if (typeenter)
				{
					for (g = 0; g < i; g++)
					{
						g_par += par[g];
					}
					g_par = ((float)g_par / (float)(i * 100)) * 100;
					player_score += (int)g_par * 100;	//�{�[�i�X�X�R�A�v�Z
					msleep(500); //�f�B���C
					clrscr();
					WindowCreate();
					PlayerScoreView();
					Bmp_view(menu2_bmp[i], BMP_POSX, BMP_POSY);
					g_parSEplay(g_par);
					gotoxy(60, 4);
					printf("%s�@�F�����x�@%.1f��", menu00[MENU_02], g_par);
					msleep(1400);
				}
				break;

			case MENU_03:
				for (i = 0; menu3[i] != NULL; i++)
				{
					//������
					typeend = false;
					score = 0;
					a = 0;

					IsTime(hThread, result);
					anslen = strlen(menu3[i]);
					clrscr();
					WindowCreate();
					PlayerScoreView();
					//�摜�\���@�����ibmp�t�@�C�����A���ʒu�A���ʒu�j
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
					//�H���̃X�R�A�v�Z
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
						par[i] = ((float)score / (float)anslen) * 100;	//�p�[�Z���e�[�W�̌v�Z
						parSEplay(par[i]);
						player_score += (int)par[i] * 10;	//�X�R�A�v�Z
					}
				}
				//���v�p�[�Z���g�v�Z
				if (typeenter)
				{
					for (g = 0; g < i; g++)
					{
						g_par += par[g];
					}
					g_par = ((float)g_par / (float)(i * 100)) * 100;
					player_score += (int)g_par * 100;	//�{�[�i�X�X�R�A�v�Z
					msleep(500); //�f�B���C
					clrscr();
					WindowCreate();
					PlayerScoreView();
					Bmp_view(menu3_bmp[i], BMP_POSX, BMP_POSY);
					g_parSEplay(g_par);
					gotoxy(60, 4);
					printf("%s�@�F�����x�@%.1f��", menu00[MENU_03], g_par);
					msleep(1400);
				}
				break;

			case MENU_04:
				for (i = 0; menu4[i] != NULL; i++)
				{
					//������
					typeend = false;
					score = 0;
					a = 0;

					IsTime(hThread, result);
					anslen = strlen(menu4[i]);
					clrscr();
					WindowCreate();
					PlayerScoreView();
					//�摜�\���@�����ibmp�t�@�C�����A���ʒu�A���ʒu�j
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
					//�H���̃X�R�A�v�Z
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
						par[i] = ((float)score / (float)anslen) * 100;	//�p�[�Z���e�[�W�̌v�Z
						parSEplay(par[i]);
						player_score += (int)par[i] * 10;	//�X�R�A�v�Z
					}
				}
				//���v�p�[�Z���g�v�Z
				if (typeenter)
				{
					for (g = 0; g < i; g++)
					{
						g_par += par[g];
					}
					g_par = ((float)g_par / (float)(i * 100)) * 100;
					player_score += (int)g_par * 100;	//�{�[�i�X�X�R�A�v�Z
					msleep(500); //�f�B���C
					clrscr();
					WindowCreate();
					PlayerScoreView();
					Bmp_view(menu4_bmp[i], BMP_POSX, BMP_POSY);
					g_parSEplay(g_par);
					gotoxy(60, 4);
					printf("%s�@�F�����x�@%.1f��", menu00[MENU_04], g_par);
					msleep(1400);
				}
				break;

			 case MENU_05:
				for (i = 0; menu5[i] != NULL; i++)
				{
					//������
					typeend = false;
					score = 0;
					a = 0;

					IsTime(hThread, result);
					anslen = strlen(menu5[i]);
					clrscr();
					WindowCreate();
					PlayerScoreView();
					//�摜�\���@�����ibmp�t�@�C�����A���ʒu�A���ʒu�j
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
					//�H���̃X�R�A�v�Z
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
						par[i] = ((float)score / (float)anslen) * 100;	//�p�[�Z���e�[�W�̌v�Z
						parSEplay(par[i]);
						player_score += (int)par[i] * 10;	//�X�R�A�v�Z
					}
				}
				//���v�p�[�Z���g�v�Z
				if (typeenter)
				{
					for (g = 0; g < i; g++)
					{
						g_par += par[g];
					}
					g_par = ((float)g_par / (float)(i * 100)) * 100;
					player_score += (int)g_par * 100;	//�{�[�i�X�X�R�A�v�Z
					msleep(500); //�f�B���C
					clrscr();
					WindowCreate();
					PlayerScoreView();
					Bmp_view(menu5_bmp[i], BMP_POSX, BMP_POSY);
					g_parSEplay(g_par);
					gotoxy(60, 4);
					printf("%s�@�F�����x�@%.1f��", menu00[MENU_05], g_par);
					msleep(1400);
				}
				break;

			case MENU_06:
				for (i = 0; menu6[i] != NULL; i++)
				{
					//������
					typeend = false;
					score = 0;
					a = 0;

					IsTime(hThread, result);
					anslen = strlen(menu6[i]);
					clrscr();
					WindowCreate();
					PlayerScoreView();
					//�摜�\���@�����ibmp�t�@�C�����A���ʒu�A���ʒu�j
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
					//�H���̃X�R�A�v�Z
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
						par[i] = ((float)score / (float)anslen) * 100;	//�p�[�Z���e�[�W�̌v�Z
						parSEplay(par[i]);
						player_score += (int)par[i] * 10;	//�X�R�A�v�Z
					}
				}
				//���v�p�[�Z���g�v�Z
				if (typeenter)
				{
					for (g = 0; g < i; g++)
					{
						g_par += par[g];
					}
					g_par = ((float)g_par / (float)(i * 100)) * 100;
					player_score += (int)g_par * 100;	//�{�[�i�X�X�R�A�v�Z
					msleep(500); //�f�B���C
					clrscr();
					WindowCreate();
					PlayerScoreView();
					Bmp_view(menu6_bmp[i], BMP_POSX, BMP_POSY);
					g_parSEplay(g_par);
					gotoxy(60, 4);
					printf("%s�@�F�����x�@%.1f��", menu00[MENU_06], g_par);
					msleep(1400);
				}
				break;

			case MENU_07:
				for (i = 0; menu7[i] != NULL; i++)
				{
					//������
					typeend = false;
					score = 0;
					a = 0;

					IsTime(hThread, result);
					anslen = strlen(menu7[i]);
					clrscr();
					WindowCreate();
					PlayerScoreView();
					//�摜�\���@�����ibmp�t�@�C�����A���ʒu�A���ʒu�j
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
					//�H���̃X�R�A�v�Z
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
						par[i] = ((float)score / (float)anslen) * 100;	//�p�[�Z���e�[�W�̌v�Z
						parSEplay(par[i]);
						player_score += (int)par[i] * 10;	//�X�R�A�v�Z
					}
				}
				//���v�p�[�Z���g�v�Z
				if (typeenter)
				{
					for (g = 0; g < i; g++)
					{
						g_par += par[g];
					}
					g_par = ((float)g_par / (float)(i * 100)) * 100;
					player_score += (int)g_par * 100;	//�{�[�i�X�X�R�A�v�Z
					msleep(500); //�f�B���C
					clrscr();
					WindowCreate();
					PlayerScoreView();
					Bmp_view(menu7_bmp[i], BMP_POSX, BMP_POSY);
					g_parSEplay(g_par);
					gotoxy(60, 4);
					printf("%s�@�F�����x�@%.1f��", menu00[MENU_07], g_par);
					msleep(1400);
				}
				break;

			case MENU_08:
				for (i = 0; menu8[i] != NULL; i++)
				{
					//������
					typeend = false;
					score = 0;
					a = 0;

					IsTime(hThread, result);
					anslen = strlen(menu8[i]);
					clrscr();
					WindowCreate();
					PlayerScoreView();
					//�摜�\���@�����ibmp�t�@�C�����A���ʒu�A���ʒu�j
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
					//�H���̃X�R�A�v�Z
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
						par[i] = ((float)score / (float)anslen) * 100;	//�p�[�Z���e�[�W�̌v�Z
						parSEplay(par[i]);
						player_score += (int)par[i] * 10;	//�X�R�A�v�Z
					}
				}
				//���v�p�[�Z���g�v�Z
				if (typeenter)
				{
					for (g = 0; g < i; g++)
					{
						g_par += par[g];
					}
					g_par = ((float)g_par / (float)(i * 100)) * 100;
					player_score += (int)g_par * 100;	//�{�[�i�X�X�R�A�v�Z
					msleep(500); //�f�B���C
					clrscr();
					WindowCreate();
					PlayerScoreView();
					Bmp_view(menu8_bmp[i], BMP_POSX, BMP_POSY);
					g_parSEplay(g_par);
					gotoxy(60, 4);
					printf("%s�@�F�����x�@%.1f��", menu00[MENU_08], g_par);
					msleep(1400);
				}
				break;

			case MENU_09:
				for (i = 0; menu9[i] != NULL; i++)
				{
					//������
					typeend = false;
					score = 0;
					a = 0;

					IsTime(hThread, result);
					anslen = strlen(menu9[i]);
					clrscr();
					WindowCreate();
					PlayerScoreView();
					//�摜�\���@�����ibmp�t�@�C�����A���ʒu�A���ʒu�j
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
					//�H���̃X�R�A�v�Z
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
						par[i] = ((float)score / (float)anslen) * 100;	//�p�[�Z���e�[�W�̌v�Z
						parSEplay(par[i]);
						player_score += (int)par[i] * 10;	//�X�R�A�v�Z
					}
				}
				//���v�p�[�Z���g�v�Z
				if (typeenter)
				{
					for (g = 0; g < i; g++)
					{
						g_par += par[g];
					}
					g_par = ((float)g_par / (float)(i * 100)) * 100;
					player_score += (int)g_par * 100;	//�{�[�i�X�X�R�A�v�Z
					msleep(500); //�f�B���C
					clrscr();
					WindowCreate();
					PlayerScoreView();
					Bmp_view(menu9_bmp[i], BMP_POSX, BMP_POSY);
					g_parSEplay(g_par);
					gotoxy(60, 4);
					printf("%s�@�F�����x�@%.1f��", menu00[MENU_09], g_par);
					msleep(1400);
				}
				break;
			}
			printf("\n");
		}
		//���U���g�\��
		Result(hThread);
	}
	SoundEnd();
	return 0;
}

static DWORD WINAPI ThreadProc(LPVOID lpParameter)
{
	DWORD	now_time, pre_time;	// ���Ԍv���p
	DWORD	remaining = *((DWORD*)lpParameter);	// �c�莞��
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

//�o�ߎ��Ԃɂ���Ęg�̐F��ς���

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
	GetExitCodeThread(hthread, &Result);	//�^�C�}�[�I������
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