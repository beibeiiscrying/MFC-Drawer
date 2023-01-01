
// ChildView.cpp : implementation of the CChildView class
//

#include "pch.h"
#include "framework.h"
#include "Drawer.h"
#include "ChildView.h"
#include "afxwin.h"
#include "ProperSet.h"
#include <afxtempl.h>
#include <iostream>
#include <cstringt.h>
#include "Graphic.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CChildView
CChildView::CChildView()
{
	m_GlobalBntColor[0] = RGB(0, 0, 0);
	m_GlobalBntColor[1] = RGB(255, 255, 255);
	m_GlobalBntColor[2] = RGB(0, 0, 0);
	m_GlobalNextStepColor = 0;
	m_GlobalBorderType = 0;
	m_GlobalObjType = 0;
	m_GlobalTextFontType = _T("Comic Sans MS");
	m_GlobalTextUnderline = false;
	m_GlobalTextItalic = false;
	m_GlobalIsBg = false;
	m_GlobalTextWeight = 0;

	m_IsProperSet = FALSE;

	m_Flags = new btnFlags;
	m_PtrFlags[0] = &(m_Flags->m_bNormal);
	m_PtrFlags[1] = &(m_Flags->m_bPan);
	m_PtrFlags[2] = &(m_Flags->Cut);
	m_PtrFlags[3] = &(m_Flags->m_bCircle);
	m_PtrFlags[4] = &(m_Flags->m_bTriangle);
	m_PtrFlags[5] = &(m_Flags->Text);

	EnableToolTips();
	m_toolTip.Create(this);
	m_toolTip.Activate(TRUE);
	m_toolTip.SetDelayTime(150);
}

CChildView::~CChildView()
{
	SafeShapeArrayRemoveALL();
	delete m_Flags;
}

COLORREF CChildView::m_clrColors[5] = {
	RGB(0 , 0 , 0),  //BLACK			預設顏色1
	RGB(255 ,   0 ,   0),  //RED		預設顏色2
	RGB(0 ,   0 , 255),  //BIUE			預設顏色3
	RGB(255 , 255 , 255), // 背景色
	RGB(0, 0, 0),
};

const int CChildView::m_Type[3] = {
	PS_SOLID,
	PS_DASH,
	PS_DOT,
};


COLORREF CChildView::GetGlobalBntColor(int idx)
{
	return m_GlobalBntColor[idx];
}
int CChildView::GetGlobalNextStepColor()
{
	return m_GlobalNextStepColor;
}
int CChildView::GetGlobalBorderType()
{
	return m_GlobalBorderType;
}
int CChildView::GetGlobalObjType()
{
	return m_GlobalObjType;
}
CString CChildView::GetGlobalTextFontType()
{
	return m_GlobalTextFontType;
}
bool CChildView::GetGlobalTextUnderline()
{
	return m_GlobalTextUnderline;
}
bool CChildView::GetGlobalTextItalic()
{
	return m_GlobalTextItalic;
}
bool CChildView::GetGlobalIsBg()
{
	return m_GlobalIsBg;
}
int CChildView::GetGlobalTextWeight()
{
	return m_GlobalTextWeight;
}


void CChildView::SetGlobalBntColor(int idx,COLORREF bntColo)
{
	m_GlobalBntColor[idx] = bntColo;
}
void CChildView::SetGlobalNextStepColor(int nextStepColor)
{
	m_GlobalNextStepColor = nextStepColor;
}
void CChildView::SetGlobalBorderType(int borderType)
{
	m_GlobalBorderType = borderType;
}
void CChildView::SetGlobalObjType(int objType)
{
	m_GlobalObjType = objType;
}
void CChildView::SetGlobalTextFontType(CString textFontType)
{
	m_GlobalTextFontType = textFontType;
}
void CChildView::SetGlobalTextUnderline(bool textUnderline)
{
	m_GlobalTextUnderline = textUnderline;
}
void CChildView::SetGlobalTextItalic(bool textItalic)
{
	m_GlobalTextItalic = textItalic;
}
void CChildView::SetGlobalIsBg(bool isBg)
{
	m_GlobalIsBg = isBg;
}
void CChildView::SetGlobalTextWeight(int textWeight)
{
	m_GlobalTextWeight = textWeight;
}

BEGIN_MESSAGE_MAP(CChildView, CMyScrollView)

	ON_MESSAGE(WM_PROPERSET_APPLY, &CChildView::OnProperSetApply)
	ON_COMMAND(ID_SHAPE_CIRCLE, OnShapeCircle)
	ON_COMMAND(ID_SHAPE_TRIANGLE, OnShapeTriangle)
	ON_COMMAND(ID_GRAPHIC_TEXT, OnShapeText)
	ON_COMMAND_RANGE(ID_COLOR_BLACK, ID_COLOR_BLUE, OnColor)
	ON_UPDATE_COMMAND_UI_RANGE(ID_COLOR_BLACK, ID_COLOR_BLUE, OnUpdateColor)
	ON_COMMAND_RANGE(ID_TYPE_SOLID, ID_TYPE_DOT, OnType)
	ON_UPDATE_COMMAND_UI_RANGE(ID_TYPE_SOLID, ID_TYPE_DOT, OnUpdateType)
	ON_COMMAND(ID_Property, OnProperty)
	ON_COMMAND(ID_VIEW_ZOOMIN, OnViewZoomin)
	ON_COMMAND(ID_VIEW_ZOOMOUT, OnViewZoomout)
	ON_COMMAND(ID_FILE_NEW, &CChildView::OnFileNew)
	ON_COMMAND(ID_FILE_SAVE, &CChildView::OnFileSave)
	ON_COMMAND(ID_FILE_OPEN, &CChildView::OnFileOpen)
	ON_COMMAND(ID_NORMAL, &CChildView::OnNormal)
	ON_COMMAND(ID_Pan, &CChildView::OnPan)
	ON_COMMAND(ID_EDIT_CUT, &CChildView::OnEditCut)
	ON_UPDATE_COMMAND_UI(ID_NORMAL, &CChildView::OnUpdateToolbarBtn)
	ON_UPDATE_COMMAND_UI(ID_Pan, &CChildView::OnUpdateToolbarBtn)
	ON_UPDATE_COMMAND_UI(ID_EDIT_CUT, &CChildView::OnUpdateToolbarBtn)
	ON_UPDATE_COMMAND_UI(ID_SHAPE_CIRCLE, &CChildView::OnUpdateToolbarBtn)
	ON_UPDATE_COMMAND_UI(ID_SHAPE_TRIANGLE, &CChildView::OnUpdateToolbarBtn)
	ON_UPDATE_COMMAND_UI(ID_GRAPHIC_TEXT, &CChildView::OnUpdateToolbarBtn)
	ON_WM_CONTEXTMENU()
	ON_WM_LBUTTONDOWN()
	ON_WM_RBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_SETCURSOR()
	ON_WM_ERASEBKGND()
	ON_WM_LBUTTONUP()
	ON_WM_KEYDOWN()
