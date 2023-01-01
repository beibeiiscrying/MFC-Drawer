#include "pch.h"
#include "Drawer.h"
#include "ProperSet.h"
#include "afxdialogex.h"

IMPLEMENT_DYNAMIC(CProperSet, CDialog)

CProperSet::CProperSet(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_PropSet, pParent)
{
	//  m_One = 0;
	oldBntColor[0] = bntColor[0];
	oldBntColor[1] = bntColor[1];
	oldBntColor[2] = bntColor[2];
	//oldNStepColor = nStepColor;
	m_oldOldType = m_OldType;
	oldOldType = OldType;
	m_oldFontType = m_FontType;
	m_oldUnderline = m_Underline;
	m_oldItalic = m_Italic;
	m_oldIsBg = m_IsBg;
	m_oldWeight = m_Weight;
}

CProperSet::~CProperSet()
{
}

void CProperSet::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_Tab, m_Tab);
	DDX_Control(pDX, IDC_APPLY, m_BtnApply);
	if (OldType == 2)
	{
		m_Tab.InsertItem(0, _T("Color"));
		m_Tab.InsertItem(1, _T("Text"));
	}

	else if (OldType == 0 || OldType == 1)
	{
		m_Tab.InsertItem(0, _T("Color"));
		m_Tab.InsertItem(1, _T("Border"));
	}
	else
	{
		m_Tab.InsertItem(0, _T("Color"));
		m_Tab.InsertItem(1, _T("Border"));
		m_Tab.InsertItem(2, _T("Text"));
	}

}


BEGIN_MESSAGE_MAP(CProperSet, CDialog)
	ON_NOTIFY((WORD)0xFFFFFFFFFFFFFDD9, IDC_Tab, &CProperSet::OnTcnSelchangeTab)
	//ON_NOTIFY(TCN_SELCHANGE, IDC_Tab, &CProperSet::OnTcnSelchangeTab)
	ON_BN_CLICKED(IDC_APPLY, &CProperSet::OnClickedApply)
	ON_MESSAGE(WM_PROPERSET_CHANGE, &CProperSet::OnChange)
END_MESSAGE_MAP()


// CProperSet 訊息處理常式


BOOL CProperSet::OnInitDialog()
{
	CDialog::OnInitDialog();

	oldBntColor[0] = bntColor[0];
	oldBntColor[1] = bntColor[1];
	oldBntColor[2] = bntColor[2];
	//oldNStepColor = nStepColor;
	m_oldOldType = m_OldType;
	oldOldType = OldType;
	m_oldFontType = m_FontType;
	m_oldUnderline = m_Underline;
	m_oldItalic = m_Italic;
	m_oldIsBg = m_IsBg;
	m_oldWeight = m_Weight;

	// TODO:  在此加入額外的初始化
	if (OldType == 2)
	{
		CRect rTab, rItem;
		m_Tab.GetItemRect(0, &rItem);
		m_Tab.GetClientRect(&rTab);
		int x = rItem.left;
		int y = rItem.bottom + 1;
		int cx = rTab.right - rItem.left - 3;
		int cy = rTab.bottom - y - 2;
		m_One.Create(IDD_One_Tab, &m_Tab);
		m_One.m_pView = this;
		m_Thr.Create(IDD_Thr_Tab, &m_Tab);
		m_Thr.m_pView = this;
		m_One.SetWindowPos(NULL, x, y, cx, cy, SWP_HIDEWINDOW);
		m_Thr.SetWindowPos(NULL, x, y, cx, cy, SWP_HIDEWINDOW);
		m_One.ShowWindow(true);
		m_Thr.ShowWindow(false);
	}
	else if (OldType == 0 || OldType == 1)
	{
		CRect rTab, rItem;
		m_Tab.GetItemRect(0, &rItem);
		m_Tab.GetClientRect(&rTab);
		int x = rItem.left;
		int y = rItem.bottom + 1;
		int cx = rTab.right - rItem.left - 3;
		int cy = rTab.bottom - y - 2;
		m_One.Create(IDD_One_Tab, &m_Tab);
		m_One.m_pView = this;
		m_Sec.Create(IDD_Two_Tab, &m_Tab);
		m_Sec.m_pView = this;
		m_One.SetWindowPos(NULL, x, y, cx, cy, SWP_HIDEWINDOW);
		m_Sec.SetWindowPos(NULL, x, y, cx, cy, SWP_HIDEWINDOW);
		m_One.ShowWindow(true);
		m_Sec.ShowWindow(false);
	}
	else
	{
		CRect rTab, rItem;
		m_Tab.GetItemRect(0, &rItem);
		m_Tab.GetClientRect(&rTab);
		int x = rItem.left;
		int y = rItem.bottom + 1;
		int cx = rTab.right - rItem.left - 3;
		int cy = rTab.bottom - y - 2;
		m_One.Create(IDD_One_Tab, &m_Tab);
		m_One.m_pView = this;
		m_Sec.Create(IDD_Two_Tab, &m_Tab);
		m_Sec.m_pView = this;
		m_Thr.Create(IDD_Thr_Tab, &m_Tab);
		m_Thr.m_pView = this;
		m_One.SetWindowPos(NULL, x, y, cx, cy, SWP_HIDEWINDOW);
		m_Sec.SetWindowPos(NULL, x, y, cx, cy, SWP_HIDEWINDOW);
		m_Thr.SetWindowPos(NULL, x, y, cx, cy, SWP_HIDEWINDOW);
		m_One.ShowWindow(true);
		m_Sec.ShowWindow(false);
		m_Thr.ShowWindow(false);
	}

	Invalidate();
	return TRUE;  // return TRUE unless you set the focus to a control
				  // EXCEPTION: OCX 屬性頁應傳回 FALSE
}





