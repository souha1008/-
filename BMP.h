#pragma once

#define BG_DELAY 100

//------------------------------------------------------
// タグ宣言
//------------------------------------------------------
typedef union {
	RGBQUAD		byte_color;		// 青緑赤のBYTE型として見るメンバ
	DWORD		long_color;		// 32ビット値として見るメンバ
}color_t;	// 青緑赤の輝度値型

typedef struct {
	int			width;		// ドット絵の幅
	int			height;		// ドット絵の高さ
	color_t* pixel;			// ピクセルデータ(動的領域)
}bmp_t;

//-------------------------------------------------------------------
// 関数プロトタイプ宣言
//-------------------------------------------------------------------
bool BmpLoad(const char* fname, bmp_t* p);
void BmpDelete(bmp_t* p);
void BmpPrint(int pos_x, int pos_y, bmp_t* p);
void setBmpTransparentColor(DWORD color);
void Bmp_view(const char* FNAME, int pos_x, int pos_y);