END_MESSAGE_MAP()

// 屬性套用
LRESULT CChildView::OnProperSetApply(WPARAM wParam, LPARAM lParam) {
	if (pNode != NULL)
	{
		if (pNode->GetType() == CGraphic::ElementType::TEXT) // 文字 
		{
			CText* TextnP = (CText*)pNode;
			pNode->SetBorderColor(m_GlobalBntColor[0]);
			TextnP->SetFontType(m_GlobalTextFontType);
			TextnP->SetUnderline(m_GlobalTextUnderline);
			TextnP->SetItalic(m_GlobalTextItalic);
			TextnP->SetWeight(m_GlobalTextWeight);
			pNode->SetBgColor(m_GlobalBntColor[1]);
			pNode->SetIsBg(m_GlobalIsBg);
		}
		else // 幾何圖形 
		{
			pNode->SetFillColor(m_GlobalBntColor[0]);
			pNode->SetBgColor(m_GlobalBntColor[1]);
			pNode->SetBorderColor(m_GlobalBntColor[2]);
			pNode->SetBorderType(m_Type[m_NextType]);
			pNode->SetIsBg(m_GlobalIsBg);
		}
	}
	else // 全域屬性 
	{
		m_clrColors[m_NextColor] = m_GlobalBntColor[0];
		m_clrColors[3] = m_GlobalBntColor[1];
		m_clrColors[4] = m_GlobalBntColor[2];
		m_NextType = m_GlobalBorderType;
	}

	Invalidate();
	return LRESULT(0);
}

enum class CChildView::BtnID {
	NORMAL = 0, PAN, EDIT_CUT, SHAPE_CIRCLE, SHAPE_TRIANGLE, GRAPHIC_TEXT
};

// 記得清除 new 出來的資源, 避免記憶體溢出
void CChildView::SafeShapeArrayRemoveALL() {
	for (int i = 0; i < m_ShapeArray.GetCount(); i++) {
		delete m_ShapeArray[i];
	}
	m_ShapeArray.RemoveAll();
}

void CChildView::OnFileNew()
{
	SafeShapeArrayRemoveALL();
	bDraw = FALSE;
	Invalidate();
}

void CChildView::OnFileSave()
{
	CFile file;
	bool isOpen = FALSE;
	CString defaultDir = L"";
	CString fileName = L"";
	CString filter = L"draw files(*.dra)|*.dra|All files(*.*)|*.*||"; // p.s. 不可以有空格
	CFileDialog openFileDlg(isOpen, defaultDir, fileName, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, filter, NULL);
	INT_PTR result = openFileDlg.DoModal();
	CString filePath = defaultDir + "\\" + fileName;

	if (result == IDOK) {
		filePath = openFileDlg.GetPathName();
		file.Open(filePath, CFile::modeCreate | CFile::modeWrite);
		CArchive ar(&file, CArchive::store);
		int count = (int)m_ShapeArray.GetCount();
		ar << count;
		if (count > 0)
		{
			CGraphic* p = NULL;
			for (int i = 0; i < count; i++) // 物件屬性序列化
			{
				p = (CGraphic*)m_ShapeArray[i];
				p->Serialize(ar);
			}
		}
		ar.Close();
		file.Flush();
		file.Close();
	}
}

void CChildView::OnFileOpen()
{
	CFile file;
	bool isOpen = TRUE;
	CString defaultDir = L"";
	CString fileName = L"";
	CString filter = _T("dra files(*.dra)|*.dra|All files(*.*)|*.*||");
	CFileDialog openFileDlg(isOpen, defaultDir, fileName, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, filter, NULL);
	INT_PTR result = openFileDlg.DoModal();
	CString filePath = defaultDir + "\\" + fileName;

	if (result == IDOK) {
		filePath = openFileDlg.GetPathName();
		file.Open(filePath, CFile::modeReadWrite);
		CArchive ar(&file, CArchive::load);
		int count;
		ar >> count;
		int type;
		CGraphic* p = NULL;
		if (count > 0)
		{
			SafeShapeArrayRemoveALL();
			for (int i = 0; i < count; i++) // 物件屬性反序列化 -> 新建物件 -> 存入物件陣列 (載入)
			{
				ar >> type;
				switch (type)
				{
				case 0:
					p = new CTriangle();
					p->Serialize(ar);
					break;
				case 1:
					p = new CCircle();
					p->Serialize(ar);
					break;
				case 2:
					p = new CText();
					((CText*)p)->Serialize(ar);
					break;
				}
				m_ShapeArray.Add(p);
			}
			Invalidate();
		}
		ar.Close();
		file.Flush();
		file.Close();
	}
}

// 檢查物件選取框
void CChildView::CheckTracker()
{
	if (pNode == NULL) { return; }
	CRect rect = pNode->GetTrackerRect();
	m_Tracker.m_rect.SetRect(rect.left, rect.top, rect.right, rect.bottom);
	LPtoDP(m_Tracker.m_rect);

	m_Tracker.m_rect.NormalizeRect();
	m_Tracker.m_nStyle = CRectTracker::dottedLine | CRectTracker::resizeOutside;
	m_Tracker.Track(this, FALSE);
	Invalidate();
}

