// pch.cpp: 對應到先行編譯標頭的來源檔案

#include "pch.h"

// 使用先行編譯的標頭時，需要來源檔案才能使編譯成功。

static CMFCToolBarFontComboBox unused(0, -1);
COLORREF bntColor[3] = { RGB(0,0,0),RGB(255,255,255),RGB(0,0,0), };
int nStepColor = 0;
int m_OldType = 0;
int OldType = 0;
CString m_FontType = _T("Comic Sans MS");
bool m_Underline = false;
bool m_Italic = false;
bool m_IsBg = false;
int m_Weight = 0;