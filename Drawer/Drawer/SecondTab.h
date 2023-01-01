#pragma once
#include <afxdialogex.h>

// SecondTab ��ܤ��

class SecondTab : public CDialogEx
{
	DECLARE_DYNAMIC(SecondTab)

public:
	SecondTab(CWnd* pParent = NULL);   // �зǫغc�禡
	virtual ~SecondTab();

	// ��ܤ�����
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_Two_Tab };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �䴩
	COLORREF bntColors;
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct);
	CComboBox m_LineTypeCombo;
	CWnd* m_pView;
	void OnCancel() override;
	afx_msg void OnCbnSelchangeCombo2();
	afx_msg void OnBnClickedButton1();
};
