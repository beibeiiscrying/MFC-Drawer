#pragma once
#include "Graphic.h"
class CShape : public CGraphic
{
protected:
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

public:
	CShape();
	virtual void Draw(CDC* pDC);
	virtual bool IsMatched(CPoint pnt);
	void Serialize(CArchive& ar);
	virtual CRect GetTrackerRect();
	virtual ~CShape();
	//DECLARE_SERIAL(CShape)
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
};

