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

	DECLARE_MESSAGE_MAP()
public:
	CWnd* m_pView;
	CMFCFontComboBox m_font;
	afx_msg void OnCbnSelchangeMfcfontcombo1();
	afx_msg void OnBnClickedCheck2();
	afx_msg void OnBnClickedCheck3();
	afx_msg void OnBnClickedCheck1();
	afx_msg void OnCbnSelchangeCombo1();
	void OnCancel() override;
};
