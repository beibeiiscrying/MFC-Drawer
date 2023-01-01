#pragma once
#include "Shape.h"
class CTriangle : public CShape
{

public:
	CTriangle();
	CTriangle(int graX, int graY, int xLength, int yLength, int borderWidth, int borderType, COLORREF borderColor, COLORREF fillColor, COLORREF bgColor);
	void Draw(CDC* pDC);
	bool IsMatched(CPoint pnt);
	CRect GetTrackerRect();
	~CTriangle();
	DECLARE_SERIAL(CTriangle)
};

