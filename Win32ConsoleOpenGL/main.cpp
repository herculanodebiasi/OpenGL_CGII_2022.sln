#include <GL/glew.h>
#include <iostream>
#include "display.h"

int main(int argc, char *argv[])
{
	try 
	{
		Display display(800, 600, "Ola Mundo!");

		while (!display.IsClosed())
		{
			display.Clear(0.0f, 0.0f, 1.0f, 1.0f);

			glBegin(GL_TRIANGLES);
				glColor3f(1, 0, 0); glVertex2f(0.0f, 0.5f);
				glColor3f(0, 1, 0); glVertex2f(-0.5f, -0.5f);
				glColor3f(0, 0, 1); glVertex2f(0.5f, -0.5f);
			glEnd();

			display.Update();
		}
	}
	catch (std::exception &e)
	{
		std::cout << "Error: " << e.what();
		exit(1);
	}

	return 0;
}