// dllmain.cpp : 定义 DLL 应用程序的入口点。
#include "stdafx.h"
#include <Windows.h>
#include "resource.h"
#include "RecvMessage.h"
INT_PTR CALLBACK DialogProc(
	_In_ HWND   hwndDlg,
	_In_ UINT   uMsg,
	_In_ WPARAM wParam,
	_In_ LPARAM lParam
);
VOID ShowUI(HMODULE hModule);

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
		CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)ShowUI, hModule, NULL, 0);
		break;
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

VOID ShowUI(HMODULE hModule)
{
	DialogBox(hModule, MAKEINTRESOURCE(MAIN), NULL, &DialogProc);
}

INT_PTR CALLBACK DialogProc(
	_In_ HWND   hwndDlg,
	_In_ UINT   uMsg,
	_In_ WPARAM wParam,
	_In_ LPARAM lParam
)
{
	DWORD hookAdd = getWechatWin() + 0x305753;
	switch (uMsg)
	{
	case WM_INITDIALOG:
		break;
	case WM_CLOSE:
		EndDialog(hwndDlg,0);
		break;
	case WM_COMMAND:
		if (wParam == RECV) {
			MessageBox(NULL, L"到了", L"哈哈", 0);
			HookWechatQrcode(hwndDlg, hookAdd);
		}
		break;
	default:
		break;
	}
	return FALSE;
}