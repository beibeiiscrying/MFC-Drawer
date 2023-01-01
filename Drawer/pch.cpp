// pch.cpp: 對應到先行編譯標頭的來源檔案

#include "pch.h"

// 使用先行編譯的標頭時，需要來源檔案才能使編譯成功。

// 阻止 CMFCFontComboBox 一直重複重載
static CMFCToolBarFontComboBox unused(0, -1);
//COLORREF m_GlobalBntColor[3] = { RGB(0,0,0), RGB(255,255,255), RGB(0,0,0) };
//int m_GlobalNextStepColor = 0;
//int m_GlobalBorderType = 0;
//int m_GlobalObjType = 0;
//CString m_GlobalTextFontType = _T("Comic Sans MS");
//bool m_GlobalTextUnderline = false;
//bool m_GlobalTextItalic = false;
//bool m_GlobalIsBg = false;
//int m_GlobalTextWeight = 0;