#include <windows.h>  
#include <GL/glut.h>  

void desenha() {
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f); 
	glClear(GL_COLOR_BUFFER_BIT);  

	glBegin(GL_QUADS);              
		glColor3f(1.0f, 0.0f, 0.0f); // Vermelho
		glVertex2f(-0.8f, 0.1f); glVertex2f(-0.2f, 0.1f);     
		glVertex2f(-0.2f, 0.7f); glVertex2f(-0.8f, 0.7f);

		glColor3f(0.0f, 1.0f, 0.0f); // Verde
		glVertex2f(-0.7f, -0.6f); glVertex2f(-0.1f, -0.6f);
		glVertex2f(-0.1f, 0.0f);  glVertex2f(-0.7f, 0.0f);

		glColor3f(0.2f, 0.2f, 0.2f); // Cinza claro
		glVertex2f(-0.9f, -0.7f);
		glColor3f(1.0f, 1.0f, 1.0f); // Branco
		glVertex2f(-0.5f, -0.7f);
		glColor3f(0.2f, 0.2f, 0.2f); // Cinza escuro
		glVertex2f(-0.5f, -0.3f);
		glColor3f(1.0f, 1.0f, 1.0f); // Branco
		glVertex2f(-0.9f, -0.3f);
	glEnd();

	glBegin(GL_TRIANGLES);          
		glColor3f(0.0f, 0.0f, 1.0f); // Azul
		glVertex2f(0.1f, -0.6f); glVertex2f(0.7f, -0.6f); glVertex2f(0.4f, -0.1f);

		glColor3f(1.0f, 0.0f, 0.0f); // Vermelho
		glVertex2f(0.3f, -0.4f);
		glColor3f(0.0f, 1.0f, 0.0f); // Verde
		glVertex2f(0.9f, -0.4f);
		glColor3f(0.0f, 0.0f, 1.0f); // Azul
		glVertex2f(0.6f, -0.9f);
	glEnd();

	glBegin(GL_POLYGON);            
		glColor3f(1.0f, 1.0f, 0.0f); // Amarelo
		glVertex2f(0.4f, 0.2f); glVertex2f(0.6f, 0.2f);
		glVertex2f(0.7f, 0.4f); glVertex2f(0.6f, 0.6f);
		glVertex2f(0.4f, 0.6f); glVertex2f(0.3f, 0.4f);
	glEnd();

	glFlush(); 
}

void redimensiona(GLsizei width, GLsizei height) { 
	// Calcula a proporção da janela
	if (height == 0) 
	{
		height = 1;	//Evita divisão por 0
	}

	GLfloat aspecto = (GLfloat)width / (GLfloat)height;

	glViewport(0, 0, width, height);

	glMatrixMode(GL_PROJECTION);  
	glLoadIdentity();             
	if (width >= height) 
	{
		// aspecto >= 1, define a altura para -1 to 1, com comprimento maior
		//glViewport(0, 0, height*aspecto, height);
		gluOrtho2D(-1.0 * aspecto, 1.0 * aspecto, -1.0, 1.0);
	}
	else 
	{
		// aspecto < 1, define o comprimento para -1 to 1, com altura maior
		//glViewport(0, 0, width, width / aspecto);
		gluOrtho2D(-1.0, 1.0, -1.0 / aspecto, 1.0 / aspecto);
	}
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitWindowSize(640, 640);
	glutInitWindowPosition(50, 50);
	glutCreateWindow("Unoesc - CG");
	glutReshapeFunc(redimensiona);
	glutDisplayFunc(desenha);
	glutMainLoop();
	return 0;
}