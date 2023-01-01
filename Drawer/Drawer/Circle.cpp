#include "pch.h"
#include "Circle.h"


IMPLEMENT_SERIAL(CCircle, CObject, 1)

CCircle::CCircle()
{
	type = ElementType::ELLIPSE;
	x = 0;
	y = 0;
	xWidth = 0;
	yWidth = 0;
	borderColor = NULL;
	borderType = 0;
	borderWidth = 0;
	fillColor = NULL;
	isBg = false;
	fillColor = NULL;
	bgColor = NULL;
}

CCircle::CCircle(int graX, int graY, int xRadius, int yRadius, int borderWidth, int borderType, COLORREF borderColor, COLORREF fillColor, COLORREF bgColor)
{
	type = ElementType::ELLIPSE;
	this->x = graX;
	this->y = graY;
	this->xWidth = xRadius;
	this->yWidth = yRadius;
	this->borderColor = borderColor;
	this->borderType = borderType;
	this->borderWidth = borderWidth;
	this->fillColor = fillColor;
	this->bgColor = bgColor;
	this->isBg = false;
}

void CCircle::Draw(CDC* pDC)
{
	CPen pen, * pOldPen;

	pen.CreatePen(borderType, borderWidth * ((borderType & 3) == 0), borderColor);
	pOldPen = (CPen*)pDC->SelectObject(&pen);

	CBrush brush(fillColor), * pOldBrush;
	pOldBrush = (CBrush*)pDC->SelectObject(&brush);

	pDC->Ellipse(x - xWidth / 2, y + yWidth / 2, x + xWidth / 2, y - yWidth / 2);

	pDC->SelectObject(pOldPen);
	pDC->SelectObject(pOldBrush);
}

bool CCircle::IsMatched(CPoint pnt)
{
	CRgn rgn;
	int offset = 1;
	int XOffset = xWidth >= 0 ? 1 * offset : -1 * offset;
	int YOffset = yWidth >= 0 ? 1 * offset : -1 * offset;
	rgn.CreateEllipticRgn(x - xWidth / 2 - XOffset, y - yWidth / 2 - YOffset, x + xWidth / 2 + XOffset, y + yWidth / 2 + YOffset);
	bool flag = rgn.PtInRegion(pnt);
	if (flag)
	{
		return true;
	}
	else
		return false;
}

CRect CCircle::GetTrackerRect() {
	return CShape::GetTrackerRect();
}

CCircle::~CCircle()
{
}