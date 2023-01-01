#include "pch.h"
#include "MyScrollView.h"

IMPLEMENT_DYNCREATE(CMyScrollView, CScrollView)



CMyScrollView::CMyScrollView()
{

	m_pdcMemory = new CDC;
	m_pBitmap = new CBitmap;
	m_bInitialSize = FALSE;

	m_zoomFactor = 5.0;
	m_minZoomFactor = 1.0f;
	m_maxZoomFactor = 10.0f;
}

CMyScrollView::~CMyScrollView()
{
	if (m_pdcMemory != NULL)
	{
		delete m_pdcMemory;
		m_pdcMemory = NULL;
	}

	if (m_pBitmap != NULL)
	{
		delete m_pBitmap;
		m_pBitmap = NULL;
	}
}

BEGIN_MESSAGE_MAP(CMyScrollView, CScrollView)
	ON_WM_PAINT()
	ON_WM_SIZE()
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()


void CMyScrollView::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();
	CClientDC dc(NULL);

	m_layout.cx = 0;
	m_layout.cy = 0;
	m_page.cx = m_layout.cx / 2;
	m_page.cy = m_layout.cy / 2;
	m_line.cx = m_layout.cx / 50;
	m_line.cy = m_layout.cy / 50;
	SetScrollSizes(MM_TEXT, m_layout, m_page, m_line);
	//m_bInitialSize = TRUE;
	if (m_pdcMemory->GetSafeHdc() == NULL)
	{
		CClientDC dc(this);
		OnPrepareDC(&dc);
		m_pdcMemory->CreateCompatibleDC(&dc);

		CRect clientRect(0, 0, 0, 0);
		GetClientRect(clientRect);
		if (m_pBitmap != NULL)
		{
			delete m_pBitmap;
			m_pBitmap = NULL;
		}
		m_pBitmap = new CBitmap();
		m_pBitmap->CreateCompatibleBitmap(&dc, clientRect.right,
			clientRect.bottom);
	}
}


void CMyScrollView::OnPaint()
{
	CPaintDC dc(this);
	OnPrepareDC(&dc);
	SetMapMode(&dc);

	CPoint viewportOrg = dc.GetViewportOrg();
	m_pdcMemory->SetViewportOrg(viewportOrg);

	CBitmap* pOldBitmap = m_pdcMemory->SelectObject(m_pBitmap);
	CRect rectUpdate(0, 0, 0, 0);
	dc.GetClipBox(&rectUpdate);
	rectUpdate.InflateRect(1, 1, 1, 1);
	m_pdcMemory->SelectClipRgn(NULL);
	m_pdcMemory->IntersectClipRect(&rectUpdate);
	CBrush backgroundBrush((COLORREF) ::GetSysColor(COLOR_WINDOW));
	CBrush* pOldBrush = m_pdcMemory->SelectObject(&backgroundBrush);
	m_pdcMemory->PatBlt(rectUpdate.left, rectUpdate.top,
		rectUpdate.Width(), rectUpdate.Height(),
		PATCOPY);

	OnDraw(m_pdcMemory);

	dc.BitBlt(rectUpdate.left, rectUpdate.top,
		rectUpdate.Width(), rectUpdate.Height(),
		m_pdcMemory, rectUpdate.left, rectUpdate.top,
		SRCCOPY);
	m_pdcMemory->SelectObject(pOldBitmap);
	m_pdcMemory->SelectObject(pOldBrush);
}


void CMyScrollView::OnSize(UINT nType, int cx, int cy)
{
	CScrollView::OnSize(nType, cx, cy);

	CDC* pDC = GetDC();
	//設定brush為希望的背景顏色
	CBrush backBrush(RGB(220, 233, 235));
	//儲存舊的brush
	CBrush* pOldBrush = pDC->SelectObject(&backBrush);
	CRect rect;
	pDC->GetClipBox(&rect);
	if (rect.Width() == 0 && rect.Height() == 0) { return; }

	CPoint viewportOrg = pDC->GetViewportOrg();
	m_pdcMemory->SetViewportOrg(viewportOrg);

	CBitmap* pOldBitmap = m_pdcMemory->SelectObject(m_pBitmap);

	BITMAP bmpBack;
	m_pBitmap->GetBitmap(&bmpBack);

	CRect r(0, 0, bmpBack.bmWidth, bmpBack.bmHeight);
	m_pdcMemory->IntersectClipRect(r);
	CBrush backgroundBrush((COLORREF) ::GetSysColor(COLOR_WINDOW));
	CBrush* pBackBrush = m_pdcMemory->SelectObject(&backgroundBrush);
	m_pdcMemory->PatBlt(r.left, r.top,
		r.Width(), r.Height(),
		PATCOPY);

	//畫需要的區域
	pDC->PatBlt(rect.left, rect.top, rect.Width(), rect.Height(), PATCOPY);
	pDC->BitBlt(r.left, r.top, r.Width(), r.Height(), m_pdcMemory, r.left, r.top, SRCCOPY);

	pDC->SelectObject(pOldBrush);

	if (m_bInitialSize == FALSE)
	{
		return;
	}

	CPaintDC dc(this);
	OnPrepareDC(&dc);
	SetMapMode(&dc);

	CRect clientRect(0, 0, 0, 0);
	GetClientRect(&clientRect);

	if (m_pBitmap != NULL)
	{
		delete m_pBitmap;
		m_pBitmap = NULL;
	}
	m_pBitmap = new CBitmap;
	m_pBitmap->CreateCompatibleBitmap(&dc, clientRect.Width(), clientRect.Height());
	Invalidate(FALSE);
}

