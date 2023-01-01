#include "pch.h"
#include "Drawer.h"
#include "ProperSet.h"
#include "afxdialogex.h"

IMPLEMENT_DYNAMIC(CProperSet, CDialog)

CProperSet::CProperSet(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_PropSet, pParent)
{
	oldBntColor[0] = NULL;
	oldBntColor[1] = NULL;
	oldBntColor[2] = NULL;
	m_oldOldType = 0;
	oldOldType = 0;
	m_oldFontType = CString();
	m_oldUnderline = false;
	m_oldItalic = false;
	m_oldIsBg = false;
	m_oldWeight = 0;
}

CProperSet::~CProperSet()
{
}

void CProperSet::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_Tab, m_Tab);
	DDX_Control(pDX, IDC_APPLY, m_BtnApply);

	CWnd* pWnd = GetParent();
	while (m_pChildView == NULL) {	// m_pChildView is CChildView.
		m_pChildView = dynamic_cast<CChildView*>(pWnd);
		pWnd = pWnd->GetNextDlgGroupItem(pWnd);
	}

	if (m_pChildView->GetGlobalObjType() == 2)
	{
		m_Tab.InsertItem(0, _T("Color"));
		m_Tab.InsertItem(1, _T("Text"));
	}

	else if (m_pChildView->GetGlobalObjType() == 0 || m_pChildView->GetGlobalObjType() == 1)
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
	ON_NOTIFY((WORD)0xFFFFFFFFFFFFFDD9, IDC_Tab, &CProperSet::OnTcnSelchangeTab) // TCN_SELCHANGE -> 0xFFFFFFFFFFFFFDD9
	ON_BN_CLICKED(IDC_APPLY, &CProperSet::OnClickedApply)
	ON_MESSAGE(WM_PROPERSET_CHANGE, &CProperSet::OnChange)
END_MESSAGE_MAP()


// CProperSet 訊息處理常式


