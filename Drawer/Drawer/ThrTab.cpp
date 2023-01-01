#include "pch.h"
#include "Drawer.h"
#include "ThrTab.h"



// ThrTab 對話方塊

IMPLEMENT_DYNAMIC(ThrTab, CDialogEx)

ThrTab::ThrTab(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_Thr_Tab, pParent)
{
	m_pView = NULL;
}

ThrTab::~ThrTab()
{
}

void ThrTab::OnCancel() {

}

void ThrTab::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);


	//CRect rect = CRect(107, 39, 80, 30);
	//CMFCFontComboBox* p_Button = new CMFCFontComboBox();
	//ASSERT_VALID(p_Button);
	//p_Button->Create(WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | WS_VSCROLL | WS_TABSTOP | 0x312, rect, this, IDC_MFCFONTCOMBO1); //建立按鈕
	//p_Button->Setup();
	//p_Button->m_bDrawUsingFont = true;
	//p_Button->SetCurSel(0);
	DDX_Control(pDX, IDC_MFCFONTCOMBO1, m_font);
	if (m_Italic == TRUE)
	{
		((CButton*)GetDlgItem(IDC_CHECK2))->SetCheck(BST_CHECKED);
	}
	if (m_Underline == TRUE)
	{
		((CButton*)GetDlgItem(IDC_CHECK3))->SetCheck(BST_CHECKED);
	}
	if (m_Weight == 700)
	{
		((CButton*)GetDlgItem(IDC_CHECK1))->SetCheck(BST_CHECKED);
	}
	LPCTSTR lpszmyExactString = m_FontType;
	int nDex = 0;
	if ((nDex = m_font.FindStringExact(nDex, lpszmyExactString)) != CB_ERR)
	{
		m_font.SetCurSel(nDex);
	}

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
	// TODO: 在此加入控制項告知處理常式程式碼
	CMFCFontInfo* pFontInfo = m_font.GetSelFont();
	m_FontType = pFontInfo->m_strName;
	m_pView->PostMessageW(WM_PROPERSET_CHANGE, 0, 0);
}


void ThrTab::OnBnClickedCheck2()
{
	if (BST_UNCHECKED == ((CButton*)GetDlgItem(IDC_CHECK2))->GetCheck())
		m_Italic = FALSE;
	else
		m_Italic = TRUE;
	m_pView->PostMessageW(WM_PROPERSET_CHANGE, 0, 0);
}


void ThrTab::OnBnClickedCheck3()
{
	if (BST_UNCHECKED == ((CButton*)GetDlgItem(IDC_CHECK3))->GetCheck())
		m_Underline = FALSE;
	else
		m_Underline = TRUE;
	m_pView->PostMessageW(WM_PROPERSET_CHANGE, 0, 0);
	// TODO: 在此加入控制項告知處理常式程式碼
}


void ThrTab::OnBnClickedCheck1()
{
	// TODO: 在此加入控制項告知處理常式程式碼
	if (BST_UNCHECKED == ((CButton*)GetDlgItem(IDC_CHECK1))->GetCheck())
		m_Weight = 0;
	else
		m_Weight = 700;
	m_pView->PostMessageW(WM_PROPERSET_CHANGE, 0, 0);
}


void ThrTab::OnCbnSelchangeCombo1()
{
	// TODO: 在此加入控制項告知處理常式程式碼
}
