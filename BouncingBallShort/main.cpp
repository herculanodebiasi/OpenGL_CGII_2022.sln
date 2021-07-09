#include <GL/freeglut.h>
#define _USE_MATH_DEFINES
#include <math.h>

GLdouble raioBola = 0.05f;
GLdouble bolaX = 0.0f;
GLdouble bolaY = 0.0f;

GLdouble bolaXMax, bolaXMin, bolaYMax, bolaYMin;
GLdouble margemEsquerda=-1, margemDireita=1, margemSuperior=1, margemInferior=-1;

GLdouble velocidadeX = 0.05f;
GLdouble velocidadeY = 0.09f;
int tempoRefresh = 30;

void desenha() {
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glTranslatef(bolaX, bolaY, 0.0f);

	glBegin(GL_TRIANGLE_FAN);
		glColor3f(0.0f, 0.0f, 1.0f);
		glVertex2f(0.0f, 0.0f);
		int numSegmentos = 100;
		GLdouble angulo;

		for (int i = 0; i <= numSegmentos; i++) {
			angulo = i * 2.0f * M_PI / numSegmentos;

			glVertex2f(cos(angulo) * raioBola, sin(angulo) * raioBola);
		}
	glEnd();

	glutSwapBuffers();

	bolaX += velocidadeX;
	bolaY += velocidadeY;

	if ((bolaX > bolaXMax) || (bolaX < bolaXMin)) {
		velocidadeX = -velocidadeX;
	}

	if ((bolaY > bolaYMax) || (bolaY < bolaYMin)) {
		velocidadeY = -velocidadeY;
	}
}

void timer(int valor) {
	glutPostRedisplay();
	glutTimerFunc(tempoRefresh, timer, 0);
}

int main(int argc, char **argv) {
	bolaXMin = margemEsquerda + raioBola;
	bolaXMax = margemDireita - raioBola;

	bolaYMin = margemInferior + raioBola;
	bolaYMax = margemSuperior - raioBola;

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(50, 50);
	glutCreateWindow("Bouncing Ball");
	glutDisplayFunc(desenha);
	glutTimerFunc(0, timer, 0);
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glutMainLoop();
	return(0);
}