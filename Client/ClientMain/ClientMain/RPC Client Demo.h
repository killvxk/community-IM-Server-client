
// RPC Client Demo.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CRPCClientDemoApp:
// �йش����ʵ�֣������ RPC Client Demo.cpp
//

class CRPCClientDemoApp : public CWinApp
{
public:
	CRPCClientDemoApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CRPCClientDemoApp theApp;