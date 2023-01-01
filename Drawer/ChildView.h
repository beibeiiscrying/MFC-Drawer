
// ChildView.h : interface of the CChildView class
//


#pragma once
#include "MyScrollView.h"
#include "Graphic.h"
#include "Shape.h"
#include "Text.h"
#include "Triangle.h"
#include "Circle.h"

// CChildView window


typedef struct btnFlags {

	bool m_bNormal = false;
	bool m_bPan = false;
	bool Cut = false;
	bool m_bCircle = false;
	bool m_bTriangle = false;
	bool Text = false;
	int len = 6;
}btnFlags;



class CChildView : public CMyScrollView
{
	// Construction
public:
	CChildView();

	// Attributes
public:
	// Operations
	COLORREF GetGlobalBntColor(int idx);
	int GetGlobalNextStepColor();
	int GetGlobalBorderType();
	int GetGlobalObjType();
	CString GetGlobalTextFontType();
	bool GetGlobalTextUnderline();
	bool GetGlobalTextItalic();
	bool GetGlobalIsBg();
	int GetGlobalTextWeight();


	void SetGlobalBntColor(int idx, COLORREF bntColo);
	void SetGlobalNextStepColor(int nextStepColor);
	void SetGlobalBorderType(int borderType);
	void SetGlobalObjType(int objType);
	void SetGlobalTextFontType(CString textFontType);
	void SetGlobalTextUnderline(bool textUnderline);
	void SetGlobalTextItalic(bool textItalic);
	void SetGlobalIsBg(bool isBg);
	void SetGlobalTextWeight(int textWeight);
public:

	// Overrides
protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);


	// Implementation
public:
	virtual ~CChildView();

	// Generated message map functions
protected:
	enum class BtnID;

	COLORREF m_GlobalBntColor[3];
	int m_GlobalNextStepColor;
	int m_GlobalBorderType;
	int m_GlobalObjType;
	CString m_GlobalTextFontType;
	bool m_GlobalTextUnderline;
	bool m_GlobalTextItalic;
	bool m_GlobalIsBg;
	int m_GlobalTextWeight;

	static COLORREF m_clrColors[5];
	static const int   m_Type[3];
	CToolTipCtrl m_toolTip;
	bool m_IsProperSet;
	CRect m_rubberBand;
	CPoint m_pStart;
	float n_Zoom = 1;

	btnFlags* m_Flags;	// 
	bool* m_PtrFlags[6];

	int m_NumOfShape = 4;
	int m_NextColor = 0;
	int m_NextType = 0;
	COLORREF bgColor = RGB(255, 255, 255);
	CObArray  m_ShapeArray;
	CGraphic* pNode = NULL;
	CRectTracker m_Tracker;
	BOOL m_bLButtonDown = FALSE;
	BOOL m_bRButtonDown = FALSE;
	int GraXCount = 0;
	int GraYCount = 0;
	BOOL bDraw = FALSE;
	int m_HitNum = -1;
	int GraCountX = 0;
	int GraCountY = 0;
	BOOL m_bNormal = TRUE;
	BOOL m_bPan = FALSE;
	BOOL m_bCUT = FALSE;
	BOOL m_bCircle = FALSE;
	BOOL m_bTriangle = FALSE;
	BOOL TEXT = FALSE;
	CPoint oldMousePoint = { 0,0 };

	void CheckTracker();
	void SetToolBarBtnFlag(BtnID btnId);
	void SafeShapeArrayRemoveALL();
	BOOL GetToolBarBtnFlag(BtnID btnId);

	afx_msg LRESULT OnProperSetApply(WPARAM w, LPARAM l);

	afx_msg void OnShapeCircle();
	afx_msg void OnShapeTriangle();
	afx_msg void OnShapeText();
	afx_msg void OnColor(UINT nID);
	afx_msg void OnUpdateColor(CCmdUI* pCmdUI);
	afx_msg void OnType(UINT nID);
	afx_msg void OnUpdateType(CCmdUI* pCmdUI);
	afx_msg void OnProperty();
	afx_msg void OnViewZoomin();
	afx_msg void OnViewZoomout();
	DECLARE_MESSAGE_MAP()
	afx_msg void OnPaint();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);

public:
	COLORREF GetClrColor(int index);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	virtual void OnDraw(CDC* /*pDC*/);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnFileNew();
	afx_msg void OnFileSave();
	afx_msg void OnFileOpen();
	afx_msg void OnNormal();
	afx_msg void OnPan();
	afx_msg void OnEditCut();
	afx_msg void OnUpdateToolbarBtn(CCmdUI* pCmdUI);
	afx_msg void OnSize(UINT nType, int cx, int cy);
};

