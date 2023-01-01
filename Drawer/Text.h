#pragma once
#include "Graphic.h"
class CText :public CGraphic
{

private:
	ElementType type;
	int x;
	int y;
	int xWidth;
	int yWidth;
	COLORREF borderColor;
	int borderType;
	int borderWidth;
	bool isBg;
	COLORREF fillColor;
	COLORREF bgColor;

	CString textContent;
	CString fontType;
	int textAngle;
	COLORREF textFillColor;
	bool underline;
	bool italic;
	int weight;
	int xTextWidth;
	int yTextWidth;

public:
	ElementType GetType();
	int GetX();
	int GetY();
	int GetXWidth();
	int GetYWidth();
	COLORREF GetBorderColor();
	int GetBorderType();
	int GetBorderWidth();
	bool GetIsBg();
	COLORREF GetFillColor();
	COLORREF GetBgColor();

	CString GetTextContent();
	CString GetFontType();
	int GetTextAngle();
	COLORREF GetTextFillColor();
	bool GetUnderline();
	bool GetItalic();
	int GetWeight();
	int GetXTextWidth();
	int GetYTextWidth();

	void SetX(int x);
	void SetY(int y);
	void SetXWidth(int xWidth);
	void SetYWidth(int yWidth);
	void SetBorderColor(COLORREF borderColor);
	void SetBorderType(int borderType);
	void SetBorderWidth(int borderWidth);
	void SetIsBg(bool isBg);
	void SetFillColor(COLORREF fillColor);
	void SetBgColor(COLORREF bgColor);

	void SetTextContent(CString textContent);
	void SetFontType(CString fontType);
	void SetTextAngle(int textAngle);
	void SetTextFillColor(COLORREF textFillColor);
	void SetUnderline(BOOL underline);
	void SetItalic(BOOL italic);
	void SetWeight(int weight);
	void SetXTextWidth(int xTextWidth);
	void SetYTextWidth(int yTextWidth);
public:
	CText();
	CText(int orgX, int orgY, CString textContent, int xTextWidth, int yTextWidth, int borderWidth, int borderType, COLORREF borderColor, COLORREF textFillColor, COLORREF bgColor, CString fontType, BOOL underline, BOOL italic, int weight);
	void Draw(CDC* pDC);
	bool IsMatched(CPoint pnt);
	void Serialize(CArchive& ar);
	CRect GetTrackerRect();
	~CText();
	DECLARE_SERIAL(CText)
};

