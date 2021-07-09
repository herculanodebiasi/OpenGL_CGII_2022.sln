#include <windows.h>  // for MS Windows
#include <GL/glut.h>  // GLUT, include glu.h and gl.h

void desenha() {
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0, 0.0, 0.0);

	/*glPointSize(15);
	glBegin(GL_POINTS);
		glVertex2f(25, 25);
		glVertex2f(25, 75);
		glVertex2f(75, 25);
		glVertex2f(75, 75);
	glEnd();

	const float distancia = 5.0f;
	float y = 50, pos = -1 + distancia;
	float blue = 0.0;

	for (int i = 1; i <= 20; i++)
	{
		glColor3f(0, 0, blue);
		glPointSize(i);

		glBegin(GL_POINTS);
		glVertex3f(pos, y, 0);
		glEnd();

		blue += 0.05;
		pos += distancia;
	}
	
	glLineWidth(5.0);
	glBegin(GL_LINES);
		glColor3f(1.0, 0.0, 0.0);
		glVertex2f(20.0, 20.0);

		glColor3f(0.0, 1.0, 0.0);
		glVertex2f(80, 20.0);
	glEnd();

	glBegin(GL_TRIANGLES);
		glVertex2f(10, 90);
		glVertex2f(10, 10);
		glVertex2f(35, 75);
		glVertex2f(30, 20);
		glVertex2f(90, 90);
		glVertex2f(80, 40);
	glEnd();
	

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glBegin(GL_TRIANGLE_STRIP);
		glVertex2f(10, 90);
		glVertex2f(10, 10);
		glVertex2f(35, 75);
		glVertex2f(30, 20);
		glVertex2f(90, 90);
		glVertex2f(80, 40);
	glEnd();

	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glBegin(GL_QUAD_STRIP);
		glColor3f(0.0, 1.0, 1.0);
		glVertex2f(10, 90);
		glVertex2f(10, 25);

		glColor3f(0.0, 0.5, 1.0);
		glVertex2f(30, 92);
		glVertex2f(30, 10);

		glColor3f(0.0, 0.8, 1.0);
		glVertex2f(60, 85);
		glVertex2f(60, 25);

		glColor3f(0.0, 0.0, 1.0);
		glVertex2f(90, 90);
		glVertex2f(85, 25);
	glEnd();
	*/

	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glBegin(GL_POLYGON);
		glVertex2f(20, 20);
		glVertex2f(50, 20);
		glVertex2f(80, 50);
		glVertex2f(80, 80);
		glVertex2f(20, 80);
	glEnd();

	glutSwapBuffers();
}
	/*
	
	glPushMatrix();
		// Cubo 1
		glPushMatrix();
			glTranslatef(-2.0, 0.0, 0.0);
			glScalef(2.0, 1.0, 4.0);
			glutWireCube(10.0);
		glPopMatrix();
			/*
		// Cubo 2
		//glPushMatrix();
			glRotatef(25.0, 0.0, 0.0, 1.0);
			glTranslatef(2.0, 0.0, 0.0);
			glScalef(2.0, 1.0, 4.0);
			glutWireCube(1.0);
		//glPopMatrix();

		// Cubo 3 
		//glPushMatrix();
			glTranslatef(0.0, 2.0, 0.0);
			glScalef(2.0, 1.0, 4.0);
			glutWireCube(1.0);
		//glPopMatrix();

		// Cubo 4
		//glPushMatrix();
			glTranslatef(0.0, -2.0, 0.0);
			glScalef(2.0, 1.0, 4.0);
			glutWireCube(1.0);
		//glPopMatrix();
	glPopMatrix();*/
	
/*
void display(void){
	glClear(GL_COLOR_BUFFER_BIT);
	glPushMatrix();

	// Cubo 1 
	glPushMatrix();
		glTranslatef(-2.0, 0.0, 0.0);
		glScalef(2.0, 1.0, 4.0);
		glutWireCube(10.0);
	glPopMatrix();

	// Cubo 2 
	glPushMatrix();
		glRotatef(25.0, 0.0, 0.0, 1.0);
		glTranslatef(2.0, 0.0, 0.0);
		glScalef(2.0, 1.0, 4.0);
		glutWireCube(1.0);
	glPopMatrix();

	// Cubo 3 
	glPushMatrix();
	glTranslatef(0.0, 2.0, 0.0);
	glScalef(2.0, 1.0, 4.0);
	glutWireCube(1.0);
	glPopMatrix();

	// Cubo 4 
	glPushMatrix();
	glTranslatef(0.0, -2.0, 0.0);
	glScalef(2.0, 1.0, 4.0);
	glutWireCube(1.0);
	glPopMatrix();

	glPopMatrix();
	glutSwapBuffers();
}*/

void reshape(int w, int h){
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(65.0, (GLfloat)w / (GLfloat)h, 1.0, 20.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(0.0, 0.0, -10.0);
}

void teclado(unsigned char key, int x, int y){
	switch (key) {
	case 27:                                         // tecla Esc (encerra o programa)
		exit(0);
		break;
	}
}

/* Main function: GLUT runs as a console application starting at main()  */
int main(int argc, char** argv) {
	glutInit(&argc, argv);                  // Initialize GLUT
	glutInitWindowSize(640, 640);			// Set the window's initial width & height
	glutInitWindowPosition(50, 50);			// Position the window's initial top-left corner
	glutCreateWindow("Unoesc: CG (Polígono)");  // Create a window with the given title

	/*
	glViewport(0, 0, 640, 640); // Set viewport size to be entire OpenGL window.
	glMatrixMode(GL_PROJECTION); // Set matrix mode to projection.
	glLoadIdentity(); // Clear current projection matrix to identity.
	// Specify the orthographic (or perpendicular) projection,
	// i.e., define the viewing box.
	glOrtho(0.0, 100.0, 0.0, 100.0, -1.0, 1.0);
	glMatrixMode(GL_MODELVIEW); // Set matrix mode to modelview.
	*/

	//glutReshapeFunc(reshape);
	//glLoadIdentity();

	glOrtho(0.0, 100.0, 0.0, 100.0, -1.0, 1.0);

	glutDisplayFunc(desenha);			    
	glutKeyboardFunc(teclado);
	glutMainLoop();							
	return 0;
}