void CProperSet::OnTcnSelchangeTab(NMHDR* pNMHDR, LRESULT* pResult)
{
	// TODO: 在此加入控制項告知處理常式程式碼
	*pResult = 0;
	nStepColor = 0;
	int CurSel = m_Tab.GetCurSel();
	if (OldType == 2)
	{
		switch (CurSel)
		{
		case 0:
			m_One.ShowWindow(true);
			m_Thr.ShowWindow(false);
			break;
		case 1:
			m_One.ShowWindow(false);
			m_Thr.ShowWindow(true);
			break;
		default:;
		}
	}
	else if (OldType == 0 || OldType == 1 || OldType == 2)
	{
		switch (CurSel)
		{
		case 0:
			m_One.ShowWindow(true);
			m_Sec.ShowWindow(false);
			break;
		case 1:
			m_One.ShowWindow(false);
			m_Sec.ShowWindow(true);
			break;
		default:;
		}
	}
	else
	{
		switch (CurSel)
		{
		case 0:
			m_One.ShowWindow(true);
			m_Sec.ShowWindow(false);
			m_Thr.ShowWindow(false);
			break;
		case 1:
			m_One.ShowWindow(false);
			m_Sec.ShowWindow(true);
			m_Thr.ShowWindow(false);
			break;
		case 2:
			m_One.ShowWindow(false);
			m_Sec.ShowWindow(false);
			m_Thr.ShowWindow(true);
			break;
		default:;
		}
	}

}

LRESULT CProperSet::OnChange(WPARAM wParam, LPARAM lParam) {

	if (oldBntColor[0] != bntColor[0]) { ((CButton*)GetDlgItem(IDC_APPLY))->EnableWindow(TRUE); }
	else if (oldBntColor[1] != bntColor[1]) { ((CButton*)GetDlgItem(IDC_APPLY))->EnableWindow(TRUE); }
	else if (oldBntColor[2] != bntColor[2]) { ((CButton*)GetDlgItem(IDC_APPLY))->EnableWindow(TRUE); }
	//else if (oldNStepColor != nStepColor) { ((CButton*)GetDlgItem(IDC_APPLY))->EnableWindow(TRUE); }
	else if (m_oldOldType != m_OldType) { ((CButton*)GetDlgItem(IDC_APPLY))->EnableWindow(TRUE); }
	else if (oldOldType != OldType) { ((CButton*)GetDlgItem(IDC_APPLY))->EnableWindow(TRUE); }
	else if (m_oldFontType != m_FontType) { ((CButton*)GetDlgItem(IDC_APPLY))->EnableWindow(TRUE); }
	else if (m_oldUnderline != m_Underline) { ((CButton*)GetDlgItem(IDC_APPLY))->EnableWindow(TRUE); }
	else if (m_oldItalic != m_Italic) { ((CButton*)GetDlgItem(IDC_APPLY))->EnableWindow(TRUE); }
	else if (m_oldIsBg != m_IsBg) { ((CButton*)GetDlgItem(IDC_APPLY))->EnableWindow(TRUE); }
	else if (m_oldWeight != m_Weight) { ((CButton*)GetDlgItem(IDC_APPLY))->EnableWindow(TRUE); }
	else { ((CButton*)GetDlgItem(IDC_APPLY))->EnableWindow(FALSE); }
	return LRESULT(0);
}

void CProperSet::OnClickedApply()
{
	((CButton*)GetDlgItem(IDC_APPLY))->EnableWindow(FALSE);
	HWND tp = this->GetSafeHwnd();
	CWnd* pWnd = GetParent();
	while (pView == NULL) {
		pView = dynamic_cast<CChildView*>(pWnd);
		pWnd = pWnd->GetNextDlgGroupItem(pWnd);
	}

	oldBntColor[0] = bntColor[0];
	oldBntColor[1] = bntColor[1];
	oldBntColor[2] = bntColor[2];
	//oldNStepColor = nStepColor;
	m_oldOldType = m_OldType;
	oldOldType = OldType;
	m_oldFontType = m_FontType;
	m_oldUnderline = m_Underline;
	m_oldItalic = m_Italic;
	m_oldIsBg = m_IsBg;
	m_oldWeight = m_Weight;

	pView->PostMessageW(WM_PROPERSET_APPLY, 0, 0);


}