
// MainFrm.cpp : implementation of the CMainFrame class
//

#include "pch.h"
#include "framework.h"
#include "Drawer.h"

#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#if !defined(OBM_CHECK)
#define OBM_CHECK 32760
#endif

// CMainFrame

IMPLEMENT_DYNAMIC(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	ON_WM_CREATE()
	ON_WM_SETFOCUS()
	//ON_NOTIFY_EX(TTN_NEEDTEXT, 0, OnToolTipNotify)
	ON_NOTIFY_EX((WORD)0xFFFFFFFFFFFFFDEE, 0, OnToolTipNotify)
	//ON_WM_ERASEBKGND()
	ON_WM_MEASUREITEM()
	ON_WM_DRAWITEM()
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

// CMainFrame construction/destruction

CMainFrame::CMainFrame() noexcept
{
	m_wndView = new CChildView();
	// TODO: add member initialization code here
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	// create a view to occupy the client area of the frame
	if (!m_wndView->Create(nullptr, nullptr, AFX_WS_DEFAULT_VIEW, CRect(0, 0, 0, 0), this, AFX_IDW_PANE_FIRST, nullptr))
	{
		TRACE0("Failed to create view window\n");
		return -1;
	}

	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP | CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}

	if (!m_wndStatusBar.Create(this))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}
	m_wndStatusBar.SetIndicators(indicators, sizeof(indicators) / sizeof(UINT));

	// TODO: Delete these three lines if you don't want the toolbar to be dockable
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	m_wndToolBar.SetButtonStyle(4, TBBS_CHECKBOX);
	//m_wndToolBar.SetButtonText(4, CString(_T("sdf")));
	//m_wndToolBar.GetButtonInfo(4,, TBBS_CHECKBOX)
	//CWnd* pC = GetDlgItem(ID_NORMAL);
	//((TBBUTTON*)GetDlgItem(ID_NORMAL))->iString = (INT_PTR)TEXT("選取");
	m_wndToolBar.SetButtonStyle(5, TBBS_CHECKBOX);
	m_wndToolBar.SetButtonStyle(6, TBBS_CHECKBOX);
	m_wndToolBar.SetButtonStyle(7, TBBS_CHECKBOX);
	m_wndToolBar.SetButtonStyle(8, TBBS_CHECKBOX);
	m_wndToolBar.SetButtonStyle(9, TBBS_CHECKBOX);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);


	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if (!CFrameWnd::PreCreateWindow(cs))
		return FALSE;
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	cs.dwExStyle &= ~WS_EX_CLIENTEDGE;
	cs.lpszClass = AfxRegisterWndClass(0);
	return TRUE;
}

// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}
#endif //_DEBUG


// CMainFrame message handlers

void CMainFrame::OnSetFocus(CWnd* /*pOldWnd*/)
{
	// forward focus to the view window
	m_wndView->SetFocus();
}

BOOL CMainFrame::OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo)
{
	// let the view have first crack at the command
	if (m_wndView->OnCmdMsg(nID, nCode, pExtra, pHandlerInfo))
		return TRUE;

	// otherwise, do default handling
	return CFrameWnd::OnCmdMsg(nID, nCode, pExtra, pHandlerInfo);
}


BOOL CMainFrame::OnEraseBkgnd(CDC* pDC) {
	//設定brush為希望的背景顏色
	CBrush backBrush(RGB(220, 233, 235));

	//儲存舊的brush
	CBrush* pOldBrush = pDC->SelectObject(&backBrush);
	CRect rect;
	pDC->GetClipBox(&rect);

	//畫需要的區域
	pDC->PatBlt(rect.left, rect.top, rect.Width(), rect.Height(), PATCOPY);
	pDC->SelectObject(pOldBrush);
	return TRUE;
}
void CMainFrame::OnMeasureItem(int nIDCtl, LPMEASUREITEMSTRUCT lpmis)
{
	lpmis->itemWidth = ::GetSystemMetrics(SM_CYMENU) * 4;
	lpmis->itemHeight = ::GetSystemMetrics(SM_CYMENU);
}
void CMainFrame::OnDrawItem(int nIDctl, LPDRAWITEMSTRUCT lpdis)
{
	BITMAP bm;
	CBitmap bitmap;
	bitmap.LoadOEMBitmap(OBM_CHECK);
	bitmap.GetObject(sizeof(bm), &bm);

	CDC dc;
	dc.Attach(lpdis->hDC);

	CBrush* pBrush = new CBrush(::GetSysColor((lpdis->itemState &
		ODS_SELECTED) ? COLOR_HIGHLIGHT : COLOR_MENU));
	dc.FrameRect(&(lpdis->rcItem), pBrush);
	delete pBrush;

	if (lpdis->itemState & ODS_CHECKED)
	{
		CDC dcMem;
		dcMem.CreateCompatibleDC(&dc);
		CBitmap* pOldBitmap = dcMem.SelectObject(&bitmap);

		dc.BitBlt(lpdis->rcItem.left + 4, lpdis->rcItem.top +
			(((lpdis->rcItem.bottom - lpdis->rcItem.top) -
				bm.bmHeight) / 2), bm.bmWidth, bm.bmHeight, &dcMem,
			0, 0, SRCCOPY);
		dcMem.SelectObject(pOldBitmap);
	}
	UINT itemID = lpdis->itemID & 0XFFFF;
	itemID = itemID - ID_COLOR_BLACK;
	if (itemID >= 0 && itemID < 4) {
		pBrush = new CBrush(m_wndView->GetClrColor(itemID));

		CRect rect = lpdis->rcItem;
		rect.DeflateRect(6, 4);
		rect.left += bm.bmWidth;
		dc.FillRect(rect, pBrush);
		delete pBrush;
	}

	dc.Detach();
}


BOOL CMainFrame::OnToolTipNotify(UINT id, NMHDR* pNMHDR, LRESULT* pResult)
{
	TOOLTIPTEXT* pTTT = (TOOLTIPTEXT*)pNMHDR;
	CString str;
	UINT nID = (UINT)pNMHDR->idFrom; //獲取工具欄按鈕ID
	if (nID)
	{
		nID = m_wndToolBar.CommandToIndex(nID); //根據ID獲取按鈕索引
		if (nID != -1)
		{
			switch (nID)
			{
			case 1:
				pTTT->lpszText = L"開啟新檔";
				break;
			case 2:
				pTTT->lpszText = L"開啟舊檔";
				break;
			case 3:
				pTTT->lpszText = L"儲存檔案";
				break;
			case 4:
				pTTT->lpszText = L"選取";
				break;
			case 5:
				pTTT->lpszText = L"移動";
				break;
			case 6:
				pTTT->lpszText = L"剪下";
				break;
			case 7:
				pTTT->lpszText = L"文字";
				break;
			case 8:
				pTTT->lpszText = L"三角形";
				break;
			case 9:
				pTTT->lpszText = L"橢圓形";
				break;
			case 10:
				pTTT->lpszText = L"放大";
				break;
			case 11:
				pTTT->lpszText = L"縮小";
				break;
			default:
				pTTT->lpszText = L" ";
				break;

			}

			//獲取工具欄文字			
			pTTT->hinst = AfxGetResourceHandle();
			return(TRUE);
		}
	}
	return(FALSE);
}