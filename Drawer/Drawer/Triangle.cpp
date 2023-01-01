#include "pch.h"
#include "Triangle.h"

IMPLEMENT_SERIAL(CTriangle, CObject, 1)


CTriangle::CTriangle() {
	this->type = ElementType::TRIANGLE;
	this->x = 0;
	this->y = 0;
	this->xWidth = 100;
	this->yWidth = 100;
	this->borderWidth = 1;
	this->borderType = 1;
	this->borderColor = NULL;
	this->fillColor = NULL;
	this->bgColor = NULL;
	this->isBg = false;
}

CTriangle::CTriangle(int graX, int graY, int xLength, int yLength, int borderWidth, int borderType, COLORREF borderColor, COLORREF fillColor, COLORREF bgColor) {
	this->type = ElementType::TRIANGLE;
	this->x = graX;
	this->y = graY;
	this->xWidth = xLength;
	this->yWidth = yLength;
	this->borderWidth = borderWidth;
	this->borderType = borderType;
	this->borderColor = borderColor;
	this->fillColor = fillColor;
	this->bgColor = bgColor;
	this->isBg = false;
}

void CTriangle::Draw(CDC* pDC) {
	CPen pen, * pOldPen;
	pen.CreatePen(borderType, borderWidth * ((borderType & 3) == 0), borderColor);
	pOldPen = (CPen*)pDC->SelectObject(&pen);

	CBrush brush(fillColor), * pOldBrush;
	pOldBrush = (CBrush*)pDC->SelectObject(&brush);

	double x1 = double(x), y1 = double(y) - double(yWidth) / 2;
	double x2 = double(x) - double(xWidth) / 2, y2 = double(y) + double(yWidth) / 2;
	double x3 = double(x) + double(xWidth) / 2, y3 = double(y) + double(yWidth) / 2;
	CPoint points[3] = { CPoint(int(x1), int(y1)), CPoint(int(x2), int(y2)), CPoint(int(x3), int(y3)) };

	pDC->Polygon(points, 3);

	pDC->SelectObject(pOldPen);
	pDC->SelectObject(pOldBrush);
}

bool CTriangle::IsMatched(CPoint pnt) {
	CRgn rgn;
	CPoint ptVertex[3];
	int offset = 1;
	int XOffset = xWidth >= 0 ? 1 * offset : -1 * offset;
	int YOffset = yWidth >= 0 ? 1 * offset : -1 * offset;
	rgn.CreateRectRgn(x - xWidth / 2 - XOffset, y - yWidth / 2 - YOffset, x + xWidth / 2 + XOffset, y + yWidth / 2 + YOffset);
	bool flag = rgn.PtInRegion(pnt);
	if (flag)
	{
		return true;
	}
	else
		return false;
}

CRect CTriangle::GetTrackerRect() {
	return CShape::GetTrackerRect();
}

CTriangle::~CTriangle() {

}