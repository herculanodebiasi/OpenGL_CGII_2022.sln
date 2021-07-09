#include <windows.h>  // for MS Windows
#include <GL/glut.h>  // GLUT, include glu.h and gl.h

int comprimento = 640, altura = 640;

/* Handler for window-repaint event. Call back when the window first appears and
whenever the window needs to be re-painted. */
void display() {
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Set background color to black and opaque
	glClear(GL_COLOR_BUFFER_BIT);         // Clear the color buffer (background)

	// Define shapes enclosed within a pair of glBegin and glEnd
	glBegin(GL_QUADS);				 // Each set of 4 vertices form a quad
		glColor3f(1.0f, 0.0f, 0.0f); // Red
		glVertex2f(-0.8f, 0.1f);     // Define vertices in counter-clockwise (CCW) order
		glVertex2f(-0.2f, 0.1f);     //  so that the normal (front-face) is facing you
		glVertex2f(-0.2f, 0.7f);
		glVertex2f(-0.8f, 0.7f);
	glEnd();
	
	glBegin(GL_QUADS);                  // Draw A Quad
		glColor3f(1.0f, 1.0f, 0.0f);

		glVertex3f(-0.5f, 0.5f, 0.0f);  // Top Left
		glVertex3f(0.5f, 0.5f, 0.0f);   // Top Right
		glVertex3f(0.5f, -0.5f, 0.0f);  // Bottom Right
		glVertex3f(-0.5f, -0.5f, 0.0f); // Bottom Left
	glEnd();                            // Done Drawing The Quad
	
	glFlush();  // Render now
}

void teclado(unsigned char key, int x, int y)
{
	static bool telaCheia = false;

	if (key == 'q' || key == 'Q' || key == 27) 
	{
		exit(0);
	}
	else if (key == 'F' || key == 'f')
	{
		telaCheia = !telaCheia;

		if (!telaCheia) 
		{
			glutReshapeWindow(comprimento, altura);
		}
		else 
		{
			glutFullScreen();
		}
	}
}

/* Main function: GLUT runs as a console application starting at main()  */
int main(int argc, char** argv) {
	glutInit(&argc, argv);                  // Initialize GLUT
	glutInitWindowSize(comprimento, altura);			// Set the window's initial width & height
	glutInitWindowPosition(50, 50);			// Position the window's initial top-left corner
	glutCreateWindow("OpenGL Setup Test");  // Create a window with the given title
	glutDisplayFunc(display);			    // Register display callback handler for window re-paint
	glutKeyboardFunc(teclado);
	glutMainLoop();							// Enter the event-processing loop
	return 0;
}