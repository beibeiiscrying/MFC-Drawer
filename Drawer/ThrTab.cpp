#include "pch.h"
#include "Drawer.h"
#include "ThrTab.h"
#include "ProperSet.h"



// ThrTab 對話方塊

IMPLEMENT_DYNAMIC(ThrTab, CDialogEx)

ThrTab::ThrTab(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_Thr_Tab, pParent)
{
	m_pView = NULL;
	m_pChildView = NULL;
}

ThrTab::~ThrTab()
{
}

void ThrTab::OnCancel() {

}

void ThrTab::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_MFCFONTCOMBO1, m_font);
	Invalidate();
}


BEGIN_MESSAGE_MAP(ThrTab, CDialogEx)
	ON_CBN_SELCHANGE(IDC_MFCFONTCOMBO1, &ThrTab::OnCbnSelchangeMfcfontcombo1)
	ON_BN_CLICKED(IDC_CHECK2, &ThrTab::OnBnClickedCheck2)
	ON_BN_CLICKED(IDC_CHECK3, &ThrTab::OnBnClickedCheck3)
	ON_BN_CLICKED(IDC_CHECK1, &ThrTab::OnBnClickedCheck1)
	ON_CBN_SELCHANGE(IDC_COMBO2, &ThrTab::OnCbnSelchangeCombo1)
END_MESSAGE_MAP()


// ThrTab 訊息處理常式


void ThrTab::OnCbnSelchangeMfcfontcombo1()
{
	CMFCFontInfo* pFontInfo = m_font.GetSelFont();
	((CChildView*)m_pChildView)->SetGlobalTextFontType(pFontInfo->m_strName);
	m_pView->PostMessageW(WM_PROPERSET_CHANGE, 0, 0);
}


void ThrTab::OnBnClickedCheck2()
{
	if (BST_UNCHECKED == ((CButton*)GetDlgItem(IDC_CHECK2))->GetCheck())
		((CChildView*)m_pChildView)->SetGlobalTextItalic(false);
	else
		((CChildView*)m_pChildView)->SetGlobalTextItalic(true);
	m_pView->PostMessageW(WM_PROPERSET_CHANGE, 0, 0);
}


void ThrTab::OnBnClickedCheck3()
{
	if (BST_UNCHECKED == ((CButton*)GetDlgItem(IDC_CHECK3))->GetCheck())
		((CChildView*)m_pChildView)->SetGlobalTextUnderline(false);
	else
		((CChildView*)m_pChildView)->SetGlobalTextUnderline(true);
	m_pView->PostMessageW(WM_PROPERSET_CHANGE, 0, 0);
}


void ThrTab::OnBnClickedCheck1()
{
	if (BST_UNCHECKED == ((CButton*)GetDlgItem(IDC_CHECK1))->GetCheck())
		((CChildView*)m_pChildView)->SetGlobalTextWeight(0);
	else
		((CChildView*)m_pChildView)->SetGlobalTextWeight(700);
	m_pView->PostMessageW(WM_PROPERSET_CHANGE, 0, 0);
}


void ThrTab::OnCbnSelchangeCombo1()
{
}

void ThrTab::SetpView(CWnd* pView)
{
	m_pView = pView;
	m_pChildView = ((CProperSet*)m_pView)->GetpChildView();

	if (((CChildView*)m_pChildView)->GetGlobalTextItalic() == true)
	{
		((CButton*)GetDlgItem(IDC_CHECK2))->SetCheck(BST_CHECKED);
	}
	if (((CChildView*)m_pChildView)->GetGlobalTextUnderline() == true)
	{
		((CButton*)GetDlgItem(IDC_CHECK3))->SetCheck(BST_CHECKED);
	}
	if (((CChildView*)m_pChildView)->GetGlobalTextWeight() == 700)
	{
		((CButton*)GetDlgItem(IDC_CHECK1))->SetCheck(BST_CHECKED);
	}
	if (m_pChildView != NULL) {
		LPCTSTR lpszmyExactString = ((CChildView*)m_pChildView)->GetGlobalTextFontType();
		int nDex = 0;
		if ((nDex = m_font.FindStringExact(nDex, lpszmyExactString)) != CB_ERR)
		{
			m_font.SetCurSel(nDex);
		}
	}
}