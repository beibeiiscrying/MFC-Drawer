#pragma once
#include <afxdialogex.h>

class ThrTab : public CDialogEx
{
	DECLARE_DYNAMIC(ThrTab)

public:
	ThrTab(CWnd* pParent = NULL);   // �зǫغc�禡
	virtual ~ThrTab();

	// ��ܤ�����
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_Thr_Tab };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �䴩
	CMFCFontComboBox m_font;
	CWnd *m_pView;
	CWnd *m_pChildView;
	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnCbnSelchangeMfcfontcombo1();
	afx_msg void OnBnClickedCheck2();
	afx_msg void OnBnClickedCheck3();
	afx_msg void OnBnClickedCheck1();
	afx_msg void OnCbnSelchangeCombo1();
	void OnCancel() override;
	void SetpView(CWnd* pView);
};