void CChildView::SetToolBarBtnFlag(BtnID btnId) {// NORMAL, m_bPan, EDIT_CUT, SHAPE_CIRCLE, SHAPE_TRIANGLE, GRAPHIC_TEXT
	m_bLButtonDown = FALSE;
	for (int i = 0; i < m_Flags->len; i++) {
		if (i == (int)btnId) { continue; }
		*(m_PtrFlags[i]) = false;
	}
	*(m_PtrFlags[(int)btnId]) = true;
	if (btnId > BtnID::EDIT_CUT) { m_NumOfShape = ((int)btnId) % 3; }
	else { m_NumOfShape = 4; }
}

BOOL CChildView::GetToolBarBtnFlag(BtnID btnId) {// NORMAL, m_bPan, EDIT_CUT, SHAPE_CIRCLE, SHAPE_TRIANGLE, GRAPHIC_TEXT
	return *(m_PtrFlags[(int)btnId]);
}

void CChildView::OnNormal() {
	SetToolBarBtnFlag(BtnID::NORMAL);
}

void CChildView::OnPan() {
	SetToolBarBtnFlag(BtnID::PAN);
}

void CChildView::OnEditCut() {
	SetToolBarBtnFlag(BtnID::EDIT_CUT);
}

void CChildView::OnShapeCircle() {
	SetToolBarBtnFlag(BtnID::SHAPE_CIRCLE);
}

void CChildView::OnShapeTriangle() {
	SetToolBarBtnFlag(BtnID::SHAPE_TRIANGLE);
}

void CChildView::OnShapeText() {
	SetToolBarBtnFlag(BtnID::GRAPHIC_TEXT);
}

void CChildView::OnUpdateToolbarBtn(CCmdUI* pCmdUI) {
	int ids[] = { ID_NORMAL, ID_Pan, ID_EDIT_CUT, ID_SHAPE_CIRCLE, ID_SHAPE_TRIANGLE, ID_GRAPHIC_TEXT };
	int idsLen = sizeof(ids) / sizeof(ids[0]);
	int idx = 0;
	for (; idx < idsLen && (pCmdUI->m_nID != ids[idx]); idx++);
	pCmdUI->SetCheck(GetToolBarBtnFlag((BtnID)idx));
}
void CChildView::OnLButtonDown(UINT nFlags, CPoint point) {
	CClientDC dc(this);
	CPoint pntLogical = point;
	OnPrepareDC(&dc);
	DPtoLP(&pntLogical);
	int graX = pntLogical.x;
	int graY = pntLogical.y;
	int xWidth = 100;
	int yWidth = 100;
	int borderWidth = 1;
	int xTextWidth = 112;
	int yTextWidth = 16;
	int borderType = m_Type[m_NextType];
	bool underline = m_GlobalTextUnderline;
	bool italic = m_GlobalTextItalic;
	int weight = m_GlobalTextWeight;
	CString fontType = m_GlobalTextFontType;
	CString textContent = _T("MFC Assignment");
	COLORREF borderColor = m_GlobalBntColor[2];
	COLORREF bgColor = m_GlobalBntColor[1];
	COLORREF fillColor = m_clrColors[m_NextColor];
	COLORREF textFillColor = m_clrColors[3];
	m_bLButtonDown = TRUE;

	// 是否是圖形繪畫
	if (m_NumOfShape < 3)
	{ // yse
		switch (m_NumOfShape)
		{
		case 0: // CCircle
		{
			CCircle* p = new CCircle(graX, graY, xWidth, yWidth, borderWidth, borderType, borderColor, fillColor, bgColor);
			p->SetIsBg(m_GlobalIsBg);
			m_ShapeArray.Add(p);
			break;
		}
		case 1: // CTriangle
		{
			CTriangle* p = new CTriangle(graX, graY, xWidth, yWidth, borderWidth, borderType, borderColor, fillColor, bgColor);
			p->SetIsBg(m_GlobalIsBg);
			m_ShapeArray.Add(p);
			break;
		}
		case 2: // CText
		{
			borderColor = m_clrColors[m_NextColor];
			CText* p = new CText(graX, graY, textContent, xTextWidth, yTextWidth, borderWidth, borderType, borderColor, textFillColor, bgColor, fontType, underline, italic, weight);
			p->SetIsBg(m_GlobalIsBg);
			m_ShapeArray.Add(p);
			break;
		}
		}
		bDraw = FALSE;
		Invalidate();
		return;
	}
	int count = (int)m_ShapeArray.GetCount();
	m_HitNum = m_Tracker.HitTest(point);
	bool isEmptyPt = TRUE;
	// 是否擊中物件選框的縮放點
	if (m_HitNum >= 0 && m_HitNum < 8)
	{
		if (pNode != NULL)
		{
			oldMousePoint = point;
			m_Tracker.Track(this, point, FALSE);
			bDraw = TRUE;
			Invalidate();
			return;
		}
	}
	else {
		bDraw = FALSE;
		pNode = NULL;
	}
	for (int i = 0; i < count; i++)
	{
		pNode = (CGraphic*)m_ShapeArray[i];
		if (pNode->IsMatched(pntLogical))
		{
			isEmptyPt = FALSE;
			if (GetToolBarBtnFlag(BtnID::EDIT_CUT))
			{
				delete m_ShapeArray[i];
				m_ShapeArray.RemoveAt(i);
				Invalidate();
				return;
			}
			bDraw = TRUE;
			GraXCount = pntLogical.x - pNode->GetX();
			GraYCount = pntLogical.y - pNode->GetY();
			CRect rect = pNode->GetTrackerRect();
			m_Tracker.m_rect.SetRect(rect.left, rect.top, rect.right, rect.bottom);
			LPtoDP(m_Tracker.m_rect);
			m_Tracker.m_rect.NormalizeRect();
			m_Tracker.m_nStyle = CRectTracker::dottedLine | CRectTracker::resizeOutside;
			m_Tracker.Track(this, FALSE);
			Invalidate();
			m_bLButtonDown = TRUE;
			return;
		}
		else
		{
			bDraw = FALSE;
		}
	}
	pNode = NULL;
	if (isEmptyPt) {
		oldMousePoint = point;
	}
	if (m_Flags->m_bNormal) {
		CRectTracker  temp;
		temp.TrackRubberBand(this, point, TRUE);
		temp.m_rect.NormalizeRect();
	}
	Invalidate();
}

