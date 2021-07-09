#include <Windows.h>
#include <GL/gl.h>
#include <GL/GLU.h>

HGLRC hRC = NULL;				//Contexto de renderização
HDC hDC = NULL;					//Contexto de dispositivo GDI
HWND hWnd = NULL;				//Handle da janela
HINSTANCE hInstance = NULL;		//Instância da aplicação

bool keys[256];					//Arranjo utilizado pela rotina de teclado
bool active = TRUE;				//Flag de janela ativa
bool fullscreen = TRUE;			//Flag de tela cheia

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);	//Declaração da função WndProc

GLvoid ResizeGLScene(GLsizei width, GLsizei height)
{
	if (height == 0)
	{
		height = 1;
	}

	glViewport(0, 0, width, height);	//Resseta o viewport

	glMatrixMode(GL_PROJECTION);		//Seleciona a matriz de projeção
	glLoadIdentity();					//Resseta a matriz

	gluPerspective(45.0f, (GLfloat)width / (GLfloat)height, 0.1f, 100.0f);

	glMatrixMode(GL_MODELVIEW);			//Seleciona a matriz modelview
	glLoadIdentity();					//Resseta a matriz
}

int InitGL()
{
	glShadeModel(GL_SMOOTH);			//Sombreamento suave
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClearDepth(1.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

	return(TRUE);
}

int DrawGLScene()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	glTranslatef(0.0f, 0.0f, -3.0f);
	glColor3f(1.0f, 0.0f, 0.0f);
	glBegin(GL_TRIANGLES);                
		glVertex2f(0.0f, 0.5f);              
		glVertex2f(-0.5f, -0.5f);             
		glVertex2f(0.5f, -0.5f);              
	glEnd();                           

	return(TRUE);
}

