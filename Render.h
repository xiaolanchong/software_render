// Render.h : main header file for the Render application
//
#pragma once

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols


// CRenderApp:
// See Render.cpp for the implementation of this class
//

class CRenderApp : public CWinApp
{
public:
	CRenderApp();


// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CRenderApp theApp;