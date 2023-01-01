#include "pch.h"
#include "Drawer.h"
#include "SecondTab.h"

// SecondTab 對話方塊

IMPLEMENT_DYNAMIC(SecondTab, CDialogEx)

SecondTab::SecondTab(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_Two_Tab, pParent)
{
	m_pView = NULL;
	bntColors = bntColor[2];
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
	m_LineTypeCombo.SetCurSel(m_OldType);
}


BEGIN_MESSAGE_MAP(SecondTab, CDialogEx)
	ON_WM_DRAWITEM()
	ON_CBN_SELCHANGE(IDC_COMBO2, &SecondTab::OnCbnSelchangeCombo2)
	ON_BN_CLICKED(IDC_BUTTON1, &SecondTab::OnBnClickedButton1)
END_MESSAGE_MAP()


// SecondTab 訊息處理常式


void SecondTab::OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	// TODO: 在此加入您的訊息處理常式程式碼和 (或) 呼叫預設值
	CDC* pDC = CDC::FromHandle(lpDrawItemStruct->hDC);
	CRect drawRect;
	drawRect.CopyRect(&(lpDrawItemStruct->rcItem));
	if (nIDCtl == IDC_BUTTON1) {
		CBrush pBrush;
		pBrush.CreateSolidBrush(bntColors);
		pDC->FillRect(drawRect, &pBrush);
	}
	CDialogEx::OnDrawItem(nIDCtl, lpDrawItemStruct);
}


void SecondTab::OnCbnSelchangeCombo2()
{
	// TODO: 在此加入控制項告知處理常式程式碼
	m_OldType = m_LineTypeCombo.GetCurSel();
	m_pView->PostMessageW(WM_PROPERSET_CHANGE, 0, 0);
}


void SecondTab::OnBnClickedButton1()
{
	// TODO: 在此加入控制項告知處理常式程式碼
	CColorDialog dlg(RGB(255, 0, 0), CC_FULLOPEN);
	if (dlg.DoModal() == IDOK)
	{
		bntColors = dlg.GetColor();
		bntColor[2] = bntColors;
		m_pView->PostMessageW(WM_PROPERSET_CHANGE, 0, 0);
	}
	Invalidate();
}
