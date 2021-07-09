#include <Windows.h>
#include <GL/gl.h>
#include <GL/GLU.h>

LRESULT CALLBACK ProcessaJanela(HWND, UINT, WPARAM, LPARAM);	//Declaração da função ProcessaJanela

int DesenhaOpenGL()
{
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	glColor3f(1.0f, 0.0f, 0.0f);
	glBegin(GL_TRIANGLES);
		glVertex2f(0.0f, 0.5f);
		glVertex2f(-0.5f, -0.5f);
		glVertex2f(0.5f, -0.5f);
	glEnd();
	glFlush();

	return(TRUE);
}

BOOL CriaJanelaOpenGL(wchar_t *titulo, int comprimento, int altura, int bits)
{
	HINSTANCE hInstancia = NULL;	//Instância da aplicação
	HWND hJanela = NULL;			//Handle da janela
	GLuint PixelFormat;				//Formato de pixel
	WNDCLASS classeJanela;			//Estrutura janela

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
	classeJanela.lpszClassName = L"OpenGL";

	//Tenta registrar a classe de janela
	if (!RegisterClass(&classeJanela))
	{
		MessageBox(NULL, L"Falha em registrar a classe Window", L"ERROR", MB_OK | MB_ICONEXCLAMATION);
		return(FALSE);
	}

	//Cria janela
	hJanela = CreateWindowEx(
		WS_EX_APPWINDOW | WS_EX_WINDOWEDGE,
		L"OpenGL",
		(LPCWSTR)titulo,
		WS_CLIPSIBLINGS | WS_CLIPCHILDREN | WS_OVERLAPPEDWINDOW,
		0, 0,
		comprimento,
		altura,
		NULL,
		NULL,
		hInstancia,
		NULL
	);

	//Define o formato de vídeo
	static PIXELFORMATDESCRIPTOR pfd = { 
		sizeof(PIXELFORMATDESCRIPTOR),
		1,
		PFD_SUPPORT_OPENGL,
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

	HDC hDC = NULL;					//Contexto de dispositivo GDI
	HGLRC hRC = NULL;				//Contexto de renderização

	hDC = GetDC(hJanela);			//Recupera o dispositivo de contexto

	PixelFormat = ChoosePixelFormat(hDC, &pfd);	//Procura um formato de pixel apropriado
	SetPixelFormat(hDC, PixelFormat, &pfd);		//Define o formato de pixel

	hRC = wglCreateContext(hDC);	//Cria um contexto de renderização
	wglMakeCurrent(hDC, hRC);		//Ativa o contexto de renderização

	ShowWindow(hJanela, SW_SHOW);	//Mostra a janela

	return(TRUE);
}

//Função callback que processa as mensagens recebidas pela janela
LRESULT CALLBACK ProcessaJanela(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_DESTROY:		//Fechamento da janela
		PostQuitMessage(0);
		return(0);
	}

	//Repassa todas as mensagens não tratadas para DefWindowProc()
	return(DefWindowProc(hWnd, uMsg, wParam, lParam));
}

//Função principal
int WINAPI WinMain(HINSTANCE hCopia, HINSTANCE hCopiaAnterior, LPSTR szLinhaCmd, int iCmdMostrar)
{
	MSG msg;
	CriaJanelaOpenGL(L"Unoesc OpenGL", 640, 480, 16);

	//Laço para tratamento de mensagens
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);

		DesenhaOpenGL();
	}

	return msg.wParam;
}