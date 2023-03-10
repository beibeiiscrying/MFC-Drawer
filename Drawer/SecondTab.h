#pragma once
#include <afxdialogex.h>

// SecondTab 對話方塊

class SecondTab : public CDialogEx
{
	DECLARE_DYNAMIC(SecondTab)

public:
	SecondTab(CWnd* pParent = NULL);   // 標準建構函式
	virtual ~SecondTab();

	// 對話方塊資料
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_Two_Tab };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支援
	COLORREF m_BorderColor;
	CComboBox m_LineTypeCombo;
	CWnd *m_pView;
	CWnd *m_pChildView;
	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct);
	afx_msg void OnCbnSelchangeCombo2();
	afx_msg void OnBnClickedButton1();
	void OnCancel() override;
	void SetpView(CWnd* pView);
};
