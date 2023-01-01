#include "pch.h"
#include "Graphic.h"

CGraphic::CGraphic() {
	type = ElementType::TRIANGLE;
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

void CGraphic::SetAttribute(int graX, int graY, COLORREF borderColor,
	int borderType, int borderWidth, COLORREF fillColor, COLORREF bgColor) {
	this->x = graX;
	this->y = graY;
	this->borderColor = borderColor;
	this->borderType = borderType;
	this->fillColor = fillColor;
	this->bgColor = bgColor;
	this->isBg = false;
}

CGraphic::~CGraphic() {

}