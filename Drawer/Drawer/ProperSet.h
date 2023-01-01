#pragma once
#include <afxwin.h>
#include "OneTab.h"
#include "SecondTab.h"
#include "ThrTab.h"
#include "ChildView.h"
#include "MainFrm.h"

class CProperSet : public CDialog
{
	DECLARE_DYNAMIC(CProperSet)

public:
	CProperSet(CWnd* pParent = NULL);   // 標準建構函式
	virtual ~CProperSet();

	// 對話方塊資料
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PropSet };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支援

	DECLARE_MESSAGE_MAP()
public:
	CTabCtrl m_Tab;
	CButton m_BtnApply;
	OneTab m_One;
	SecondTab m_Sec;
	ThrTab m_Thr;
	CChildView* pView;

	COLORREF oldBntColor[3];
	//int oldNStepColor;
	int m_oldOldType;
	int oldOldType;
	CString m_oldFontType;
	bool m_oldUnderline;
	bool m_oldItalic;
	bool m_oldIsBg;
	int m_oldWeight;

	virtual BOOL OnInitDialog();
	afx_msg void OnTcnSelchangeTab(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg LRESULT OnChange(WPARAM w, LPARAM l);
	afx_msg void OnClickedApply();
};

