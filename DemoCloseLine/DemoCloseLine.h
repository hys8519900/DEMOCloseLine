
// DemoCloseLine.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CDemoCloseLineApp:
// �йش����ʵ�֣������ DemoCloseLine.cpp
//

class CDemoCloseLineApp : public CWinApp
{
public:
	CDemoCloseLineApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CDemoCloseLineApp theApp;