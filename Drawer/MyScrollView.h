#pragma once
#include <afxwin.h>
class CMyScrollView :public CScrollView
{
public:
	CDC* m_PdcMemory;
	CBitmap* m_pBitmap;
	BOOL		m_bInitialSize;

protected:
	float		m_ZoomFactor;
	float		m_MinZoomFactor;
	float		m_MaxZoomFactor;
	CSize		m_Line;
	CSize		m_Page;
	CSize		m_Layout;
	CSize		m_DisplaySize;

public:
	int  SetMapMode(CDC* pDC);
	void SetDisplaySize(void);
	void SetZoomScale(float fScale);
	void SetZoomArea(CRect zoomRect);
	CPoint GetCenterScrollPosition(void);
	void LPtoDP(LPPOINT lpPoint);
	void LPtoDP(LPRECT lpRect);
	void LPtoDP(LPSIZE lpSize);
	void DPtoLP(LPPOINT lpPoint);
	void DPtoLP(LPRECT lpRect);
	void DPtoLP(LPSIZE lpSize);
	CSize GetDisplaySize() { return m_DisplaySize; };
	int FloatToInt(float fNumber);

protected:
	void SetZoomFactor(float fZoomFactor);
	CMyScrollView();
	virtual ~CMyScrollView();
	DECLARE_DYNCREATE(CMyScrollView)

protected:
	virtual void OnInitialUpdate();
	afx_msg void OnPaint();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	DECLARE_MESSAGE_MAP()
	virtual void OnDraw(CDC* /*pDC*/);
};