BOOL CProperSet::OnInitDialog()
{
	CDialog::OnInitDialog();

	oldBntColor[0] = m_pChildView->GetGlobalBntColor(0);
	oldBntColor[1] = m_pChildView->GetGlobalBntColor(1);
	oldBntColor[2] = m_pChildView->GetGlobalBntColor(2);
	m_oldOldType = m_pChildView->GetGlobalBorderType();
	oldOldType = m_pChildView->GetGlobalObjType();
	m_oldFontType = m_pChildView->GetGlobalTextFontType();
	m_oldUnderline = m_pChildView->GetGlobalTextUnderline();
	m_oldItalic = m_pChildView->GetGlobalTextItalic();
	m_oldIsBg = m_pChildView->GetGlobalIsBg();
	m_oldWeight = m_pChildView->GetGlobalTextWeight();

	// TODO:  在此加入額外的初始化
	if (m_pChildView->GetGlobalObjType() == 2)
	{
		CRect rTab, rItem;
		m_Tab.GetItemRect(0, &rItem);
		m_Tab.GetClientRect(&rTab);
		int x = rItem.left;
		int y = rItem.bottom + 1;
		int cx = rTab.right - rItem.left - 3;
		int cy = rTab.bottom - y - 2;
		m_One.Create(IDD_One_Tab, &m_Tab);
		m_One.SetpView(this);
		m_Thr.Create(IDD_Thr_Tab, &m_Tab);
		m_Thr.SetpView(this);
		m_One.SetWindowPos(NULL, x, y, cx, cy, SWP_HIDEWINDOW);
		m_Thr.SetWindowPos(NULL, x, y, cx, cy, SWP_HIDEWINDOW);
		m_One.ShowWindow(true);
		m_Thr.ShowWindow(false);
	}
	else if (m_pChildView->GetGlobalObjType() == 0 || m_pChildView->GetGlobalObjType() == 1)
	{
		CRect rTab, rItem;
		m_Tab.GetItemRect(0, &rItem);
		m_Tab.GetClientRect(&rTab);
		int x = rItem.left;
		int y = rItem.bottom + 1;
		int cx = rTab.right - rItem.left - 3;
		int cy = rTab.bottom - y - 2;
		m_One.Create(IDD_One_Tab, &m_Tab);
		m_One.SetpView(this);
		m_Sec.Create(IDD_Two_Tab, &m_Tab);
		m_Sec.SetpView(this);
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
		m_One.SetpView(this);
		m_Sec.Create(IDD_Two_Tab, &m_Tab);
		m_Sec.SetpView(this);
		m_Thr.Create(IDD_Thr_Tab, &m_Tab);
		m_Thr.SetpView(this);
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
	*pResult = 0;
	m_pChildView->SetGlobalNextStepColor(0);
	int CurSel = m_Tab.GetCurSel();
	if (m_pChildView->GetGlobalObjType() == 2)
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
	else if (m_pChildView->GetGlobalObjType() == 0 || m_pChildView->GetGlobalObjType() == 1 || m_pChildView->GetGlobalObjType() == 2)
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

	if (oldBntColor[0] != m_pChildView->GetGlobalBntColor(0)) { ((CButton*)GetDlgItem(IDC_APPLY))->EnableWindow(TRUE); }
	else if (oldBntColor[1] != m_pChildView->GetGlobalBntColor(1)) { ((CButton*)GetDlgItem(IDC_APPLY))->EnableWindow(TRUE); }
	else if (oldBntColor[2] != m_pChildView->GetGlobalBntColor(2)) { ((CButton*)GetDlgItem(IDC_APPLY))->EnableWindow(TRUE); }
	//else if (oldNStepColor != m_GlobalNextStepColor) { ((CButton*)GetDlgItem(IDC_APPLY))->EnableWindow(TRUE); }
	else if (m_oldOldType != m_pChildView->GetGlobalBorderType()) { ((CButton*)GetDlgItem(IDC_APPLY))->EnableWindow(TRUE); }
	else if (oldOldType != m_pChildView->GetGlobalObjType()) { ((CButton*)GetDlgItem(IDC_APPLY))->EnableWindow(TRUE); }
	else if (m_oldFontType != m_pChildView->GetGlobalTextFontType()) { ((CButton*)GetDlgItem(IDC_APPLY))->EnableWindow(TRUE); }
	else if (m_oldUnderline != m_pChildView->GetGlobalTextUnderline()) { ((CButton*)GetDlgItem(IDC_APPLY))->EnableWindow(TRUE); }
	else if (m_oldItalic != m_pChildView->GetGlobalTextItalic()) { ((CButton*)GetDlgItem(IDC_APPLY))->EnableWindow(TRUE); }
	else if (m_oldIsBg != m_pChildView->GetGlobalIsBg()) { ((CButton*)GetDlgItem(IDC_APPLY))->EnableWindow(TRUE); }
	else if (m_oldWeight != m_pChildView->GetGlobalTextWeight()) { ((CButton*)GetDlgItem(IDC_APPLY))->EnableWindow(TRUE); }
	else { ((CButton*)GetDlgItem(IDC_APPLY))->EnableWindow(FALSE); }
	return LRESULT(0);
}

void CProperSet::OnClickedApply()
{
	((CButton*)GetDlgItem(IDC_APPLY))->EnableWindow(FALSE);

	oldBntColor[0] = m_pChildView->GetGlobalBntColor(0);
	oldBntColor[1] = m_pChildView->GetGlobalBntColor(1);
	oldBntColor[2] = m_pChildView->GetGlobalBntColor(2);
	m_oldOldType = m_pChildView->GetGlobalBorderType();
	oldOldType = m_pChildView->GetGlobalObjType();
	m_oldFontType = m_pChildView->GetGlobalTextFontType();
	m_oldUnderline = m_pChildView->GetGlobalTextUnderline();
	m_oldItalic = m_pChildView->GetGlobalTextItalic();
	m_oldIsBg = m_pChildView->GetGlobalIsBg();
	m_oldWeight = m_pChildView->GetGlobalTextWeight();

	m_pChildView->PostMessageW(WM_PROPERSET_APPLY, 0, 0);


}

CChildView* CProperSet::GetpChildView()
{
	return m_pChildView;
}