BOOL CMyScrollView::OnEraseBkgnd(CDC* pDC)
{
	return FALSE;
}

int CMyScrollView::SetMapMode(CDC* pDC)
{
	int previousMode = pDC->SetMapMode(MM_ISOTROPIC);
	pDC->SetWindowExt(100, 100);
	pDC->SetViewportExt(FloatToInt(100 * m_zoomFactor / 5), FloatToInt(100 * (m_zoomFactor / 5)));

	return previousMode;
}

void CMyScrollView::SetDisplaySize(void)
{
	CRect clientRect(0, 0, 0, 0);
	GetClientRect(&clientRect);
	//m_displaySize.cx = FloatToInt(m_layout.cx * (m_zoomFactor / 5));
	//m_displaySize.cy = FloatToInt(m_layout.cy * (m_zoomFactor / 5));
	m_displaySize.cx = FloatToInt(clientRect.right * (m_zoomFactor / 5));
	m_displaySize.cy = FloatToInt(clientRect.bottom * (m_zoomFactor / 5));



	CPaintDC dc(this);
	OnPrepareDC(&dc);
	SetMapMode(&dc);
	//BITMAP bitmap;
	//m_pBitmap->GetBitmap(&bitmap);

	if (m_pBitmap != NULL)
	{
		delete m_pBitmap;
		m_pBitmap = NULL;
	}
	m_pBitmap = new CBitmap;
	m_pBitmap->CreateCompatibleBitmap(&dc, m_displaySize.cx, m_displaySize.cy);

	CRect rectMax(CPoint(0, 0), m_displaySize);
	SetScrollSizes(MM_TEXT, m_displaySize, m_page, m_line);
	SetMapMode(m_pdcMemory);

	if (m_displaySize.cx > clientRect.right && m_displaySize.cy > clientRect.bottom) { return; }

	CDC* pDC = GetDC();
	//設定brush為希望的背景顏色
	CBrush backBrush(RGB(220, 233, 235));
	//儲存舊的brush
	CBrush* pOldBrush = pDC->SelectObject(&backBrush);
	CRect rect;
	pDC->GetClipBox(&rect);
	if (rect.Width() == 0 && rect.Height() == 0) { return; }

	CPoint viewportOrg = pDC->GetViewportOrg();
	m_pdcMemory->SetViewportOrg(viewportOrg);

	CBitmap* pOldBitmap = m_pdcMemory->SelectObject(m_pBitmap);

	BITMAP bmpBack;
	m_pBitmap->GetBitmap(&bmpBack);

	CRect r(0, 0, bmpBack.bmWidth, bmpBack.bmHeight);
	m_pdcMemory->IntersectClipRect(r);
	CBrush backgroundBrush((COLORREF) ::GetSysColor(COLOR_WINDOW));
	CBrush* pBackBrush = m_pdcMemory->SelectObject(&backgroundBrush);
	m_pdcMemory->PatBlt(r.left, r.top,
		r.Width(), r.Height(),
		PATCOPY);

	//畫需要的區域
	pDC->PatBlt(clientRect.left, clientRect.top, clientRect.Width(), clientRect.Height(), PATCOPY);
	pDC->BitBlt(r.left, r.top, r.Width(), r.Height(), m_pdcMemory, r.left, r.top, SRCCOPY);

	pDC->SelectObject(pOldBrush);
}

