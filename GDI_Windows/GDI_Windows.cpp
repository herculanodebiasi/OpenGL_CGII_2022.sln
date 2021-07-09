#include <windows.h>
#include <tchar.h>
#include <assert.h>

void CenterText(HDC hDC, int x, int y, LPCTSTR szFace, LPCTSTR szMessage, int point)
{
	HFONT hFont = CreateFont(
		point * GetDeviceCaps(hDC, LOGPIXELSY) / 72,
		0, 0, 0, FW_BOLD, TRUE, FALSE, FALSE,
		ANSI_CHARSET, OUT_TT_PRECIS, CLIP_DEFAULT_PRECIS,
		PROOF_QUALITY, VARIABLE_PITCH, szFace);

	assert(hFont);
	HGDIOBJ hOld = SelectObject(hDC, hFont);
	SetTextAlign(hDC, TA_CENTER | TA_BASELINE);
	SetBkMode(hDC, TRANSPARENT);
	SetTextColor(hDC, RGB(0, 0, 0xFF));
	TextOut(hDC, x, y, szMessage, _tcslen(szMessage));
	SelectObject(hDC, hOld);
	DeleteObject(hFont);
}

const TCHAR szMessage[] = _T("Olá Mundo!!!");
const TCHAR szFace[] = _T("Times New Roman");

void WinMainCRTStartup()
{
	HDC hDC = GetDC(NULL);
	assert(hDC);
	CenterText(hDC, GetSystemMetrics(SM_CXSCREEN) / 2,
		GetSystemMetrics(SM_CYSCREEN) / 2,
		szFace, szMessage, 72);
	ReleaseDC(NULL, hDC);
	ExitProcess(0);
}

//int WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR lpCmdLine, int nCmdShow)
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
{
	WinMainCRTStartup();
	return(0);
}