GLvoid KillGLWindow()
{
	if (fullscreen)
	{
		ChangeDisplaySettings(NULL, 0);
		ShowCursor(TRUE);
	}

	if (hRC)
	{
		if (!wglMakeCurrent(NULL, NULL)) 
		{
			MessageBox(NULL, L"Liberação do DC e RC falhou.", L"SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION);
		}

		if (!wglDeleteContext(hRC))
		{
			MessageBox(NULL, L"Liberação do Contexto de Renderização falhou.", L"SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION);
		}
		hRC = NULL;
	}

	if (hDC && !ReleaseDC(hWnd, hDC)) 
	{
		MessageBox(NULL, L"Liberação do Contexto de Dispositivo falhou.", L"SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION);
		hDC = NULL;
	}

	if (hWnd && !DestroyWindow(hWnd))
	{
		MessageBox(NULL, L"Não consegui liberar hWnd.", L"SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION);
		hWnd = NULL;
	}

	if (!UnregisterClass(L"OpenGL", hInstance))
	{
		MessageBox(NULL, L"Não consegui desregistrar a classe", L"SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION);
		hInstance = NULL;
	}
}

BOOL CreateGLWindow(wchar_t *title, int width, int height, int bits, bool fullscreenflag)
{
	GLuint PixelFormat;		//Formato de pixel
	WNDCLASS wc;			//Estrutura janela
	DWORD dwExStyle;		//Estilo estendido
	DWORD dwStyle;			//Estilo da janela

	RECT WindowRect;		//Área retangular da janela
	WindowRect.left = (long)0;
	WindowRect.right = (long)width;
	WindowRect.top = (long)0;
	WindowRect.bottom = (long)height;

	fullscreen = fullscreenflag;

	hInstance = GetModuleHandle(NULL);
	wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	wc.lpfnWndProc = (WNDPROC)WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = LoadIcon(NULL, IDI_WINLOGO);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = NULL;
	wc.lpszMenuName = NULL;
	wc.lpszClassName = L"OpenGL";

	if (!RegisterClass(&wc))
	{
		MessageBox(NULL, L"Falha em registrar a classe Window", L"ERROR", MB_OK | MB_ICONEXCLAMATION);
		return(FALSE);
	}

	if (fullscreen)
	{
		DEVMODE dmScreenSettings;
		memset(&dmScreenSettings, 0, sizeof(dmScreenSettings));

		dmScreenSettings.dmSize = sizeof(dmScreenSettings);
		dmScreenSettings.dmPelsWidth = width;
		dmScreenSettings.dmPelsHeight = height;
		dmScreenSettings.dmBitsPerPel = bits;
		dmScreenSettings.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;

		if (ChangeDisplaySettings(&dmScreenSettings, CDS_FULLSCREEN) != DISP_CHANGE_SUCCESSFUL)
		{
			if (MessageBox(NULL, L"Modo de tela cheia não é suportado pelo hardware de vídeo. Usar modo enjanelado?", L"Unoesc OpenGL", MB_YESNO | MB_ICONEXCLAMATION) == IDYES)
			{
				fullscreen = FALSE;
			}
			else
			{
				MessageBox(NULL, L"Programa irá fechar agora", L"ERROR", MB_OK | MB_ICONSTOP);
				return(FALSE);
			}
		}
	}

	if (fullscreen) 
	{
		dwExStyle = WS_EX_APPWINDOW;
		dwStyle = WS_POPUP;
		ShowCursor(FALSE);
	}
	else
	{
		dwExStyle = WS_EX_APPWINDOW|WS_EX_WINDOWEDGE;
		dwStyle = WS_OVERLAPPEDWINDOW;
	}

	AdjustWindowRectEx(&WindowRect, dwStyle, FALSE, dwExStyle);

	if (!(hWnd = CreateWindowEx(dwExStyle,
		L"OpenGL",
		(LPCWSTR)title,
		WS_CLIPSIBLINGS | WS_CLIPCHILDREN | dwStyle,
		0, 0,
		WindowRect.right - WindowRect.left,
		WindowRect.bottom - WindowRect.top,
		NULL,
		NULL,
		hInstance,
		NULL)))
	{
		KillGLWindow();
		MessageBox(NULL, L"Erro na criação da janela", L"ERROR", MB_OK | MB_ICONEXCLAMATION);
		return(FALSE);
	}

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

	if (!(hDC = GetDC(hWnd)))
	{
		KillGLWindow();
		MessageBox(NULL, L"Não consigo criar um contexto de dispositivo GL", L"ERROR", MB_OK | MB_ICONEXCLAMATION);
		return(FALSE);
	}

	if (!(PixelFormat = ChoosePixelFormat(hDC, &pfd))) 
	{
		KillGLWindow();
		MessageBox(NULL, L"Não consigo encontrar um PixelFormat apropriado", L"ERROR", MB_OK | MB_ICONEXCLAMATION);
		return(FALSE);
	}

	if (!SetPixelFormat(hDC, PixelFormat, &pfd))
	{
		KillGLWindow();
		MessageBox(NULL, L"Não consigo setar o PixelFormat", L"ERROR", MB_OK | MB_ICONEXCLAMATION);
		return(FALSE);
	}

	if (!(hRC = wglCreateContext(hDC)))
	{
		KillGLWindow();
		MessageBox(NULL, L"Não consigo criar um contexto de renderização GL", L"ERROR", MB_OK | MB_ICONEXCLAMATION);
		return(FALSE);
	}

	if (!wglMakeCurrent(hDC, hRC))
	{
		KillGLWindow();
		MessageBox(NULL, L"Não consigo ativar o contexto de renderização GL", L"ERROR", MB_OK | MB_ICONEXCLAMATION);
		return(FALSE);
	}

	ShowWindow(hWnd, SW_SHOW);
	SetForegroundWindow(hWnd);
	SetFocus(hWnd);
	ResizeGLScene(width, height);

	if (!InitGL())
	{
		KillGLWindow();
		MessageBox(NULL, L"Falha de Inicialização", L"ERROR", MB_OK | MB_ICONEXCLAMATION);
		return(FALSE);
	}

	return(TRUE);
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_ACTIVATE:
		if (!HIWORD(wParam))
		{
			active = TRUE;
		}
		else
		{
			active = FALSE;
		}
		return(0);
	case WM_SYSCOMMAND:
		switch (wParam)
		{
		case SC_SCREENSAVE:
		case SC_MONITORPOWER:
			return(0);
		}
		break;
	case WM_CLOSE:
		PostQuitMessage(0);
		return(0);
	case WM_KEYDOWN:
		keys[wParam] = TRUE;
		return(0);
	case WM_KEYUP:
		keys[wParam] = FALSE;
		return(0);
	case WM_SIZE:
		ResizeGLScene(LOWORD(lParam), HIWORD(lParam));
		return(0);
	}

	return(DefWindowProc(hWnd, uMsg, wParam, lParam));
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	MSG msg;
	BOOL done = FALSE;

	if (MessageBox(NULL, L"Gostaria de rodar em modo de tela cheia?", L"Iniciar tela cheia?", MB_YESNO | MB_ICONQUESTION) == IDNO)
	{
		fullscreen = FALSE;
	}

	if (!CreateGLWindow(L"Unoesc OpenGL", 640, 480, 16, fullscreen))
	{
		return(0);
	}

	while (!done)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
			{
				done = TRUE;
			}
			else
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}

		if (active)
		{
			if (keys[VK_ESCAPE])
			{
				done = TRUE;
			}
			else
			{
				DrawGLScene();
				SwapBuffers(hDC);
			}
		}

		if (keys[VK_F1])
		{
			keys[VK_F1] = FALSE;
			KillGLWindow();
			fullscreen = !fullscreen;
			if (!CreateGLWindow(L"Unoesc OpenGL", 640, 480, 16, fullscreen))
			{
				return(0);
			}
		}
	}
}