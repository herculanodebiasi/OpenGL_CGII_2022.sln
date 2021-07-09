#include <stdlib.h>
#include <GL/glut.h>

GLfloat Xi = 0.0f, Yi = 0.0f;
GLfloat Xf = 0.0f, Yf = 0.0f;

double passo = 0.5f;

void desenha(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glColor3f(1.0, 0.0, 1.0);
	glBegin(GL_QUADS);
		glVertex3f(-0.25, -0.25, 0.0);
		glVertex3f(0.25, -0.25, 0.0);
		glVertex3f(0.25, 0.25, 0.0);
		glVertex3f(-0.25, 0.25, 0.0);
	glEnd();

	glFlush();
}

void atualizaDisplay() {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-1.0 + Xi, 1.0 + Xf, -1.0 + Yi, 1.0 + Yf);
	glutPostRedisplay();
}

void teclasNormais(unsigned char key, int x, int y)
{
	if (key == 'q' || key == 'Q' || key == 27) {
		exit(0);
	}

	switch (key) {
	case '+':
		Xi += passo; Xf -= passo;
		Yi += passo; Yf -= passo;
		break;
	case '-':
		Xi -= passo; Xf += passo;
		Yi -= passo; Yf += passo;
		break;
	}

	atualizaDisplay();
}

void teclasEspeciais(int key, int x, int y) 
{
	switch (key) {
	case GLUT_KEY_LEFT:
		Xi -= passo; Xf -= passo;
		break;
	case GLUT_KEY_RIGHT:
		Xi += passo; Xf += passo;
		break;
	case GLUT_KEY_UP:
		Yi += passo; Yf += passo;
		break;
	case GLUT_KEY_DOWN:
		Yi -= passo; Yf -= passo;
		break;
	}

	atualizaDisplay();
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Navegação");

	glutDisplayFunc(desenha);
	glutKeyboardFunc(teclasNormais);
	glutSpecialFunc(teclasEspeciais);

	glutMainLoop();

	return 0;
}