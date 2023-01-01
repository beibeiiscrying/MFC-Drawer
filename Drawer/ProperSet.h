#pragma once
#include <afxwin.h>
#include "ChildView.h"
#include "OneTab.h"
#include "SecondTab.h"
#include "ThrTab.h"
#include "MainFrm.h"

class CProperSet : public CDialog
{
	DECLARE_DYNAMIC(CProperSet)

public:
	CProperSet(CWnd* pParent = NULL);   // �зǫغc�禡
	virtual ~CProperSet();

	// ��ܤ�����
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PropSet };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �䴩

	DECLARE_MESSAGE_MAP()
public:

	virtual BOOL OnInitDialog();
	afx_msg void OnTcnSelchangeTab(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg LRESULT OnChange(WPARAM w, LPARAM l);
	afx_msg void OnClickedApply();
	CChildView* GetpChildView();

protected:
	CTabCtrl m_Tab;
	CButton m_BtnApply;
	OneTab m_One;
	SecondTab m_Sec;
	ThrTab m_Thr;
	CChildView* m_pChildView;

	COLORREF oldBntColor[3];
	int m_oldOldType;
	int oldOldType;
	CString m_oldFontType;
	bool m_oldUnderline;
	bool m_oldItalic;
	bool m_oldIsBg;
	int m_oldWeight;
};

