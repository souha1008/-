#define CONIOEX
#include "MYconioex.h"
#include <atlimage.h>  //画像を読み込むためのライブラリ
#include "BMP.h"

//-------------------------------------------------------------------
// グローバル変数宣言
//-------------------------------------------------------------------
static DWORD	transparent_color;		// 透過色
bool once = false;

//-------------------------------------------------------------------
// 使用画像登録
//-------------------------------------------------------------------


//-------------------------------------------------------------------
// BMPファイルを入力する(全てのBMPファイルに対応)
//-------------------------------------------------------------------
bool BmpLoad(const char* fname, bmp_t* p)
{
	HBITMAP		hBitmap;	// ビットマップファイルロード用
	CImage		image;		// ビットマップイメージ

	memset(p, 0, sizeof(bmp_t));	// BMP情報を０クリアする

	hBitmap = (HBITMAP)LoadImageA(NULL, fname, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	if (hBitmap == NULL) {
		printf("%sがロードできません\n", fname);
		return false;
	}
	image.Attach(hBitmap);	// ATLのCImage型にロードしたデータをアタッチする

	p->height = image.GetHeight();	// ビットマップの高さを取得
	p->width = image.GetWidth();	// ビットマップの幅を取得

	p->pixel = (color_t*)calloc(p->height * p->width, sizeof(color_t));
	if (p->pixel == NULL) {
		printf("メモリ不足が発生\n");
		image.Destroy();
		DeleteObject(hBitmap);
		return false;
	}
	for (int y = 0; y < p->height; y++) {
		for (int x = 0; x < p->width; x++) {
			COLORREF pixel = image.GetPixel(x, y);	// ピクセル情報を取得

			// ０で初期化してから青緑赤の輝度値を設定する
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
// BmpLoadで獲得した動的メモリを返却する
//-------------------------------------------------------------------
void BmpDelete(bmp_t* p)
{
	if (p->pixel != NULL)	free(p->pixel);
}
//-------------------------------------------------------------------
// ピクセルデータを表示する
//-------------------------------------------------------------------
void BmpPrint(int pos_x, int pos_y, bmp_t* p)
{
	if (p->pixel == NULL)	return;	// 動的領域未獲得なら何もしない

	for (int y = 0; y < p->height; y++) {
		gotoxy(pos_x, pos_y);
		for (int x = 0; x < p->width; x++) {
			// 透過色は表示しない
			if (p->pixel[y * p->width + x].long_color == transparent_color) {
				gotoxy(pos_x + (x + 1) * 2, pos_y);		// カーソルを次の位置に移動
			}
			else {
				printf("\033[48;2;%d;%d;%dm  ",		// RGBで背景色を設定
					p->pixel[y * p->width + x].byte_color.rgbRed,
					p->pixel[y * p->width + x].byte_color.rgbGreen,
					p->pixel[y * p->width + x].byte_color.rgbBlue);
			}
		}
		pos_y++;
		printf("\033[0m");	// 色指定のエスケープシーケンスを終了
	}
}
//-------------------------------------------------------------------
// 透過色をセットする
//-------------------------------------------------------------------
void setBmpTransparentColor(DWORD color)
{
	transparent_color = color;
}

void Bmp_view(const char* FNAME, int pos_x, int pos_y)
{
	bmp_t	BMP;					// BMPデータ入力用

	if (!once)
	{
		system("cls");
		once = true;
	}
	setBmpTransparentColor(0x00ff00);	//透過色を黒に設定

		if (BmpLoad(FNAME, &BMP)) {		// BMPファイルが準備できた場合
			BmpPrint(pos_x, pos_y, &BMP);			// BMPファイルのピクセルデータを表示
			BmpDelete(&BMP);	// BmpLoadが成功しているので獲得した動的領域を返却
		}
		else {	// BMPファイルが準備できなかった場合(エラーメッセージ表示有り)
			(void)_getch();		// エコーバック無しでrewind不要のキー入力待ち
		}
}