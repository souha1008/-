#include "Tutorial.h"
#include "CHAR.h"
#include "SOUND.h"

void Tutorial_view()
{
	Waku_View();

	gotoxy(4, 3);
	textbackground(LIGHTGRAY);
	textcolor(MAGENTA);
	printf("������");
	textcolor(BLACK);
	printf("�`���[�g���A��");
	textcolor(MAGENTA);
	printf("������");
	normvideo();
	GotoxyPrintf(5, 5, "���Ȃ��͂Ƃ���r�[�`�ɂ���A���l�C�ł��т��������C�̉Ɓu�^�C�v�V�[�T�C�h���]�[�g�v�ɃA���o�C�g�����ɗ��܂����B");
	GotoxyPrintf(5, 6, "�ł����E�E�E�����̊C�̉Ƃ͏�������B");
	textbackground(LIGHTGRAY);
	textcolor(RED);
	printf("�^�C�s���O");
	normvideo();
	printf("�ŗ�������邨�X�ł����B");
	GotoxyPrintf(5, 7, "�e�H�����ԈႦ�Ȃ��悤�Ƀ^�C�s���O���āA�U�O�b�ԂłP�O�O���̗���������������܂��傤�I");

	gotoxy(4, 10);
	textbackground(LIGHTGRAY);
	textcolor(YELLOW);
	printf("������");
	textcolor(BLACK);
	printf("������@");
	textcolor(YELLOW);
	printf("������");
	normvideo();
	GotoxyPrintf(5, 12, "�\������Ă��镶���uA�`Z�L�[�v�őł�����u�G���^�[�L�[�v�������I�I");

	gotoxy(4, 15);
	textbackground(LIGHTGRAY);
	textcolor(GREEN);
	printf("������");
	textcolor(BLACK);
	printf("��ʂ̌���");
	textcolor(GREEN);
	printf("������");
	normvideo();

	//�^�C�}�[�ɂ���
	GotoxyPrintf(4, 17, "�E�^�C�}�[�̌���");

	//�O���[���\��
	textcolor(GREEN);
	GotoxyPrintf(6, 19, "������");
	GotoxyPrintf(6, 20, "���@��");
	GotoxyPrintf(6, 21, "������");

	//�I�����W�\��
	textcolor(BROWN);
	GotoxyPrintf(14, 19, "������");
	GotoxyPrintf(14, 20, "���@��");
	GotoxyPrintf(14, 21, "������");

	//���b�h�\��
	textcolor(RED);
	GotoxyPrintf(22, 19, "������");
	GotoxyPrintf(22, 20, "���@��");
	GotoxyPrintf(22, 21, "������");

	normvideo();
	GotoxyPrintf(5, 23, "�o�ߎ��ԂŘg�̐F���ς��܂��B�c�莞�Ԃ̖ڈ��ɂ��Ă��������B***�c��10�b�ŐԐF�̘g�ɕς��܂�***");

	//�X�R�A�\���ɂ���
	GotoxyPrintf(4, 25, "�E�X�R�A�\��");
	GotoxyPrintf(4, 26, "�g���E��Ɍ��݂̃X�R�A��\�����Ă��܂��B");

	GotoxyPrintf(4, 28, "�E�e�H���̒B���x");
	GotoxyPrintf(4, 29, "�g�������ɗ����̒B�������H����\�����Ă��܂��B�B���x�̓p�[�Z���g�ŕ\������Ă��܂��B");

	//��闿��
	GotoxyPrintf(4, 31, "�E��闿���ƌ��݂̍H��");
	GotoxyPrintf(4, 32, "��闿���͘g���㕔�ɕ������\������Ă��܂��B�܂��A���݂̍H���͘g�������ɊG���\������g�������ɕ������\������܂��B");

	gotoxy(60, 44);
	textbackground(LIGHTGRAY);
	textcolor(BLACK);
	printf("�X�y�[�X�����ăX�^�[�g\n");
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