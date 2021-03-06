// App.cpp : Defines the entry point for the application.
//
#include "stdafx.h"
#include "resource.h"
#include "MainWnd.h"
//#include "InitDevice.h"
#include <windows.h>
#include <objbase.h>
#include <shellapi.h>
#include "QMFileSqlite.h"
#include "RegUserInfo.h"
#include "log.h"


#include "THFaceImage_i.h"
#include "THFeature_i.h"

void Show_HideTask(bool IsHide)
{
	int nCwdShow = -1;
	LPARAM lParam;
	HWND task = FindWindow(_T("Shell_TrayWnd"), NULL);
	if (IsHide)
	{
		lParam = ABS_AUTOHIDE | ABS_ALWAYSONTOP;
		nCwdShow = SW_HIDE;
	}
	else
	{
		lParam = ABS_ALWAYSONTOP;
		nCwdShow = SW_SHOW;
	}

	::ShowWindow(task, nCwdShow);

	APPBARDATA apBar;
	memset(&apBar, 0, sizeof(apBar));
	apBar.cbSize = sizeof(apBar);
	apBar.hWnd = task;
	if (apBar.hWnd != NULL)
	{
		apBar.lParam = lParam;
		SHAppBarMessage(ABM_SETSTATE, &apBar);
	}
}

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE /*hPrevInstance*/, LPSTR /*lpCmdLine*/, int nCmdShow)
{
	CPaintManagerUI::SetInstance(hInstance);
	CPaintManagerUI::SetResourcePath(CPaintManagerUI::GetInstancePath() + _T("skin"));

	HRESULT Hr = ::CoInitialize(NULL);
	if (FAILED(Hr)) return 0;

	Loggering::Logger_initiation();

	//init face
	THFI_Param param;
	param.nMinFaceSize = 150;
	param.nRollAngle = 145;
	param.bOnlyDetect = true;
	THFI_Create(1, &param);

	short ret = EF_Init(1);
	if (ret == 1)
	{
		cout << "Feature init ok" << endl;
	}


	//init database
	QFileSqlite *pDb = QFileSqlite::getInstance();
	pDb->createTable(CREATE_USER_INFO_TABLE);
	//CInitDevice	Init_Device;
	//Init_Device.InitStart();

	//init userinfo
	RegUserInfo::init();

	std::auto_ptr<CMainWnd> pFrame(new CMainWnd);
	assert(pFrame.get());
	pFrame->Create(NULL, NULL, UI_WNDSTYLE_DIALOG, WS_EX_WINDOWEDGE | WS_EX_ACCEPTFILES);
	pFrame->SetIcon(IDI_ICON1);
	pFrame->CenterWindow();
	pFrame->ShowWindow(true);
	
//	Show_HideTask(true);

	CPaintManagerUI::MessageLoop();
	::CoUninitialize();

	THFI_Release();
	EF_Release();

	return 0;
}
