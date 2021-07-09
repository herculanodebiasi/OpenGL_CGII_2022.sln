#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <cstdlib>

int main(int argc, char **argv)
{
	GLFWwindow *window;

	//Inicializar janela
	if (!glfwInit())
	{
		exit(EXIT_FAILURE);
	}

	//Cria janela e o contexto OpenGL
	window = glfwCreateWindow(640, 480, "OpenGL", NULL, NULL);

	if (!window)
	{
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	//Seta contexto da janela OpenGL como o atual
	glfwMakeContextCurrent(window);

	//Repete até fechar a janela
	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		//Alterna os buffers
		glfwSwapBuffers(window);

		//Processa eventos pendentes
		glfwPollEvents();
	}

	glfwDestroyWindow(window);
	glfwTerminate();

	exit(EXIT_SUCCESS);
}