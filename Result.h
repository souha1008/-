#pragma once
#define CONIOEX
#include "MYconioex.h"

//�X�R�A�����N�}�N��
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
	"�X�傩��̂����Ƃ΁u���������A����肷�����񂶂�Ȃ����H�����͋�����{�ɂ��Ă���I������낵���ȁI�v",
	"�X�傩��̂����Ƃ΁u������l�O���ȁI�����̔���͂��O����̂��������I���肪�ƂȁI�v",
	"�X�傩��̂����Ƃ΁u�܂����ꂮ�炢�͂���Ă����Ȃ��ƂȁB�������낵���I�v",
	"�X�傩��̂����Ƃ΁u���������A���������撣���ė~���������ȁB�v",
	"�X�傩��̂����Ƃ΁u�܂����A���̌��ʂɋ����𕥂��ƌ���Ȃ���ȁH�v"
};