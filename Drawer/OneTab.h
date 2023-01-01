#pragma once
#include <afxdialogex.h>

class OneTab : public CDialogEx
{
	DECLARE_DYNAMIC(OneTab)

public:
	OneTab(CWnd *pParent = NULL);   // �зǫغc�禡
	virtual ~OneTab();

	// ��ܤ�����
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_One_Tab };
#endif

protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV �䴩
	COLORREF m_BorderColor[2];
	CButton m_ForeColor;
	CButton m_BgColor;
	bool m_ItemIsBg;
	CWnd *m_pView;
	CWnd *m_pChildView;


	DECLARE_MESSAGE_MAP()
public:
	void OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct);
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedCheck1();
	void  OnCancel() override;
	void SetpView(CWnd *pView);

};


