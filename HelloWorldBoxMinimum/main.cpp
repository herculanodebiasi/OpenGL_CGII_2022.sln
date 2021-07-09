#include <windows.h>
#include <tchar.h>

LRESULT CALLBACK ProcessaJanela(HWND, UINT, WPARAM, LPARAM);
wchar_t szNomeAplicacao[] = L"Principal";

LRESULT CALLBACK ProcessaJanela(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	HDC hdc; 
	PAINTSTRUCT ps;
	RECT rect; 
	
	switch (uMsg)
	{
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
			GetClientRect(hWnd, &rect);
			DrawText(hdc, L"Olá Mundo!", -1, &rect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
		EndPaint(hWnd, &ps);

		return 0; 
	case WM_DESTROY:
		PostQuitMessage(0);
		return(0);
	}

	return(DefWindowProc(hWnd, uMsg, wParam, lParam));
}

int WINAPI WinMain(HINSTANCE hCopia, HINSTANCE hCopiaAnterior, LPSTR szLinhaCmd, int iCmdMostrar)
{
	HWND hJanela;
	MSG msg;
	WNDCLASS classeJanela;

	classeJanela.style = CS_HREDRAW | CS_VREDRAW;
	classeJanela.lpfnWndProc = ProcessaJanela;
	classeJanela.cbClsExtra = 0;
	classeJanela.cbWndExtra = 0;
	classeJanela.hInstance = hCopia;
	classeJanela.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	classeJanela.hCursor = LoadCursor(NULL, IDC_ARROW);
	classeJanela.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	classeJanela.lpszMenuName = NULL;
	classeJanela.lpszClassName = szNomeAplicacao;

	if (!RegisterClass(&classeJanela)) {
		return(0);
	}

	hJanela = CreateWindow(szNomeAplicacao, L"Janela Principal", WS_OVERLAPPEDWINDOW, 100, 100, 400, 400, HWND_DESKTOP, NULL, hCopia, NULL);
	ShowWindow(hJanela, iCmdMostrar);
	UpdateWindow(hJanela);

	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return msg.wParam;
}