void CMyScrollView::SetZoomScale(float fScale)
{
	float oldZoomFactor = m_zoomFactor;
	CPoint centerScrollPosition = GetCenterScrollPosition();

	SetZoomFactor(fScale);
	SetDisplaySize();

	int newXScrollPosition = FloatToInt((centerScrollPosition.x / oldZoomFactor) * (m_zoomFactor / 5));
	int newYScrollPosition = FloatToInt((centerScrollPosition.y / oldZoomFactor) * (m_zoomFactor / 5));
	int tpX = newXScrollPosition;
	int tpY = newYScrollPosition;

	CRect clientRect(0, 0, 0, 0);
	GetClientRect(&clientRect);
	newXScrollPosition -= clientRect.right / 2;
	newYScrollPosition -= clientRect.bottom / 2;
	ScrollToPosition(CPoint(newXScrollPosition, newYScrollPosition));

	Invalidate(FALSE);
}

void CMyScrollView::SetZoomArea(CRect zoomRect)
{
	CRect clientRect(0, 0, 0, 0);
	GetClientRect(clientRect);

	CRect realRect(zoomRect);
	LPtoDP(&realRect);

	float widthRatio = float(clientRect.Width()) / float(realRect.Width());
	float heightRatio = float(clientRect.Height()) / float(realRect.Height());
	float ratio = (widthRatio < heightRatio) ? widthRatio : heightRatio;
	if (m_zoomFactor != 0) {
		ratio = ratio * (m_zoomFactor / 5);
	}

	CPoint centerScrollPosition = CPoint(0, 0);
	centerScrollPosition.x = zoomRect.left + zoomRect.Width() / 2;
	centerScrollPosition.y = zoomRect.top + zoomRect.Height() / 2;

	SetZoomFactor(ratio);
	SetDisplaySize();

	int newXScrollPosition = FloatToInt(centerScrollPosition.x * (m_zoomFactor / 5));
	int newYScrollPosition = FloatToInt(centerScrollPosition.y * (m_zoomFactor / 5));

	GetClientRect(clientRect);
	newXScrollPosition -= clientRect.Width() / 2;
	newYScrollPosition -= clientRect.Height() / 2;
	ScrollToPosition(CPoint(newXScrollPosition, newYScrollPosition));

	Invalidate(FALSE);
}

CPoint CMyScrollView::GetCenterScrollPosition(void)
{
	CPoint ScrollPosition = GetScrollPosition();
	CRect ClientRect(0, 0, 0, 0);
	GetClientRect(&ClientRect);
	ScrollPosition.x += ClientRect.right / 2;
	ScrollPosition.y += ClientRect.bottom / 2;
	return ScrollPosition;
}

void CMyScrollView::LPtoDP(LPPOINT lpPoint)
{
	CClientDC dc(this);
	OnPrepareDC(&dc);
	SetMapMode(&dc);
	dc.LPtoDP(lpPoint);
}

void CMyScrollView::LPtoDP(LPRECT lpRect)
{
	CClientDC dc(this);
	OnPrepareDC(&dc);
	SetMapMode(&dc);
	dc.LPtoDP(lpRect);
}

void CMyScrollView::LPtoDP(LPSIZE lpSize)
{
	CClientDC dc(this);
	OnPrepareDC(&dc);
	SetMapMode(&dc);
	dc.LPtoDP(lpSize);
}

void CMyScrollView::DPtoLP(LPPOINT lpPoint)
{
	CClientDC dc(this);
	OnPrepareDC(&dc);
	SetMapMode(&dc);
	dc.DPtoLP(lpPoint);
}

void CMyScrollView::DPtoLP(LPRECT lpRect)
{
	CClientDC dc(this);
	OnPrepareDC(&dc);
	SetMapMode(&dc);
	dc.DPtoLP(lpRect);
}

void CMyScrollView::DPtoLP(LPSIZE lpSize)
{
	CClientDC dc(this);
	OnPrepareDC(&dc);
	SetMapMode(&dc);
	dc.DPtoLP(lpSize);
}

int CMyScrollView::FloatToInt(float fNumber)
{
	if (fNumber >= 0)
	{
		fNumber += 0.5f;
	}
	else
	{
		fNumber -= 0.5f;
	}
	return int(fNumber);
}

void CMyScrollView::SetZoomFactor(float fZoomFactor)
{
	if (fZoomFactor <= m_minZoomFactor) {
		m_zoomFactor = m_minZoomFactor;
	}
	else if (fZoomFactor >= m_maxZoomFactor)
		m_zoomFactor = m_maxZoomFactor;
	else
		m_zoomFactor = fZoomFactor;
}

void CMyScrollView::OnDraw(CDC* /*pDC*/)
{

}