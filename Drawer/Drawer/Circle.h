#pragma once
#include "Shape.h"
class CCircle : public CShape
{
public:
	CCircle();
	CCircle(int graX, int graY, int xRadius, int yRadius, int borderWidth, int borderType, COLORREF borderColor, COLORREF fillColor, COLORREF bgColor);
	void Draw(CDC* pDC);
	bool IsMatched(CPoint pnt);
	CRect GetTrackerRect();
	CRectTracker m_RectTracker;
	~CCircle();
	DECLARE_SERIAL(CCircle); //wCircle ¥i§Ç¦C¤Æ
};

