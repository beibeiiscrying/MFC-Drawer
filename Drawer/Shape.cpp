#include "pch.h"
#include "Shape.h"

CShape::CShape()
{
	this->type = ElementType::TRIANGLE;
	this->x = 0;
	this->y = 0;
	this->xWidth = 100;
	this->yWidth = 100;
	this->borderColor = NULL;
	this->borderType = 0;
	this->borderWidth = 0;
	this->fillColor = NULL;
	this->isBg = false;
	this->fillColor = NULL;
	this->bgColor = NULL;
}

void CShape::Draw(CDC* pDC) {

}

bool CShape::IsMatched(CPoint pnt)
{
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

void CShape::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		ar << (int)type;
		ar << x << y;
		ar << borderColor << borderType << borderWidth;
		ar << fillColor << bgColor << isBg;
		ar << xWidth << yWidth;
	}
	else
	{
		ar >> x >> y;
		ar >> borderColor >> borderType >> borderWidth;
		ar >> fillColor >> bgColor >> isBg;
		ar >> xWidth >> yWidth;
	}
}

CRect CShape::GetTrackerRect() 
{
	return CRect((x - xWidth / 2), (y - yWidth / 2), (x + xWidth / 2), (y + yWidth / 2));
}

CShape::~CShape()
{

}


CGraphic::ElementType CShape::GetType()
{
	return type;
}
int CShape::GetX()
{
	return x;
}
int CShape::GetY()
{
	return y;
}
int CShape::GetXWidth()
{
	return xWidth;
}
int CShape::GetYWidth()
{
	return yWidth;
}
COLORREF CShape::GetBorderColor()
{
	return borderColor;
}
int CShape::GetBorderType()
{
	return borderType;
}
int CShape::GetBorderWidth()
{
	return borderWidth;
}

bool CShape::GetIsBg()
{
	return isBg;
}

COLORREF CShape::GetFillColor()
{
	return fillColor;
}

COLORREF CShape::GetBgColor()
{
	return bgColor;
}

void CShape::SetX(int x)
{
	this->x = x;
}
void CShape::SetY(int y)
{
	this->y = y;
}
void CShape::SetXWidth(int xWidth)
{
	this->xWidth = xWidth;
}
void CShape::SetYWidth(int yWidth)
{
	this->yWidth = yWidth;
}
void CShape::SetBorderColor(COLORREF borderColor)
{
	this->borderColor = borderColor;
}
void CShape::SetBorderType(int borderType)
{
	this->borderType = borderType;
}
void CShape::SetBorderWidth(int borderWidth)
{
	this->borderWidth = borderWidth;
}
void CShape::SetIsBg(bool isBg)
{
	this->isBg = isBg;
}
void CShape::SetFillColor(COLORREF fillColor)
{
	this->fillColor = fillColor;
}
void CShape::SetBgColor(COLORREF bgColor)
{
	this->bgColor = bgColor;
}