void CChildView::OnRButtonDown(UINT nFlags, CPoint point)
{
	m_bRButtonDown = true;
	CPoint pntLogical = point;
	DPtoLP(&pntLogical);
	int count = (int)m_ShapeArray.GetCount();
	for (int i = 0; i < count; i++)
	{
		pNode = (CGraphic*)m_ShapeArray[i];
		if (pNode->IsMatched(pntLogical))
		{
			m_HitNum = m_Tracker.HitTest(point);
			if (m_HitNum >= 0 && m_HitNum < 8)
			{
				if (pNode != NULL)
				{
					oldMousePoint = point;
					m_Tracker.Track(this, point, FALSE);
					bDraw = TRUE;
					Invalidate();
				}
			}
			if (pNode == NULL) { continue; }
			bDraw = TRUE;
			GraXCount = pntLogical.x - pNode->GetX();
			GraYCount = pntLogical.y - pNode->GetY();
			CRect rect = pNode->GetTrackerRect();
			m_Tracker.m_rect.SetRect(rect.left, rect.top, rect.right, rect.bottom);
			LPtoDP(m_Tracker.m_rect);
			m_Tracker.m_rect.NormalizeRect();
			m_Tracker.m_nStyle = CRectTracker::dottedLine | CRectTracker::resizeOutside;
			m_Tracker.Track(this, FALSE);
			Invalidate();

			CMenu menu;
			menu.LoadMenu(IDR_CONTEXTMENU);
			if (menu == NULL)
			{
				return;
			}

			/* 修改 meun 的 顏色文字 -> 顏色呈現框 程式片段 */
			CMenu* pContextMenu = menu.GetSubMenu(0);
			for (int i = 0; i < 3; i++)
				pContextMenu->ModifyMenuW(static_cast<__int64>(ID_COLOR_BLACK) + static_cast<__int64>(i), MF_BYCOMMAND | MF_OWNERDRAW, static_cast<__int64>(ID_COLOR_BLACK) + static_cast<__int64>(i));
			GetCursorPos(&point);
			pContextMenu->TrackPopupMenu(TPM_TOPALIGN | TPM_LEFTALIGN | TPM_LEFTBUTTON | TPM_RIGHTBUTTON, point.x, point.y, AfxGetMainWnd());
			// -> CChildView::OnUpdateColor

			Invalidate();
			return;
		}
	}
	pNode = NULL;
	bDraw = false;
	Invalidate();
	CMenu menu;
	menu.LoadMenu(IDR_CONTEXTMENU);
	if (menu == NULL)
	{
		return;
	}

	/* 修改 meun 的 顏色文字 -> 顏色呈現框 程式片段 */
	CMenu* pContextMenu = menu.GetSubMenu(0);
	for (int i = 0; i < 3; i++)
		pContextMenu->ModifyMenuW(static_cast<__int64>(ID_COLOR_BLACK) + static_cast<__int64>(i), MF_BYCOMMAND | MF_OWNERDRAW, static_cast<__int64>(ID_COLOR_BLACK) + static_cast<__int64>(i));
	GetCursorPos(&point);
	pContextMenu->TrackPopupMenu(TPM_TOPALIGN | TPM_LEFTALIGN | TPM_LEFTBUTTON | TPM_RIGHTBUTTON, point.x, point.y, AfxGetMainWnd());
	// -> CChildView::OnUpdateColor

	Invalidate();
}


void CChildView::OnLButtonUp(UINT nFlags, CPoint point)
{

	m_bLButtonDown = FALSE;
	CView::OnLButtonUp(nFlags, point);
}

