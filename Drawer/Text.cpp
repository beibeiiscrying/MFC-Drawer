#include "pch.h"
#include "Text.h"


IMPLEMENT_SERIAL(CText, CGraphic, 1)

CText::CText() {
	this->type = ElementType::TEXT;
	this->x = 0;
	this->y = 0;
	this->fontType = L"";
	this->textContent = L"";
	this->borderWidth = 0;
	this->borderType = 0;
	this->borderColor = NULL;
	this->textFillColor = NULL;
	this->underline = false;
	this->italic = false;
	this->weight = false;
	this->xTextWidth = 0;
	this->yTextWidth = 0;
	this->bgColor = NULL;
	this->isBg = false;
}

CText::CText(int orgX, int orgY, CString textContent, int xTextWidth, int yTextWidth,
	int borderWidth, int borderType, COLORREF borderColor, COLORREF textFillColor, COLORREF bgColor, CString fontType, BOOL underline, BOOL italic, int weight)
{
	this->type = (ElementType)2;
	this->x = orgX;
	this->y = orgY;
	this->fontType = fontType;
	this->textContent = textContent;
	this->borderWidth = borderWidth;
	this->borderType = borderType;
	this->borderColor = borderColor;
	this->textFillColor = textFillColor;
	this->underline = underline;
	this->italic = italic;
	this->weight = weight;
	this->xTextWidth = xTextWidth + 8;
	this->yTextWidth = yTextWidth;
	this->bgColor = bgColor;
	this->isBg = false;
}

void CText::Draw(CDC* pDC) {
	LOGFONT logfont = LOGFONT();
	lstrcpy(logfont.lfFaceName, fontType);
	//lstrcpy(logfont.lfFaceName, _T("FZShuTi"));
	logfont.lfWeight = weight;
	logfont.lfHeight = 16;
	logfont.lfEscapement = 0;
	logfont.lfUnderline = underline;
	logfont.lfItalic = italic;
	logfont.lfStrikeOut = FALSE;
	logfont.lfCharSet = ANSI_CHARSET;
	//LPRECT rect = CRect(x + 4, y, x + 120 - 4, y + 16);
	LPRECT rect = CRect(x + 4, y, x + xTextWidth - 4, y + 16);
	HFONT hFont, * hOldFont;
	hFont = CreateFontIndirect(&logfont);
	hOldFont = (HFONT*)pDC->SelectObject(hFont);
	pDC->SetBkColor(textFillColor);
	pDC->SetTextColor(borderColor);
	pDC->SetBkColor(bgColor);
	//pDC->SetBkColor(TRANSPARENT);
	pDC->DrawText(textContent, (int)wcslen(textContent), rect, DT_LEFT);
	pDC->SelectObject(hOldFont);
}

bool CText::IsMatched(CPoint pnt) {

	SIZE  size;
	HFONT pNewFont = CreateFontW(yTextWidth, xTextWidth, 0, 0, 40, FALSE, FALSE, FALSE, GB2312_CHARSET, OUT_CHARACTER_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH & FF_SWISS, fontType);
	HDC hDC = CreateCompatibleDC(NULL);
	SelectObject(hDC, pNewFont);
	if (GetTextExtentPoint32(hDC, textContent, (int)wcslen(textContent), &size))
	{
		CRgn rgn;
		POINT ptVertex[4] = {0};
		ptVertex[0].x = x;
		ptVertex[0].y = y;
		ptVertex[1].x = x + xTextWidth;
		ptVertex[1].y = y;
		ptVertex[2].x = x + xTextWidth;
		ptVertex[2].y = y + yTextWidth;
		ptVertex[3].x = x;
		ptVertex[3].y = y + yTextWidth;
		rgn.CreatePolygonRgn(ptVertex, 4, WINDING);

		BOOL flag = rgn.PtInRegion(pnt);
		if (flag)
		{
			return true;
		}
		else
			return false;
	}
	else
		return false;
}

void CText::Serialize(CArchive& ar) {
	if (ar.IsStoring())
	{
		ar << (int)type;
		ar << x << y;
		ar << borderColor << borderType << borderWidth;
		ar << textFillColor << fontType << underline << italic << weight << bgColor << isBg;
		ar << textContent << xTextWidth << yTextWidth;
	}
	else
	{
		//int w;
		//ar >> w;
		//type = (ElementType)w;
		ar >> x >> y;
		ar >> borderColor >> borderType >> borderWidth;
		ar >> textFillColor >> fontType >> underline >> italic >> weight >> bgColor >> isBg;
		ar >> textContent >> xTextWidth >> yTextWidth;
	}
}
CRect CText::GetTrackerRect() {
	return CRect(x, y, (x + xTextWidth), (y + yTextWidth));
}

CText::~CText() {

}

CGraphic::ElementType CText::GetType()
{
	return type;
}
int CText::GetX()
{
	return x;
}
int CText::GetY()
{
	return y;
}
int CText::GetXWidth()
{
	return xWidth;
}
int CText::GetYWidth()
{
	return yWidth;
}
COLORREF CText::GetBorderColor()
{
	return borderColor;
}
int CText::GetBorderType()
{
	return borderType;
}
int CText::GetBorderWidth()
{
	return borderWidth;
}

bool CText::GetIsBg()
{
	return isBg;
}

COLORREF CText::GetFillColor()
{
	return fillColor;
}

COLORREF CText::GetBgColor()
{
	return bgColor;
}

CString CText::GetTextContent()
{
	return textContent;
}
CString CText::GetFontType()
{
	return fontType;
}
int CText::GetTextAngle()
{
	return textAngle;
}
COLORREF CText::GetTextFillColor()
{
	return textFillColor;
}
bool CText::GetUnderline()
{
	return underline;
}
bool CText::GetItalic()
{
	return italic;
}
int CText::GetWeight()
{
	return weight;
}
int CText::GetXTextWidth()
{
	return xTextWidth;
}
int CText::GetYTextWidth()
{
	return yTextWidth;
}



void CText::SetX(int x)
{
	this->x = x;
}
void CText::SetY(int y)
{
	this->y = y;
}
void CText::SetXWidth(int xWidth)
{
	this->xWidth = xWidth;
}
void CText::SetYWidth(int yWidth)
{
	this->yWidth = yWidth;
}
void CText::SetBorderColor(COLORREF borderColor)
{
	this->borderColor = borderColor;
}
void CText::SetBorderType(int borderType)
{
	this->borderType = borderType;
}
void CText::SetBorderWidth(int borderWidth)
{
	this->borderWidth = borderWidth;
}
void CText::SetIsBg(bool isBg)
{
	this->isBg = isBg;
}
void CText::SetFillColor(COLORREF fillColor)
{
	this->fillColor = fillColor;
}
void CText::SetBgColor(COLORREF bgColor)
{
	this->bgColor = bgColor;
}

void CText::SetTextContent(CString textContent)
{
	this->textContent = textContent;
}
void CText::SetFontType(CString fontType)
{
	this->fontType = fontType;
}
void CText::SetTextAngle(int textAngle)
{
	this->textAngle = textAngle;
}
void CText::SetTextFillColor(COLORREF textFillColor)
{
	this->textFillColor = textFillColor;
}
void CText::SetUnderline(BOOL underline)
{
	this->underline = underline;
}
void CText::SetItalic(BOOL italic)
{
	this->italic = italic;
}
void CText::SetWeight(int weight)
{
	this->weight = weight;
}
void CText::SetXTextWidth(int xTextWidth)
{
	this->xTextWidth = xTextWidth;
}
void CText::SetYTextWidth(int yTextWidth)
{
	this->yTextWidth = yTextWidth;
}