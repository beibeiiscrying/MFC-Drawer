#include "pch.h"
#include "Drawer.h"
#include "OneTab.h"
#include "ProperSet.h"


// OneTab 對話方塊

IMPLEMENT_DYNAMIC(OneTab, CDialogEx)
COLORREF OldBgColor;
OneTab::OneTab(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_One_Tab, pParent)
{
	m_pView = NULL;
	m_pChildView = NULL;
	m_ItemIsBg = false;
	m_BorderColor[0] = NULL;
	m_BorderColor[1] = NULL;
	OldBgColor = NULL;
}

OneTab::~OneTab()
{
}

void OneTab::OnCancel() {

}

void OneTab::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	Invalidate();
}


BEGIN_MESSAGE_MAP(OneTab, CDialogEx)
	ON_WM_DRAWITEM()
	ON_BN_CLICKED(IDC_BUTTON1, &OneTab::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON3, &OneTab::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_CHECK1, &OneTab::OnBnClickedCheck1)
END_MESSAGE_MAP()


// OneTab 訊息處理常式

void OneTab::OnBnClickedButton1()
{
	((CChildView*)m_pChildView)->SetGlobalNextStepColor(0);
	CColorDialog dlg(m_BorderColor[0], CC_FULLOPEN);
	if (dlg.DoModal() == IDOK)
	{
		m_BorderColor[0] = dlg.GetColor();
		((CChildView*)m_pChildView)->SetGlobalBntColor(0, m_BorderColor[0]);
		m_pView->PostMessageW(WM_PROPERSET_CHANGE, 0, 0);
	}
	((CChildView*)m_pChildView)->SetGlobalNextStepColor(0);
	Invalidate();
}

void OneTab::OnBnClickedButton3()
{
	((CChildView*)m_pChildView)->SetGlobalNextStepColor(1);
	CColorDialog dlg(m_BorderColor[1], CC_FULLOPEN);
	if (dlg.DoModal() == IDOK)
	{
		m_BorderColor[1] = dlg.GetColor();
		((CChildView*)m_pChildView)->SetGlobalBntColor(1, m_BorderColor[1]);
		m_pView->PostMessageW(WM_PROPERSET_CHANGE, 0, 0);
	}
	((CChildView*)m_pChildView)->SetGlobalNextStepColor(1);
	Invalidate();
}

void OneTab::OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	CDC* pDC = CDC::FromHandle(lpDrawItemStruct->hDC);
	CRect drawRect;
	drawRect.CopyRect(&(lpDrawItemStruct->rcItem));
	CBrush pBrush;
	if (nIDCtl == IDC_BUTTON1) {
		((CChildView*)m_pChildView)->SetGlobalNextStepColor(0);
	}
	else if (nIDCtl == IDC_BUTTON3) {
		((CChildView*)m_pChildView)->SetGlobalNextStepColor(1);
	}
	pBrush.CreateSolidBrush(m_BorderColor[((CChildView*)m_pChildView)->GetGlobalNextStepColor()]);
	pDC->FillRect(drawRect, &pBrush);
}



void OneTab::OnBnClickedCheck1()
{
	((CChildView*)m_pChildView)->SetGlobalIsBg(!(BST_UNCHECKED == ((CButton*)GetDlgItem(IDC_CHECK1))->GetCheck()));
	m_pView->PostMessageW(WM_PROPERSET_CHANGE, 0, 0);
}

void OneTab::SetpView(CWnd *pView)
{
	m_pView = pView;
	m_pChildView = ((CProperSet*)m_pView)->GetpChildView();
	m_ItemIsBg = ((CChildView*)m_pChildView)->GetGlobalIsBg();
	((CChildView*)m_pChildView)->SetGlobalNextStepColor(0);
	m_BorderColor[0] = ((CChildView*)m_pChildView)->GetGlobalBntColor(0);
	m_BorderColor[1] = ((CChildView*)m_pChildView)->GetGlobalBntColor(1);
	OldBgColor = ((CChildView*)m_pChildView)->GetGlobalBntColor(1);


	if (((CChildView*)m_pChildView)->GetGlobalIsBg()) { ((CButton*)GetDlgItem(IDC_CHECK1))->SetCheck(1); }
	((CChildView*)m_pChildView)->SetGlobalNextStepColor(0);
}