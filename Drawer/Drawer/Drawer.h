
// Drawer.h : main header file for the Drawer application
//
#pragma once

#ifndef __AFXWIN_H__
#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CDrawerApp:
// See Drawer.cpp for the implementation of this class
//

class CDrawerApp : public CWinApp
{
public:
	CDrawerApp() noexcept;


	// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

	// Implementation

public:
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CDrawerApp theApp;