void CChildView::OnMouseMove(UINT nFlags, CPoint point)
{
	CPoint pntLogical = point;
	DPtoLP(&pntLogical);
	CPoint OldpntLogical = oldMousePoint;
	DPtoLP(&OldpntLogical);
	if (m_bLButtonDown && GetToolBarBtnFlag(BtnID::PAN) && !(m_HitNum >= 0 && m_HitNum < 8))
	{
		if (pNode != NULL) // 選中物件時 移動物件
		{
			pNode->SetX(pntLogical.x - GraXCount);
			pNode->SetY(pntLogical.y - GraYCount);
			CheckTracker();
			Invalidate();
		}
		else {	// 未選中物件時 移動畫布
			CPoint pt = GetScrollPosition();
			BOOL bHasHorzBar = false, bHasVertBar = false;
			CheckScrollBars(bHasHorzBar, bHasVertBar);
			CPoint newpt;
			if (bHasHorzBar && bHasVertBar) {
				newpt = CPoint((pt.x + (pntLogical.x - OldpntLogical.x)), (pt.y + (pntLogical.y - OldpntLogical.y)));
			}
			else if (bHasHorzBar) {
				newpt = CPoint((pt.x + (pntLogical.x - OldpntLogical.x)), pt.y);
			}
			else if (bHasVertBar) {
				newpt = CPoint(pt.x, (pt.y + (pntLogical.y - OldpntLogical.y)));
			}
			else {
				newpt = pt;
			}
			ScrollToPosition(newpt);
			oldMousePoint = point;
			Invalidate();
		}
	}
	if (m_HitNum != -1 && m_HitNum >= 0 && m_HitNum < 8 && pNode != NULL) {	// 對物件縮放點調整放開後進入
		m_bLButtonDown = FALSE;
		int xsary[] = { 1, -1, 1, -1 };
		int ysary[] = { 1, -1, -1, 1 };
		int idx = -1;

		if (m_HitNum == 2 || m_HitNum == 5 || m_HitNum == 6) { idx = 0; }
		else if (m_HitNum == 0 || m_HitNum == 4 || m_HitNum == 7) { idx = 1; }
		else if (m_HitNum == 1) { idx = 2; }
		else if (m_HitNum == 3) { idx = 3; }

		/* m_HitNum:
			0     4     1
			   _______
			  |       |
			7 |       | 5 
			  |_______|
            
			3     6     2
		
		*/


		// 物件縮放的設定調整
		if (pNode->GetType() == CGraphic::ElementType::TEXT)	// 文字圖處理
		{
			CText* XText;
			XText = (CText*)pNode;

			// 相對位置調整演算法  
			/* 四面(x,y)相對差值 */
			int xAry[4] = { (pntLogical.x - XText->GetX()), (XText->GetX() - pntLogical.x),
							(pntLogical.x - XText->GetX()), (XText->GetX() - pntLogical.x) };
			int yAry[4] = { (pntLogical.y - XText->GetY()), (XText->GetY() - pntLogical.y),
							(XText->GetY() - pntLogical.y), (pntLogical.y - XText->GetY()) };

			int tpX = XText->GetX(), tpY = XText->GetY(), tpTX = XText->GetXTextWidth(), tpTY = XText->GetYTextWidth();
			
			//  位置調整
			if (idx >= 0 && idx < 4) {
				GraCountX = xAry[idx];
				GraCountY = yAry[idx];
				XText->SetX((m_HitNum == 0 || m_HitNum == 3 || m_HitNum == 7) ? XText->GetX() + xsary[idx] * GraCountX : XText->GetX()); // 是否為左側 需要校正位置
				XText->SetY((m_HitNum == 0 || m_HitNum == 1 || m_HitNum == 4) ? XText->GetY() + ysary[idx] * GraCountY : XText->GetY()); // 是否為上側 需要校正位置
			}

			// 長寬設定
			XText->SetXTextWidth((m_HitNum == 1 || m_HitNum == 2 || m_HitNum == 5) ? GraCountX :
				(m_HitNum == 0 || m_HitNum == 3 || m_HitNum == 7) ? XText->GetXTextWidth() + GraCountX :
				XText->GetXTextWidth());
			XText->SetYTextWidth((m_HitNum == 2 || m_HitNum == 3 || m_HitNum == 6) ? GraCountY :
				(m_HitNum == 0 || m_HitNum == 1 || m_HitNum == 4) ? XText->GetYTextWidth() + GraCountY :
				XText->GetYTextWidth());


			if (XText->GetXTextWidth() < 0 || XText->GetYTextWidth() < 0) {
				XText->SetX(tpX);
				XText->SetY(tpY);
				XText->SetXTextWidth(1);
				XText->SetYTextWidth(1);
			}
		}
		else // 幾何圖處理
		{	
			// 相對位置調整演算法  
			/* 四面(x,y)相對差值 */
			int xAry[4] = { (pntLogical.x - OldpntLogical.x) , (OldpntLogical.x - pntLogical.x),
							(pntLogical.x - OldpntLogical.x), (OldpntLogical.x - pntLogical.x) };
			int yAry[4] = { (pntLogical.y - OldpntLogical.y), (OldpntLogical.y - pntLogical.y),
							(OldpntLogical.y - pntLogical.y), (pntLogical.y - OldpntLogical.y) };

			//  位置調整
			if (idx >= 0 && idx < 4) {
				GraCountX = xAry[idx];
				GraCountY = yAry[idx];
				pNode->SetX(pNode->GetX() + (xsary[idx] * GraCountX / 2));
				pNode->SetY(pNode->GetY() + (ysary[idx] * GraCountY / 2));
			}

			// 長寬設定
			if (pNode->GetXWidth() < 0) { GraCountX = -GraCountX; }
			if (pNode->GetYWidth() < 0) { GraCountY = -GraCountY; }
			pNode->SetXWidth(pNode->GetXWidth() + GraCountX);
			pNode->SetYWidth(pNode->GetYWidth() + GraCountY);
		}

		GraCountX = 0;
		GraCountY = 0;
		m_HitNum = -1;

		CheckTracker();
		Invalidate();
		return;
	}

	CView::OnMouseMove(nFlags, point);
}

BOOL CChildView::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message)
{
	if (m_Tracker.SetCursor(pWnd, nHitTest))
		return TRUE;

	BITMAP bmpBack;
	m_pBitmap->GetBitmap(&bmpBack);

	CRect r(0, 0, bmpBack.bmWidth, bmpBack.bmHeight);
	CRect rect(0, 0, 0, 0);
	GetDC()->GetClipBox(&rect);
	POINT p;
	GetCursorPos(&p);
	ScreenToClient(&p);
	BOOL w = false, h = false;
	CheckScrollBars(h, w);

	if (p.x > r.right || p.y > r.bottom) { return CView::OnSetCursor(pWnd, nHitTest, message); }

	if (m_NumOfShape < 2)
	{
		if (w && p.x > (rect.right - 3)) { return CView::OnSetCursor(pWnd, nHitTest, message); }
		if (h && p.y > (rect.bottom - 3)) { return CView::OnSetCursor(pWnd, nHitTest, message); }
		::SetCursor(LoadCursor(NULL, IDC_CROSS));
		return TRUE;
	}
	if (m_NumOfShape == 2)
	{
		if (w && p.x > (rect.right - 3)) { return CView::OnSetCursor(pWnd, nHitTest, message); }
		if (h && p.y > (rect.bottom - 3)) { return CView::OnSetCursor(pWnd, nHitTest, message); }
		::SetCursor(LoadCursor(NULL, IDC_IBEAM));
		return TRUE;
	}
	if (GetToolBarBtnFlag(BtnID::PAN)) {
		if (w && p.x > (rect.right - 3)) { return CView::OnSetCursor(pWnd, nHitTest, message); }
		if (h && p.y > (rect.bottom - 3)) { return CView::OnSetCursor(pWnd, nHitTest, message); }
		::SetCursor(LoadCursor(NULL, IDC_SIZEALL));
		return TRUE;
	}

	return CView::OnSetCursor(pWnd, nHitTest, message);
}

