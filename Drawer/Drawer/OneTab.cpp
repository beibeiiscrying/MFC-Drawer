#include "pch.h"
#include "Drawer.h"
#include "OneTab.h"
#include "afxdialogex.h"
#include "Resource.h"
#include "ProperSet.h"


// OneTab 對話方塊

IMPLEMENT_DYNAMIC(OneTab, CDialogEx)
COLORREF OldBgColor;
OneTab::OneTab(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_One_Tab, pParent)
{
	m_pView = NULL;
	m_ItemIsBg = m_IsBg;
	nStepColor = 0;
	bntColors[0] = bntColor[0];
	bntColors[1] = bntColor[1];
	OldBgColor = bntColor[1];
	static int nStepColor = 0;
}

OneTab::~OneTab()
{
}

void OneTab::OnCancel() {

}

void OneTab::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	if (m_IsBg) { ((CButton*)GetDlgItem(IDC_CHECK1))->SetCheck(1); }
	nStepColor = 0;
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
	nStepColor = 0;
	CColorDialog dlg(RGB(255, 0, 0), CC_FULLOPEN);
	if (dlg.DoModal() == IDOK)
	{
		bntColors[0] = dlg.GetColor();
		bntColor[0] = bntColors[0];
		m_pView->PostMessageW(WM_PROPERSET_CHANGE, 0, 0);
	}
	//if (nStepColor != 0)
	nStepColor = 0;
	Invalidate();
}

void OneTab::OnBnClickedButton3()
{
	nStepColor = 1;
	CColorDialog dlg(RGB(255, 0, 0), CC_FULLOPEN);
	if (dlg.DoModal() == IDOK)
	{
		bntColors[1] = dlg.GetColor();
		bntColor[1] = bntColors[1];
		m_pView->PostMessageW(WM_PROPERSET_CHANGE, 0, 0);
	}
	//if (nStepColor != 0)
	nStepColor = 1;
	Invalidate();
}

void OneTab::OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	CDC* pDC = CDC::FromHandle(lpDrawItemStruct->hDC);
	CRect drawRect;
	drawRect.CopyRect(&(lpDrawItemStruct->rcItem));
	CBrush pBrush;
	if (nIDCtl == IDC_BUTTON1) {
		nStepColor = 0;
	}
	else if (nIDCtl == IDC_BUTTON3) {
		nStepColor = 1;
	}
	pBrush.CreateSolidBrush(bntColors[nStepColor]);
	pDC->FillRect(drawRect, &pBrush);
	//nStepColor = (nStepColor+1)%2;
}



void OneTab::OnBnClickedCheck1()
{
	m_IsBg = !(BST_UNCHECKED == ((CButton*)GetDlgItem(IDC_CHECK1))->GetCheck());
	m_pView->PostMessageW(WM_PROPERSET_CHANGE, 0, 0);

	// TODO: 在此加入控制項告知處理常式程式碼
}
