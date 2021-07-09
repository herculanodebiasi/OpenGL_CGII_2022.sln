#include <gl/glut.h> 

void Desenha(void) {
	glClearColor(1, 1, 1, 1);
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0, 0, 0);
	glutWireCube(50);
	glFlush();
}

void output(GLfloat x, GLfloat y, char *text)
{
	char *p;

	glPushMatrix();
	glTranslatef(x, y, 0);
	for (p = text; *p; p++)
		glutStrokeCharacter(GLUT_STROKE_ROMAN, *p);
	glPopMatrix();
}

void text()
{
	char menu[80];
	strcpy_s(menu, "Have courage and be kind");
	int len;
	len = strlen(menu);

	glColor3f(0, 0, 0);

	glRasterPos3f(0, 0, 0);

	for (int i = 0; i < len; ++i)
	{
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, menu[i]);
	}
	glFlush();
}

void trocaModo(int modo) {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	if (modo == 0) 
	{
		glOrtho(-65.0, 65.0, -65.0, 65.0, -400.0, 400.0);
	}
	else 
	{
		gluPerspective(60.0, 1, 0.5, 500.0);
	}

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	output(0, 0, "Teste");
	gluLookAt(40, 60, 100, 0, 0, 0, 0, 1, 0);

}

void Inicializa() {
	trocaModo(0);	
}

void Teclado(unsigned char key, int x, int y) {
	switch (key) {
	case 27:
		exit(0);
	case 'O':
	case 'o':
		trocaModo(0);
		break;
	case 'P':
	case 'p':
		trocaModo(1);
		break;
	}
	glutPostRedisplay();
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(10, 10);
	glutCreateWindow("Exemplo de Projecao Ortografica/Perspectiva");
	glutDisplayFunc(Desenha);
	glutKeyboardFunc(Teclado);
	Inicializa();
	glutMainLoop();
}