#pragma once
#include <afxdialogex.h>


class ThrTab : public CDialogEx
{
	DECLARE_DYNAMIC(ThrTab)

public:
	ThrTab(CWnd* pParent = NULL);   // 標準建構函式
	virtual ~ThrTab();

	// 對話方塊資料
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_Thr_Tab };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支援

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
