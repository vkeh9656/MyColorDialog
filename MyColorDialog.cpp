
// MyColorDialog.cpp: 애플리케이션에 대한 클래스 동작을 정의합니다.
//

#include "pch.h"
#include "framework.h"
#include "MyColorDialog.h"
#include "MyColorDialogDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMyColorDialogApp

BEGIN_MESSAGE_MAP(CMyColorDialogApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CMyColorDialogApp 생성

CMyColorDialogApp::CMyColorDialogApp()
{
	// TODO: 여기에 생성 코드를 추가합니다.
	// InitInstance에 모든 중요한 초기화 작업을 배치합니다.
}


// 유일한 CMyColorDialogApp 개체입니다.

CMyColorDialogApp theApp;


// CMyColorDialogApp 초기화

BOOL CMyColorDialogApp::InitInstance()
{
	CWinApp::InitInstance();

	CMyColorDialogDlg dlg;
	dlg.DoModal();
	
	return FALSE;
}

