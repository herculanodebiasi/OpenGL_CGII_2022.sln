#include <stdlib.h>
#include <GL/freeglut.h>

// Fun��o callback de redesenho da janela de visualiza��o
void Desenha(void)
{
	GLubyte padrao1[] = {
		0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF,
		0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00,
		0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF,
		0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00,
		0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF,
		0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00,
		0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF,
		0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00,
		0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF,
		0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00,
		0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF,
		0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00,
		0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF,
		0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00,
		0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF,
		0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00
	};

	GLubyte padrao2[] = {
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA
	};

	GLubyte padrao3[] = {
		0x00, 0xAA, 0x00, 0xAA, 0x00, 0xAA, 0x00, 0xAA,
		0x00, 0xAA, 0x00, 0xAA, 0x00, 0xAA, 0x00, 0xAA,
		0x00, 0xAA, 0x00, 0xAA, 0x00, 0xAA, 0x00, 0xAA,
		0x00, 0xAA, 0x00, 0xAA, 0x00, 0xAA, 0x00, 0xAA,
		0x00, 0xAA, 0x00, 0xAA, 0x00, 0xAA, 0x00, 0xAA,
		0x00, 0xAA, 0x00, 0xAA, 0x00, 0xAA, 0x00, 0xAA,
		0x00, 0xAA, 0x00, 0xAA, 0x00, 0xAA, 0x00, 0xAA,
		0x00, 0xAA, 0x00, 0xAA, 0x00, 0xAA, 0x00, 0xAA,
		0x00, 0xAA, 0x00, 0xAA, 0x00, 0xAA, 0x00, 0xAA,
		0x00, 0xAA, 0x00, 0xAA, 0x00, 0xAA, 0x00, 0xAA,
		0x00, 0xAA, 0x00, 0xAA, 0x00, 0xAA, 0x00, 0xAA,
		0x00, 0xAA, 0x00, 0xAA, 0x00, 0xAA, 0x00, 0xAA,
		0x00, 0xAA, 0x00, 0xAA, 0x00, 0xAA, 0x00, 0xAA,
		0x00, 0xAA, 0x00, 0xAA, 0x00, 0xAA, 0x00, 0xAA,
		0x00, 0xAA, 0x00, 0xAA, 0x00, 0xAA, 0x00, 0xAA,
		0x00, 0xAA, 0x00, 0xAA, 0x00, 0xAA, 0x00, 0xAA,
	};

	// Limpa a janela de visualiza��o com a cor  
	// de fundo definida previamente
	glClear(GL_COLOR_BUFFER_BIT);

	// Habilita a altera��o do estilo das linhas
	glEnable(GL_POLYGON_STIPPLE);

	// Altera a cor do desenho para preto
	glColor3f(0.0f, 0.0f, 0.0f);

	// Altera o padrao de preenchimento do pol�gono 
	// (chamin� da casa)
	glPolygonStipple(padrao1);
	glBegin(GL_POLYGON);
		glVertex2f(15.0f, 28.0f);
		glVertex2f(15.0f, 45.0f);
		glVertex2f(25.0f, 45.0f);
		glVertex2f(25.0f, 21.0f);
	glEnd();

	// Altera o padrao de preenchimento do pol�gono 
	// (frente da casa)
	glPolygonStipple(padrao3);
	glBegin(GL_QUADS);
		glVertex2f(-40.0f, -40.0f);
		glVertex2f(-40.0f, 10.0f);
		glVertex2f(-10.0f, 10.0f);
		glVertex2f(-10.0f, -40.0f);
		glVertex2f(-10.0f, -20.0f);
		glVertex2f(-10.0f, 10.0f);
		glVertex2f(10.0f, 10.0f);
		glVertex2f(10.0f, -20.0f);
		glVertex2f(10.0f, -40.0f);
		glVertex2f(10.0f, 10.0f);
		glVertex2f(40.0f, 10.0f);
		glVertex2f(40.0f, -40.0f);
	glEnd();

	// Altera o padrao de preenchimento do pol�gono 
	// (telhado da casa)
	glPolygonStipple(padrao2);
	glBegin(GL_TRIANGLES);
		glVertex2f(-40.0f, 10.0f);
		glVertex2f(0.0f, 40.0f);
		glVertex2f(40.0f, 10.0f);
	glEnd();

	// Altera o padrao de preenchimento do pol�gono 
	// (porta da casa)
	glPolygonStipple(padrao2);
	glBegin(GL_QUADS);
		glVertex2f(-10.0f, -40.0f);
		glVertex2f(-10.0f, -20.0f);
		glVertex2f(10.0f, -20.0f);
		glVertex2f(10.0f, -40.0f);
	glEnd();

	// Executa os comandos OpenGL 
	glFlush();
}

// Fun��o callback chamada quando o tamanho da janela � alterado 
void AlteraTamanhoJanela(GLsizei w, GLsizei h)
{
	// Evita a divisao por zero
	if (h == 0) h = 1;

	// Especifica as dimens�es da Viewport
	glViewport(0, 0, w, h);

	// Inicializa o sistema de coordenadas
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// Estabelece a janela de sele��o (esquerda, direita, inferior, 
	// superior) mantendo a propor��o com a janela de visualiza��o
	if (w <= h)
		gluOrtho2D(-50.0f, 50.0f, -50.0f*h / w, 50.0f*h / w);
	else
		gluOrtho2D(-50.0f*w / h, 50.0f*w / h, -50.0f, 50.0f);
}

// Fun��o callback chamada para gerenciar eventos de teclas
void Teclado(unsigned char key, int x, int y)
{
	if (key == 27)
		exit(0);
}


// Fun��o respons�vel por inicializar par�metros e vari�veis
void Inicializa(void)
{
	// Define a cor de fundo da janela de visualiza��o como branca
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
}

// Programa Principal 
int main(int argc, char **argv) {
	glutInit(&argc, argv);

	// Define do modo de opera��o da GLUT
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

	// Especifica a posi��o inicial da janela GLUT
	glutInitWindowPosition(5, 5);

	// Especifica o tamanho inicial em pixels da janela GLUT
	glutInitWindowSize(450, 450);

	// Cria a janela passando como argumento o t�tulo da mesma
	glutCreateWindow("Pol�gonos com Diferentes Padr�es");

	// Registra a fun��o callback de redesenho da janela de visualiza��o
	glutDisplayFunc(Desenha);

	// Registra a fun��o callback de redimensionamento da janela de visualiza��o
	glutReshapeFunc(AlteraTamanhoJanela);

	// Registra a fun��o callback para tratamento das teclas ASCII
	glutKeyboardFunc(Teclado);

	// Chama a fun��o respons�vel por fazer as inicializa��es 
	Inicializa();

	// Inicia o processamento e aguarda intera��es do usu�rio
	glutMainLoop();

	return 0;
}
