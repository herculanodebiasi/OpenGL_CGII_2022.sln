#include <GL/freeglut.h>
#define _USE_MATH_DEFINES
#include <math.h>

GLfloat raioBola = 0.1f;
GLfloat bolaX = 0.0f;
GLfloat bolaY = 0.0f;
GLfloat bolaXMax, bolaXMin, bolaYMax, bolaYMin;
GLfloat velocidadeX = 0.04f;
GLfloat velocidadeY = 0.02f;

GLdouble clipAreaXLeft, clipAreaXRight, clipAreaYBottom, clipAreaYTop;
int tempoRefresh = 30;

void inicializaGL() {
	glClearColor(0.0, 0.0, 0.0, 1.0);
}

void desenha() {
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glTranslatef(bolaX, bolaY, 0.0f);

	glBegin(GL_TRIANGLE_FAN);
		glColor3f(0.0f, 0.0f, 1.0f);
		glVertex2f(0.0f, 0.0f);
		int numSegmentos = 100;
		GLfloat angulo;

		for (int i = 0; i <= numSegmentos; i++) {
			angulo = i * 2.0f * M_PI / numSegmentos;

			glVertex2f(cos(angulo) * raioBola, sin(angulo) * raioBola);
		}
	glEnd();

	glutSwapBuffers();

	bolaX += velocidadeX;
	bolaY += velocidadeY;
	
	if (bolaX > bolaXMax) {
		bolaX = bolaXMax;
		velocidadeX = -velocidadeX;
	}
	else if (bolaX < bolaXMin) {
		bolaX = bolaXMin;
		velocidadeX = -velocidadeX;
	}
	
	if (bolaY > bolaYMax) {
		bolaY = bolaYMax;
		velocidadeY = -velocidadeY;
	} else if (bolaY < bolaYMin) {
		bolaY = bolaYMin;
		velocidadeY = -velocidadeY;
	}
}

void reshape(GLsizei w, GLsizei h) {
	if (h == 0) h = 1;
	GLfloat aspecto = (GLfloat)w / (GLfloat)h;

	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	if (w >= h) {
		clipAreaXLeft = -1.0 * aspecto;
		clipAreaXRight = 1.0 * aspecto;
		clipAreaYBottom = -1.0;
		clipAreaYTop = 1.0;
	}
	else {
		clipAreaXLeft = -1.0;
		clipAreaXRight = 1.0;
		clipAreaYBottom = -1.0 / aspecto;
		clipAreaYTop = 1.0 / aspecto;
	}

	gluOrtho2D(clipAreaXLeft, clipAreaXRight, clipAreaYBottom, clipAreaYTop);

	bolaXMin = clipAreaXLeft + raioBola;
	bolaXMax = clipAreaXRight - raioBola;

	bolaYMin = clipAreaYBottom + raioBola;
	bolaYMax = clipAreaYTop - raioBola;

}

void timer(int valor) {
	glutPostRedisplay();
	glutTimerFunc(tempoRefresh, timer, 0);
}

int main(int argc, char **argv) {
	int windowWidth = 640;
	int windowHeight = 480;
	int windowPosX = 50;
	int windowPosY = 50;

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(windowWidth, windowHeight);
	glutInitWindowPosition(windowPosX, windowPosY);
	glutCreateWindow("Bouncing Ball");
	glutDisplayFunc(desenha);
	glutReshapeFunc(reshape);
	glutTimerFunc(0, timer, 0);
	inicializaGL();
	glutMainLoop();
	return(0);
}