void CChildView::OnDraw(CDC* pDC)
{
	CDC* pDoc = (CDC*)m_ShapeArray.GetData();
	int count = (int)m_ShapeArray.GetCount();
	if (bDraw)
	{
		m_Tracker.Draw(pDC);
		if (!m_bRButtonDown && !m_bLButtonDown && !m_IsProperSet) {
			CheckTracker();
		}
		else {
			m_bRButtonDown = false;
		}
	}
	if (count > 0)
	{
		CGraphic* p = NULL;
		for (int i = 0; i < count; i++)
		{
			p = (CGraphic*)m_ShapeArray[i];
			CBrush brush(p->GetBgColor()), * pOldBrush;
			pOldBrush = (CBrush*)pDC->SelectObject(&brush);
			CPen pen, * pOldPen;
			pen.CreatePen(0, 0, p->GetBgColor());
			pOldPen = (CPen*)pDC->SelectObject(&pen);
			if (p->GetType() == CGraphic::ElementType::TEXT)
			{
				CText* XText;
				XText = (CText*)p;
				if (p->GetIsBg()) {
					pDC->Rectangle(XText->GetX(), XText->GetY(), XText->GetX() + XText->GetXTextWidth(), XText->GetY() + XText->GetYTextWidth());
				}
				p->Draw(pDC);
			}
			else
			{
				if (p->GetIsBg()) {
					pDC->Rectangle(p->GetX() - p->GetXWidth() / 2, p->GetY() - p->GetYWidth() / 2, p->GetX() + p->GetXWidth() / 2, p->GetY() + p->GetYWidth() / 2);
				}
				p->Draw(pDC);
			}

			pDC->SelectObject(pOldBrush);
			pDC->SelectObject(pOldPen);
		}
		return;
	}
}

void CChildView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if (pNode != NULL)
	{
		if (nChar == VK_DELETE)
		{
			CGraphic* p;
			int count = (int)m_ShapeArray.GetCount();
			for (int i = 0; i < count; i++)
			{
				p = (CGraphic*)m_ShapeArray[i];
				if (p == pNode)
				{
					delete m_ShapeArray[i];
					m_ShapeArray.RemoveAt(i);
					bDraw = FALSE;
					Invalidate();
					return;
				}
			}
		}
		else if (nChar == VK_RIGHT)
		{
			pNode->SetX(pNode->GetX() + 1);
			CText* XText;
			XText = (CText*)pNode;
			if (pNode->GetType() == CGraphic::ElementType::TEXT)
				m_Tracker.m_rect.SetRect((XText->GetX()), (XText->GetY()), (XText->GetX() + XText->GetXTextWidth()), (XText->GetY() + XText->GetYTextWidth()));
			else
				m_Tracker.m_rect.SetRect((pNode->GetX() - pNode->GetXWidth() / 2), (pNode->GetY() - pNode->GetYWidth() / 2), (pNode->GetX() + pNode->GetXWidth() / 2), (pNode->GetY() + pNode->GetYWidth() / 2));
			LPtoDP(m_Tracker.m_rect);
			Invalidate();
		}
		else if (nChar == VK_LEFT)
		{
			pNode->SetX(pNode->GetX() - 1);
			CText* XText;
			XText = (CText*)pNode;
			if (pNode->GetType() == CGraphic::ElementType::TEXT)
				m_Tracker.m_rect.SetRect((XText->GetX()), (XText->GetY()), (XText->GetX() + XText->GetXTextWidth()), (XText->GetY() + XText->GetYTextWidth()));
			else
				m_Tracker.m_rect.SetRect((pNode->GetX() - pNode->GetXWidth() / 2), (pNode->GetY() - pNode->GetYWidth() / 2), (pNode->GetX() + pNode->GetXWidth() / 2), (pNode->GetY() + pNode->GetYWidth() / 2));
			LPtoDP(m_Tracker.m_rect);
			Invalidate();
		}
		else if (nChar == VK_UP)
		{
			pNode->SetY(pNode->GetY() - 1);
			CText* XText;
			XText = (CText*)pNode;
			if (pNode->GetType() == CGraphic::ElementType::TEXT)
				m_Tracker.m_rect.SetRect((XText->GetX()), (XText->GetY()), (XText->GetX() + XText->GetXTextWidth()), (XText->GetY() + XText->GetYTextWidth()));
			else
				m_Tracker.m_rect.SetRect((pNode->GetX() - pNode->GetXWidth() / 2), (pNode->GetY() - pNode->GetYWidth() / 2), (pNode->GetX() + pNode->GetXWidth() / 2), (pNode->GetY() + pNode->GetYWidth() / 2));
			LPtoDP(m_Tracker.m_rect);
			Invalidate();
		}
		else if (nChar == VK_DOWN)
		{
			pNode->SetY(pNode->GetY() + 1);
			CText* XText;
			XText = (CText*)pNode;
			if (pNode->GetType() == CGraphic::ElementType::TEXT)
				m_Tracker.m_rect.SetRect((XText->GetX()), (XText->GetY()), (XText->GetX() + XText->GetXTextWidth()), (XText->GetY() + XText->GetYTextWidth()));
			else
				m_Tracker.m_rect.SetRect((pNode->GetX() - pNode->GetXWidth() / 2), (pNode->GetY() - pNode->GetYWidth() / 2), (pNode->GetX() + pNode->GetXWidth() / 2), (pNode->GetY() + pNode->GetYWidth() / 2));
			LPtoDP(m_Tracker.m_rect);
			Invalidate();
		}
		Invalidate();
	}

	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}

