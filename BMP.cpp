#define CONIOEX
#include "MYconioex.h"
#include <atlimage.h>  //�摜��ǂݍ��ނ��߂̃��C�u����
#include "BMP.h"

//-------------------------------------------------------------------
// �O���[�o���ϐ��錾
//-------------------------------------------------------------------
static DWORD	transparent_color;		// ���ߐF
bool once = false;

//-------------------------------------------------------------------
// �g�p�摜�o�^
//-------------------------------------------------------------------


//-------------------------------------------------------------------
// BMP�t�@�C������͂���(�S�Ă�BMP�t�@�C���ɑΉ�)
//-------------------------------------------------------------------
bool BmpLoad(const char* fname, bmp_t* p)
{
	HBITMAP		hBitmap;	// �r�b�g�}�b�v�t�@�C�����[�h�p
	CImage		image;		// �r�b�g�}�b�v�C���[�W

	memset(p, 0, sizeof(bmp_t));	// BMP�����O�N���A����

	hBitmap = (HBITMAP)LoadImageA(NULL, fname, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	if (hBitmap == NULL) {
		printf("%s�����[�h�ł��܂���\n", fname);
		return false;
	}
	image.Attach(hBitmap);	// ATL��CImage�^�Ƀ��[�h�����f�[�^���A�^�b�`����

	p->height = image.GetHeight();	// �r�b�g�}�b�v�̍������擾
	p->width = image.GetWidth();	// �r�b�g�}�b�v�̕����擾

	p->pixel = (color_t*)calloc(p->height * p->width, sizeof(color_t));
	if (p->pixel == NULL) {
		printf("�������s��������\n");
		image.Destroy();
		DeleteObject(hBitmap);
		return false;
	}
	for (int y = 0; y < p->height; y++) {
		for (int x = 0; x < p->width; x++) {
			COLORREF pixel = image.GetPixel(x, y);	// �s�N�Z�������擾

			// �O�ŏ��������Ă���ΐԂ̋P�x�l��ݒ肷��
			p->pixel[y * p->width + x].long_color = 0;
			p->pixel[y * p->width + x].byte_color.rgbBlue = GetBValue(pixel);
			p->pixel[y * p->width + x].byte_color.rgbGreen = GetGValue(pixel);
			p->pixel[y * p->width + x].byte_color.rgbRed = GetRValue(pixel);
		}
	}
	image.Destroy();
	DeleteObject(hBitmap);
	return true;
}
//-------------------------------------------------------------------
// BmpLoad�Ŋl���������I��������ԋp����
//-------------------------------------------------------------------
void BmpDelete(bmp_t* p)
{
	if (p->pixel != NULL)	free(p->pixel);
}
//-------------------------------------------------------------------
// �s�N�Z���f�[�^��\������
//-------------------------------------------------------------------
void BmpPrint(int pos_x, int pos_y, bmp_t* p)
{
	if (p->pixel == NULL)	return;	// ���I�̈斢�l���Ȃ牽�����Ȃ�

	for (int y = 0; y < p->height; y++) {
		gotoxy(pos_x, pos_y);
		for (int x = 0; x < p->width; x++) {
			// ���ߐF�͕\�����Ȃ�
			if (p->pixel[y * p->width + x].long_color == transparent_color) {
				gotoxy(pos_x + (x + 1) * 2, pos_y);		// �J�[�\�������̈ʒu�Ɉړ�
			}
			else {
				printf("\033[48;2;%d;%d;%dm  ",		// RGB�Ŕw�i�F��ݒ�
					p->pixel[y * p->width + x].byte_color.rgbRed,
					p->pixel[y * p->width + x].byte_color.rgbGreen,
					p->pixel[y * p->width + x].byte_color.rgbBlue);
			}
		}
		pos_y++;
		printf("\033[0m");	// �F�w��̃G�X�P�[�v�V�[�P���X���I��
	}
}
//-------------------------------------------------------------------
// ���ߐF���Z�b�g����
//-------------------------------------------------------------------
void setBmpTransparentColor(DWORD color)
{
	transparent_color = color;
}

void Bmp_view(const char* FNAME, int pos_x, int pos_y)
{
	bmp_t	BMP;					// BMP�f�[�^���͗p

	if (!once)
	{
		system("cls");
		once = true;
	}
	setBmpTransparentColor(0x00ff00);	//���ߐF�����ɐݒ�

		if (BmpLoad(FNAME, &BMP)) {		// BMP�t�@�C���������ł����ꍇ
			BmpPrint(pos_x, pos_y, &BMP);			// BMP�t�@�C���̃s�N�Z���f�[�^��\��
			BmpDelete(&BMP);	// BmpLoad���������Ă���̂Ŋl���������I�̈��ԋp
		}
		else {	// BMP�t�@�C���������ł��Ȃ������ꍇ(�G���[���b�Z�[�W�\���L��)
			(void)_getch();		// �G�R�[�o�b�N������rewind�s�v�̃L�[���͑҂�
		}
}