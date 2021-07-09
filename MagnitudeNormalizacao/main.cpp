#include <GL/freeglut.h>
#define _USE_MATH_DEFINES
#include <math.h>
#include <iostream>

class Vetor {
public:
	Vetor(GLdouble x, GLdouble y)  { _x = x;  _y = y; }

	void SetX(GLdouble x) { _x = x; };
	void SetY(GLdouble y) { _y = y; };

	GLdouble GetX() const { return(_x); };
	GLdouble GetY() const { return(_y); };

	void add(Vetor _v) {
		_x += _v.GetX();
		_y += _v.GetY();
	};

	void sub(Vetor _v) {
		_x -= _v.GetX();
		_y -= _v.GetY();
	};

	void mult(GLdouble escala) {
		_x *= escala;
		_y *= escala;
	};

	void div(GLdouble escala) {
		_x /= escala;
		_y /= escala;
	};

	GLdouble mag() {
		return(sqrt((_x*_x) + (_y*_y)));
	};

	void normalize() {
		GLfloat m = mag();

		if (m > 0) {
			div(m);
		}
	};
private:
	GLdouble _x, _y;
};

GLdouble margemEsquerda = 0, margemDireita = 500, margemInferior = 500, margemSuperior = 0;
GLdouble width = (margemDireita - margemEsquerda);
GLdouble height = (margemInferior - margemSuperior);

double _m;
Vetor _mouse(0, 0);

void desenha() {
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluOrtho2D(margemEsquerda, margemDireita, margemInferior, margemSuperior);
	
	glColor3f(0.75f, 0.75f, 0.75f);
	glBegin(GL_QUADS);
		glVertex2d(0.0f, 0.0f);
		glVertex2d(0.0f, 500.0f);
		glVertex2d(500.0f, 500.0f);
		glVertex2d(500.0f, 0.0f);
	glEnd();

	_mouse.normalize();
	_mouse.mult(50);

	glLineWidth(5);
	glColor3f(1.0f, 0.0f, 0.0f);
	glTranslated(width / 2.0, height / 2.0, 0.0f);
	
	glBegin(GL_LINES);
		glVertex2d(0.0f, 0.0f);
		glVertex2d(_mouse.GetX(), _mouse.GetY());
	glEnd();

	glutSwapBuffers();
}

void mouse(int x, int y) {
	_mouse=Vetor(x, y);
	Vetor canto(width / 2.0, height / 2.0);
	_mouse.sub(canto);
	_m = _mouse.mag();

	std::cout << _m << std::endl;

	glutPostRedisplay();
}

int main(int argc, char **argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(50, 50);
	glutCreateWindow("Vetor Normalizado");
	glutDisplayFunc(desenha);
	glutPassiveMotionFunc(mouse);
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glutMainLoop();
	return(0);
}