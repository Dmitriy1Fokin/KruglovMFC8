
// PaintORama.h : ������� ���� ��������� ��� ���������� PROJECT_NAME
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�������� stdafx.h �� ��������� ����� ����� � PCH"
#endif

#include "resource.h"		// �������� �������


// CPaintORamaApp:
// � ���������� ������� ������ ��. PaintORama.cpp
//

class CPaintORamaApp : public CWinApp
{
public:
	CPaintORamaApp();

// ���������������
public:
	virtual BOOL InitInstance();

// ����������

	DECLARE_MESSAGE_MAP()
};

extern CPaintORamaApp theApp;
