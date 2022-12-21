#pragma once

#define BG_DELAY 100

//------------------------------------------------------
// �^�O�錾
//------------------------------------------------------
typedef union {
	RGBQUAD		byte_color;		// �ΐԂ�BYTE�^�Ƃ��Č��郁���o
	DWORD		long_color;		// 32�r�b�g�l�Ƃ��Č��郁���o
}color_t;	// �ΐԂ̋P�x�l�^

typedef struct {
	int			width;		// �h�b�g�G�̕�
	int			height;		// �h�b�g�G�̍���
	color_t* pixel;			// �s�N�Z���f�[�^(���I�̈�)
}bmp_t;

//-------------------------------------------------------------------
// �֐��v���g�^�C�v�錾
//-------------------------------------------------------------------
bool BmpLoad(const char* fname, bmp_t* p);
void BmpDelete(bmp_t* p);
void BmpPrint(int pos_x, int pos_y, bmp_t* p);
void setBmpTransparentColor(DWORD color);
void Bmp_view(const char* FNAME, int pos_x, int pos_y);