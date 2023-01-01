#pragma once
#include <afx.h>
class CGraphic : public CObject
{
public:
	CGraphic();
	enum class ElementType { TRIANGLE, ELLIPSE, TEXT };
	virtual void Draw(CDC* pDC) = 0;
	virtual bool IsMatched(CPoint pnt) = 0;
	virtual void Serialize(CArchive& ar) = 0;
	void SetAttribute(int graX, int graY, COLORREF borderColor, int borderType, int borderWidth, COLORREF fillColor, COLORREF bgColor);
	virtual CRect GetTrackerRect() = 0;
	virtual ~CGraphic();
	virtual ElementType GetType() = 0;
	virtual int GetX() = 0;
	virtual int GetY() = 0;
	virtual int GetXWidth() = 0;
	virtual int GetYWidth() = 0;
	virtual COLORREF GetBorderColor() = 0;
	virtual int GetBorderType() = 0;
	virtual int GetBorderWidth() = 0;
	virtual bool GetIsBg() = 0;
	virtual COLORREF GetFillColor() = 0;
	virtual COLORREF GetBgColor() = 0;
	virtual void SetX(int x) = 0;
	virtual void SetY(int y) = 0;
	virtual void SetXWidth(int xWidth) = 0;
	virtual void SetYWidth(int yWidth) = 0;
	virtual void SetBorderColor(COLORREF borderColor) = 0;
	virtual void SetBorderType(int borderType) = 0;
	virtual void SetBorderWidth(int borderWidth) = 0;
	virtual void SetIsBg(bool isBg) = 0;
	virtual void SetFillColor(COLORREF fillColor) = 0;
	virtual void SetBgColor(COLORREF bgColor) = 0;


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

};

