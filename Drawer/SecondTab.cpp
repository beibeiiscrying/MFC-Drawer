#include "pch.h"
#include "Drawer.h"
#include "SecondTab.h"
#include "ProperSet.h"

// SecondTab 對話方塊

IMPLEMENT_DYNAMIC(SecondTab, CDialogEx)

SecondTab::SecondTab(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_Two_Tab, pParent)
{
	m_pView = NULL;
	m_pChildView = NULL;
	m_BorderColor = NULL;
}

SecondTab::~SecondTab()
{
}

void SecondTab::OnCancel() {

}
void SecondTab::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO2, m_LineTypeCombo);
}


BEGIN_MESSAGE_MAP(SecondTab, CDialogEx)
	ON_WM_DRAWITEM()
	ON_CBN_SELCHANGE(IDC_COMBO2, &SecondTab::OnCbnSelchangeCombo2)
	ON_BN_CLICKED(IDC_BUTTON1, &SecondTab::OnBnClickedButton1)
END_MESSAGE_MAP()


// SecondTab 訊息處理常式


void SecondTab::OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	CDC* pDC = CDC::FromHandle(lpDrawItemStruct->hDC);
	CRect drawRect;
	drawRect.CopyRect(&(lpDrawItemStruct->rcItem));
	if (nIDCtl == IDC_BUTTON1) {
		CBrush pBrush;
		pBrush.CreateSolidBrush(m_BorderColor);
		pDC->FillRect(drawRect, &pBrush);
	}
	CDialogEx::OnDrawItem(nIDCtl, lpDrawItemStruct);
}


void SecondTab::OnCbnSelchangeCombo2()
{
	((CChildView*)m_pChildView)->SetGlobalBorderType(m_LineTypeCombo.GetCurSel());
	m_pView->PostMessageW(WM_PROPERSET_CHANGE, 0, 0);
}


void SecondTab::OnBnClickedButton1()
{
	CColorDialog dlg(m_BorderColor, CC_FULLOPEN);
	if (dlg.DoModal() == IDOK)
	{
		m_BorderColor = dlg.GetColor();
		((CChildView*)m_pChildView)->SetGlobalBntColor(2, m_BorderColor);
		m_pView->PostMessageW(WM_PROPERSET_CHANGE, 0, 0);
	}
	Invalidate();
}

void SecondTab::SetpView(CWnd* pView)
{
	m_pView = pView;
	m_pChildView = ((CProperSet*)m_pView)->GetpChildView();
	m_BorderColor = ((CChildView*)m_pChildView)->GetGlobalBntColor(2);

	m_LineTypeCombo.SetCurSel(((CChildView*)m_pChildView)->GetGlobalBorderType());
}