BOOL CChildView::PreCreateWindow(CREATESTRUCT& cs)
{
	if (!CWnd::PreCreateWindow(cs))
		return FALSE;

	cs.dwExStyle |= WS_EX_CLIENTEDGE;
	cs.style &= ~WS_BORDER;
	cs.lpszClass = AfxRegisterWndClass(CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS,
		::LoadCursor(nullptr, IDC_ARROW), reinterpret_cast<HBRUSH>(COLOR_WINDOW + 1), nullptr);

	return TRUE;
}

// 右鍵Menu 選擇顏色
void CChildView::OnColor(UINT nID)
{
	int m_CurrentColor = nID - ID_COLOR_BLACK;
	m_GlobalBntColor[0] = m_clrColors[m_CurrentColor];
	m_GlobalBntColor[2] = m_clrColors[4];
	if (pNode != NULL)
	{
		if (pNode->GetType() == CGraphic::ElementType::TEXT)
		{
			pNode->SetBorderColor(m_GlobalBntColor[0]);
		}
		else
		{
			pNode->SetFillColor(m_GlobalBntColor[0]);
			pNode->SetBorderColor(m_GlobalBntColor[1]);
		}
		Invalidate();
	}
	else {
		m_NextColor = m_CurrentColor;
	}
	m_GlobalBntColor[0] = m_clrColors[m_NextColor];
	m_GlobalBntColor[2] = m_clrColors[4];
}

// "右鍵選單 Menu" 的重繪 顏色文字 -> 顏色呈現框
void CChildView::OnUpdateColor(CCmdUI* pCmdUI)
{
	if (pNode != NULL) {
		if (pNode->GetType() == CGraphic::ElementType::TEXT) { m_GlobalBntColor[0] = pNode->GetBorderColor(); }
		else { m_GlobalBntColor[0] = pNode->GetFillColor(); }
	}

	if (m_NextColor < 3 && m_GlobalBntColor[0] == m_clrColors[m_NextColor]) {
		pCmdUI->SetCheck((int)pCmdUI->m_nID - ID_COLOR_BLACK == m_NextColor); // -> CMainFrame::OnDrawItem
		return;
	}

	for (int i = 0; i < 3; i++)
	{
		if (m_GlobalBntColor[0] == m_clrColors[i])
		{
			int m_CurrentColor = i;
			pCmdUI->SetCheck((int)pCmdUI->m_nID - ID_COLOR_BLACK == m_CurrentColor); // -> CMainFrame::OnDrawItem
			return;
		}
	}

}

// 右鍵Menu 選擇框線
void CChildView::OnType(UINT nID)
{
	int m_CurrentType = nID - ID_TYPE_SOLID;
	if (pNode != NULL)
	{
		pNode->SetBorderType(m_Type[m_CurrentType]);
		Invalidate();
	}
	else
	{
		m_NextType = m_CurrentType;
	}
	m_GlobalBorderType = m_NextType;
}

// "右鍵選單 Menu" 的重繪 框線選項
void CChildView::OnUpdateType(CCmdUI* pCmdUI)
{
	int m_CurrentType = m_GlobalBorderType;
	if (pNode != NULL)
	{
		for (int i = 0; i < 3; i++)
		{
			if (pNode->GetBorderType() == m_Type[i])
				m_CurrentType = i;
		}
	}
	pCmdUI->SetCheck((int)pCmdUI->m_nID - ID_TYPE_SOLID == m_CurrentType);
}

// "右鍵選單 Menu" 的屬性按下
void CChildView::OnProperty()
{
	m_IsProperSet = TRUE;
	int oldWeight = m_GlobalTextWeight;
	bool oldUnderline = m_GlobalTextUnderline;
	bool oldItalic = m_GlobalTextItalic;
	CString oldFontType = m_GlobalTextFontType;
	int oldNextType = m_NextType;
	int	oldNextColor = m_NextColor;
	bool oldIsBg = m_GlobalIsBg;
	// 抓取物件屬性
	if (pNode != NULL)
	{
		if (pNode->GetType() == CGraphic::ElementType::TEXT)
		{
			CText* TextnP = (CText*)pNode;
			m_GlobalTextFontType = TextnP->GetFontType();
			m_GlobalTextWeight = TextnP->GetWeight();
			m_GlobalTextUnderline = TextnP->GetUnderline();
			m_GlobalTextItalic = TextnP->GetItalic();
			m_GlobalBntColor[0] = pNode->GetBorderColor();
		}
		else {
			m_GlobalBntColor[0] = pNode->GetFillColor();
			m_GlobalBntColor[2] = pNode->GetBorderColor();
		}
		m_GlobalBntColor[1] = pNode->GetBgColor();
		m_GlobalIsBg = pNode->GetIsBg();
		m_GlobalBorderType = pNode->GetBorderType();
		m_GlobalObjType = (int)pNode->GetType();
	}
	else // 抓取全域屬性
	{
		m_GlobalBorderType = m_NextType;
		m_GlobalObjType = 4;
		m_GlobalBntColor[0] = m_clrColors[m_NextColor];
		m_GlobalBntColor[1] = m_clrColors[3];
		m_GlobalBntColor[2] = m_clrColors[4];
	}
	CProperSet propSet;
	int result = (int)propSet.DoModal();
	if (result == IDOK)
	{
		m_NextType = m_GlobalBorderType;
		// 設定物件屬性
		if (pNode != NULL)
		{
			if (pNode->GetType() == CGraphic::ElementType::TEXT)
			{
				CText* TextnP = (CText*)pNode;
				pNode->SetBorderColor(m_GlobalBntColor[0]);
				TextnP->SetFontType(m_GlobalTextFontType);
				TextnP->SetUnderline(m_GlobalTextUnderline);
				TextnP->SetItalic(m_GlobalTextItalic);
				TextnP->SetWeight(m_GlobalTextWeight);
				pNode->SetBgColor(m_GlobalBntColor[1]);
				pNode->SetIsBg(m_GlobalIsBg);

				m_GlobalTextWeight = oldWeight;
				m_GlobalTextUnderline = oldUnderline;
				m_GlobalTextItalic = oldItalic;
				m_NextType = oldNextType;
				m_NextColor = oldNextColor;
				m_GlobalBntColor[0] = m_clrColors[m_NextColor];
				m_GlobalBntColor[1] = m_clrColors[3];
				m_GlobalBntColor[2] = m_clrColors[4];
				m_GlobalTextFontType = oldFontType;
			}
			else
			{
				pNode->SetBorderColor(m_GlobalBntColor[2]);
				pNode->SetFillColor(m_GlobalBntColor[0]);
				pNode->SetBgColor(m_GlobalBntColor[1]);
				pNode->SetBorderType(m_Type[m_NextType]);
				pNode->SetIsBg(m_GlobalIsBg);

				m_GlobalTextWeight = oldWeight;
				m_GlobalTextUnderline = oldUnderline;
				m_GlobalTextItalic = oldItalic;
				m_NextType = oldNextType;
				m_NextColor = oldNextColor;
				m_GlobalBntColor[0] = m_clrColors[m_NextColor];
				m_GlobalBntColor[1] = m_clrColors[3];
				m_GlobalBntColor[2] = m_clrColors[4];
				m_GlobalTextFontType = oldFontType;
				m_GlobalIsBg = oldIsBg;
			}
		}
		else { // 設定全域屬性
			m_clrColors[m_NextColor] = m_GlobalBntColor[0];
			m_clrColors[3] = m_GlobalBntColor[1];
			m_clrColors[4] = m_GlobalBntColor[2];
		}

		Invalidate();
	}
	else { // (取消) 復原屬性
		m_GlobalTextWeight = oldWeight;
		m_GlobalTextUnderline = oldUnderline;
		m_GlobalTextItalic = oldItalic;
		m_NextType = oldNextType;
		m_NextColor = oldNextColor;
		m_GlobalBntColor[0] = m_clrColors[m_NextColor];
		m_GlobalBntColor[1] = m_clrColors[3];
		m_GlobalBntColor[2] = m_clrColors[4];
		m_GlobalTextFontType = oldFontType;
		m_GlobalIsBg = oldIsBg;
	}
	m_IsProperSet = FALSE;
	m_bLButtonDown = FALSE;
}


