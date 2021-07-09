#include <Windows.h>
#include <GL/gl.h>
#include <GL/GLU.h>

HINSTANCE hInstancia = NULL;	//Instância da aplicação
HDC hDC = NULL;					//Contexto de dispositivo GDI

LRESULT CALLBACK ProcessaJanela(HWND, UINT, WPARAM, LPARAM);	//Declaração da função WndProc

int IniciaOpenGL()
{
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	return(TRUE);
}

GLvoid ResizeGLScene(GLsizei width, GLsizei height)
{
	if (height == 0)
	{
		height = 1;
	}

	glViewport(0, 0, width, height);	//Resseta o viewport

	glMatrixMode(GL_PROJECTION);		//Seleciona a matriz de projeção
	glLoadIdentity();					//Resseta a matriz

	glMatrixMode(GL_MODELVIEW);			//Seleciona a matriz modelview
	glLoadIdentity();					//Resseta a matriz
}

int DesenhaOpenGL()
{
	glClear(GL_COLOR_BUFFER_BIT);

	glColor3f(1.0f, 0.0f, 0.0f);
	glBegin(GL_TRIANGLES);
	glVertex2f(0.0f, 0.5f);
	glVertex2f(-0.5f, -0.5f);
	glVertex2f(0.5f, -0.5f);
	glEnd();

	return(TRUE);
}

BOOL CriaJanelaOpenGL(wchar_t *titulo, int width, int height, int bits)
{
	wchar_t szNomeAplicacao[] = L"Principal";

	HWND hJanela = NULL;	//Handle da janela
	GLuint PixelFormat;		//Formato de pixel
	WNDCLASS classeJanela;	//Estrutura janela
	DWORD dwExStyle;		//Estilo estendido
	DWORD dwStyle;			//Estilo da janela
	HGLRC hRC = NULL;		//Contexto de renderização

	RECT WindowRect;		//Área retangular da janela
	WindowRect.left = (long)0;
	WindowRect.right = (long)width;
	WindowRect.top = (long)0;
	WindowRect.bottom = (long)height;

	hInstancia = GetModuleHandle(NULL);
	classeJanela.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	classeJanela.lpfnWndProc = (WNDPROC)ProcessaJanela;
	classeJanela.cbClsExtra = 0;
	classeJanela.cbWndExtra = 0;
	classeJanela.hInstance = hInstancia;
	classeJanela.hIcon = LoadIcon(NULL, IDI_WINLOGO);
	classeJanela.hCursor = LoadCursor(NULL, IDC_ARROW);
	classeJanela.hbrBackground = NULL;
	classeJanela.lpszMenuName = NULL;
	//classeJanela.lpszClassName = (LPCWSTR)szNomeAplicacao;
	classeJanela.lpszClassName = L"OpenGL";

	dwExStyle = WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;
	dwStyle = WS_OVERLAPPEDWINDOW;

	if (!RegisterClass(&classeJanela))
	{
		MessageBox(NULL, L"Falha em registrar a classe Window", L"ERROR", MB_OK | MB_ICONEXCLAMATION);
		return(FALSE);
	}

	dwExStyle = WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;
	dwStyle = WS_OVERLAPPEDWINDOW;

	AdjustWindowRectEx(&WindowRect, dwStyle, FALSE, dwExStyle);

	hJanela = CreateWindowEx(dwExStyle,
		L"OpenGL",
		(LPCWSTR)titulo,
		WS_CLIPSIBLINGS | WS_CLIPCHILDREN | dwStyle,
		0, 0,
		WindowRect.right - WindowRect.left,
		WindowRect.bottom - WindowRect.top,
		NULL,
		NULL,
		hInstancia,
		NULL);

	static PIXELFORMATDESCRIPTOR pfd = { sizeof(PIXELFORMATDESCRIPTOR),
		1,
		PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,
		PFD_TYPE_RGBA,
		bits,
		0, 0, 0, 0, 0, 0,
		0,
		0,
		0,
		0, 0, 0, 0,
		16,
		0,
		0,
		PFD_MAIN_PLANE,
		0,
		0, 0, 0
	};

	hDC = GetDC(hJanela);
	PixelFormat = ChoosePixelFormat(hDC, &pfd);
	SetPixelFormat(hDC, PixelFormat, &pfd);
	hRC = wglCreateContext(hDC);
	wglMakeCurrent(hDC, hRC);

	ShowWindow(hJanela, SW_SHOW);
	UpdateWindow(hJanela);
	SetForegroundWindow(hJanela);
	SetFocus(hJanela);
	ResizeGLScene(width, height);

	if (!IniciaOpenGL())
	{
		MessageBox(NULL, L"Falha de Inicialização", L"ERROR", MB_OK | MB_ICONEXCLAMATION);
		return(FALSE);
	}

	return(TRUE);
}

LRESULT CALLBACK ProcessaJanela(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		return(0);
	case WM_SIZE:
		ResizeGLScene(LOWORD(lParam), HIWORD(lParam));
	}

	return(DefWindowProc(hWnd, uMsg, wParam, lParam));
}

int WINAPI WinMain(HINSTANCE hCopia, HINSTANCE hCopiaAnterior, LPSTR szLinhaCmd, int iCmdMostrar)
{
	MSG msg;
	BOOL done = FALSE;
	CriaJanelaOpenGL(L"Unoesc OpenGL", 640, 480, 16);

	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);

		DesenhaOpenGL();
		SwapBuffers(hDC);
	}

	return msg.wParam;

}