#include <GL/freeglut.h>
#define _USE_MATH_DEFINES
#include <math.h>

class Vetor {
public:
	Vetor(GLdouble x, GLdouble y)  { _x = x;  _y = y; }
	void SetX(GLdouble x) { _x = x; };
	void SetY(GLdouble y) { _y = y; };
	GLdouble GetX() const { return(_x); };
	GLdouble GetY() const { return(_y); };
	void add(Vetor _v) { _x += _v.GetX(); _y += _v.GetY(); };
	void sub(Vetor _v) { _x -= _v.GetX(); _y -= _v.GetY(); };
	void mult(GLdouble escala) { _x *= escala; _y *= escala; };
	void div(GLdouble escala) { _x /= escala; _y /= escala; };
private:
	GLdouble _x, _y;
};

Vetor _posicao(0.0f, 0.0f), _velocidade(0.02f, 0.03f);
GLdouble raioBola = 0.05f;
GLdouble bolaXMax, bolaXMin, bolaYMax, bolaYMin;
GLdouble margemEsquerda = -1, margemDireita = 1, margemSuperior = 1, margemInferior = -1;
int tempoRefresh = 30;

void desenha() {
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glTranslated(_posicao.GetX(), _posicao.GetY(), 0.0f);

	glBegin(GL_TRIANGLE_FAN);
	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex2f(0.0f, 0.0f);
	int numSegmentos = 100;
	GLdouble angulo;

	for (int i = 0; i <= numSegmentos; i++) {
		angulo = i * 2.0f * M_PI / numSegmentos;

		glVertex2d(cos(angulo) * raioBola, sin(angulo) * raioBola);
	}
	glEnd();

	glutSwapBuffers();
	_posicao.add(_velocidade);

	if ((_posicao.GetX() > bolaXMax) || (_posicao.GetX() < bolaXMin)) {
		_velocidade.SetX(-_velocidade.GetX());
	}

	if ((_posicao.GetY() > bolaYMax) || (_posicao.GetY() < bolaYMin)) {
		_velocidade.SetY(-_velocidade.GetY());
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