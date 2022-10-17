#include <windows.h>
#include <gl/freeglut.h>

bool tela_cheia = false;
int largura = 800, altura = 600;
int pos_x, pos_y;

void desenha(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glBegin(GL_TRIANGLES);
	glColor3f(1, 0, 0);
	glVertex2f(-0.5, -0.5);

	glColor3f(0, 1, 0);
	glVertex2f(0.5, -0.5);

	glColor3f(0, 0, 1);
	glVertex2f(0.0, 0.5);
	glEnd();

	glutSwapBuffers();
}

void teclado(unsigned char key, int x, int y)
{
	if (key == 'q' || key == 'Q' || key == 27) {
		exit(0);
	}
	else if (key == 'F' || key == 'f') {
		if (tela_cheia) {
			glutReshapeWindow(largura, altura);
			glutPositionWindow(pos_x, pos_y);
		}
		else {
			glutFullScreen();
		}

		tela_cheia = !tela_cheia;
	}
}

void ocioso(void) {
	if (!tela_cheia) {
		pos_x = glutGet(GLUT_WINDOW_X);
		pos_y = glutGet(GLUT_WINDOW_Y);
	}
}

void inicializa() {
	pos_x = (glutGet(GLUT_SCREEN_WIDTH) / 2) - (largura / 2);
	pos_y = (glutGet(GLUT_SCREEN_HEIGHT) / 2) - (altura / 2);
}

int APIENTRY WinMain(HINSTANCE hThisInstance, HINSTANCE hPrevInstance, LPSTR lpszArgument, int nFunsterStil)
{
	glutInit(&__argc, __argv);
	inicializa();

	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(largura, altura);
	glutInitWindowPosition(pos_x, pos_y);
	glutCreateWindow("Primeira Janela OpenGL");

	glEnable(GL_DEPTH_TEST);

	glutDisplayFunc(desenha);
	glutIdleFunc(ocioso);
	glutKeyboardFunc(teclado);

	glutMainLoop();

	return 0;
}