void CChildView::OnViewZoomin()
{
	SetZoomScale(m_ZoomFactor + 1.0f);
	if (pNode != NULL) { CheckTracker(); }
}

void CChildView::OnViewZoomout()
{
	SetZoomScale(m_ZoomFactor - 1.0f);
	if (pNode != NULL) { CheckTracker(); }
}

void CChildView::OnPaint()
{
	CPaintDC dc(this);
}

void CChildView::OnSize(UINT nType, int cx, int cy)
{
	CDC* pDC = GetDC();
	//設定brush為希望的背景顏色
	CBrush backBrush(RGB(220, 233, 235));
	//儲存舊的brush
	CBrush* pOldBrush = pDC->SelectObject(&backBrush);
	CRect rect;
	pDC->GetClipBox(&rect);
	if (rect.Width() == 0 && rect.Height() == 0) { return; }

	CPoint viewportOrg = pDC->GetViewportOrg();
	m_PdcMemory->SetViewportOrg(viewportOrg);

	CBitmap* pOldBitmap = m_PdcMemory->SelectObject(m_pBitmap);

	BITMAP bmpBack;
	m_pBitmap->GetBitmap(&bmpBack);

	CRect r(0, 0, bmpBack.bmWidth, bmpBack.bmHeight);
	m_PdcMemory->IntersectClipRect(r);
	CBrush backgroundBrush((COLORREF) ::GetSysColor(COLOR_WINDOW));
	CBrush* pBackBrush = m_PdcMemory->SelectObject(&backgroundBrush);
	m_PdcMemory->PatBlt(r.left, r.top,
		r.Width(), r.Height(),
		PATCOPY);

	//畫需要的區域
	pDC->PatBlt(rect.left, rect.top, rect.Width(), rect.Height(), PATCOPY);
	pDC->BitBlt(r.left, r.top, r.Width(), r.Height(), m_PdcMemory, r.left, r.top, SRCCOPY);

	pDC->SelectObject(pOldBrush);
	Invalidate(FALSE);
}

BOOL CChildView::OnEraseBkgnd(CDC* pDC) {
	//設定brush為希望的背景顏色
	CBrush backBrush(RGB(220, 233, 235));

	//儲存舊的brush
	CBrush* pOldBrush = pDC->SelectObject(&backBrush);
	CRect rect;
	pDC->GetClipBox(&rect);

	CPoint viewportOrg = pDC->GetViewportOrg();
	m_PdcMemory->SetViewportOrg(viewportOrg);

	CBitmap* pOldBitmap = m_PdcMemory->SelectObject(m_pBitmap);

	BITMAP bmpBack;
	m_pBitmap->GetBitmap(&bmpBack);

	if (bmpBack.bmWidth == 1 && bmpBack.bmHeight == 1 && m_pBitmap != NULL) {
		delete m_pBitmap;
		m_pBitmap = NULL;
		m_pBitmap = new CBitmap();
		m_pBitmap->CreateCompatibleBitmap(pDC, rect.right,
			rect.bottom);

		m_pBitmap->GetBitmap(&bmpBack);


		m_Layout.cx = rect.right;
		m_Layout.cy = rect.bottom;
		m_Page.cx = m_Layout.cx / 2;
		m_Page.cy = m_Layout.cy / 2;
		m_Line.cx = m_Layout.cx / 50;
		m_Line.cy = m_Layout.cy / 50;
		SetScrollSizes(MM_TEXT, m_Layout, m_Page, m_Line);

		Invalidate();
	}
	return FALSE;
}

COLORREF CChildView::GetClrColor(int index)
{
	return  m_clrColors[index];
}