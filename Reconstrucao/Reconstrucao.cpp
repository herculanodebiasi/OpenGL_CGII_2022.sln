/*
 *		Este código foi modificado e extendido por Aldo v.Wangenheim
 *		(awangenh@inf.ufsc.br - http://www.inf.ufsc.br/~awangenh/CG/)
 *		para utilização como exemplo de montagem 3D de objetos em
 *		Modelo de Arame e em Modelos de Facetas Triangulares para a
 *		Disciplina ine 5341 - Computacao Grafica do Departamento de
 *		Informatica e Estatistica da Universidade Federal de Santa
 *		Catarina.
 *
 *		Florianopolis, Ilha de Santa Catarina, Maio/Junho de 2001
 *
 *
 *		This Code Was Originally Created By Jeff Molofee 2000
 *		A HUGE Thanks To Fredric Echols For Cleaning Up
 *		And Optimizing The Base Code, Making It More Flexible!
 *		If You've Found This Code Useful, Please Let Me Know.
 *		Visit My Site At nehe.gamedev.net
 *
 *		Parts of this code were Written by Michael Sweet.
 *
 */
#pragma warning(disable:4996)

#include "font.h"
#include "normal.h"
#include <stdio.h>
#include <math.h>
#include <GL/glut.h>
#include "triangulos.h"		// Definicao dos TADs para armazenar listas de 
 // triangulos e pontos

/* ascii code for the escape key */
#define ESCAPE 27



/*
 * Globals...
 */

 /* The number of our GLUT window */
int		window;

int		Width;				/* Width of window */
int		Height;				/* Height of window */
GLfloat	rtri = 0.0f;			// Angulo de Rotacao 
TipoPontos normal;

/*==========================================*/
/* Variaveis para o Modelo de Objeto		*/
/*==========================================*/

TipoPontos		*meusPontos;		// Ponteiro para a lista de pontos. Alocada em leiaDados()
TipoTriangulo	*meusTriangulos;	// Ponteiro para a lista de indices de vertices de triangulos.
									// Tambem alocada em leiaDados()

int				numPontos;			// Quantos pontos tem o objeto.
int				numTriangulos;		// Quantos triangulos definidos por estes pontos.
BOOL			linhas = FALSE;		// Desenho wireframe ou facetas ?
BOOL			rotacionar = FALSE;	// Para a funcao Display saber se deve rodar o treco sozinha ou nao.
BOOL			ortogonal = TRUE;	// Indica se escolhemos uma projecao ortogonal ou em perspectiva.

/*==========================================*/
/* Definicao de vetores contendo dados de   */
/* cor, intensidade e pos. de fontes de luz.*/
/*==========================================*/
GLfloat			diffuseLight[] = { 1.0f, 1.0f, 1.0f, 1.0 };
GLfloat			ambientLight[] = { 0.2f, 0.2f, 0.4f, 1.0 };
GLfloat			emissiveLight[] = { 0.0f, 0.0f, 0.0f, 1.0 };
GLfloat			lightPos[] = { 0.0f, 300.0f, -200.0f, 1.0f };

GLuint			texture[1];                             // Storage For One Texture ( NEW )
GLFONT			*Font;  /* Font data */


/*
 * Functions...
 */

void Redraw(void);
void Resize(int width, int height);

void InitGL(int Width, int Height)	        // We call this right after our OpenGL window is created.
{
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);		// This Will Clear The Background Color To Black
	glClearDepth(1.0);				// Enables Clearing Of The Depth Buffer
	glDepthFunc(GL_LEQUAL);				// The Type Of Depth Test To Do
	glEnable(GL_DEPTH_TEST);			// Enables Depth Testing
	glShadeModel(GL_SMOOTH);			// Enables Smooth Color Shading

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();				// Reset The Projection Matrix

	if (!ortogonal)
	{
		gluPerspective(45.0f, (GLfloat)Width / (GLfloat)Height, 0.1f, 1000.0f);
	}
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);	// Really Nice Perspective Calculations

	glMatrixMode(GL_MODELVIEW);
}

/*==========================================================*/
/*	The function called whenever a key is pressed.			*/
void tecla(unsigned char tecla, int x, int y)
/*==========================================================*/
{
	switch (tecla) {
	case 27:        // When Escape Is Pressed...
	  /* shut down our window */
		glutDestroyWindow(window);

		/* exit the program...normal termination. */
		exit(0);
		break;        // Ready For Next Case
	default:        // Now Wrap It Up
		break;
	}

}


/*==========================================================*/
/*	The function called whenever a special key is pressed.	*/
void teclas_de_seta(int tecla, int x, int y)
/*==========================================================*/
{
	switch (tecla) {
	case GLUT_KEY_UP:     // When Up Arrow Is Pressed...
		glutFullScreen(); // Go Into Full Screen Mode
		break;
	case GLUT_KEY_DOWN:               // When Down Arrow Is Pressed...
		glutReshapeWindow(640, 480); // Go Into A 640 By 480 Window
		break;
	case 1:
		// Teclaram F1
		linhas = FALSE;
		glutPostRedisplay();
		break;
	case 2:
		// Teclaram F2
		linhas = TRUE;
		glutPostRedisplay();
		break;
	case 3:
		// Mandaram girar sozinho ou parar de girar.
		rotacionar = !rotacionar;
		break;
	case 4:
		// Mandaram mudar o modo
		ortogonal = !ortogonal;
		glutReshapeWindow(Width - 1, Height - 1); // Go Into A 640 By 480 Window
		Width--;
		Height--;
	case 100:
		// Girar para esquerda
		rtri = rtri - 0.5;
		glutPostRedisplay();
		//Redraw();
		break;
	case 102:
		// Girar para direita
		rtri = rtri + 0.5;
		glutPostRedisplay();
		//Redraw();
		break;
	default:
		printf("Teclaram: %d\n", tecla);
		break;
	}
}

/* -------------------------------------------------------------- */
/*	Le o arquivo contendo os dados para a montagem do modelo.     */
/* -------------------------------------------------------------- */
void leiaDados()
{
	FILE	*dados;			// Dados eh o arquivo de dados 

	int		i;
	TipoPontos	max, min;


	dados = fopen("dataTest.dat", "r");
	fscanf(dados, "%d", &numPontos);
	// Alocamos memoria para os pontos que vamos ler, agora que sabemos quantos serao.
	meusPontos = (TipoPontos *)malloc(sizeof(TipoPontos) * (numPontos + 1));
	// Inicializamos max e min com valores bem pequenos e bem grandes. 
	max.x = -100000.0f;	max.y = -100000.0f;	max.z = -100000.0f;
	min.x = 100000.0f;	min.y = 100000.0f;	min.z = 100000.0f;
	for (i = 1; i <= numPontos; i++)
	{
		fscanf(dados, "%f", &meusPontos[i].x);
		if (max.x < meusPontos[i].x) { max.x = meusPontos[i].x; }
		if (min.x > meusPontos[i].x) { min.x = meusPontos[i].x; }
		fscanf(dados, "%f", &meusPontos[i].z);
		if (max.z < meusPontos[i].z) { max.z = meusPontos[i].z; }
		if (min.z > meusPontos[i].z) { min.z = meusPontos[i].z; }
		fscanf(dados, "%f", &meusPontos[i].y);
		if (max.y < meusPontos[i].y) { max.y = meusPontos[i].y; }
		if (min.y > meusPontos[i].y) { min.y = meusPontos[i].y; }

	}
	/* -----------------------------------
	   Calculo do ponto central da estrutura.
	   Ja que queremos que o objeto gire em
	   torno de si mesmo, temos de calcular
	   seu centro.
	   meusPontos[0] nao era usado ate agora.
	   ----------------------------------- */
	meusPontos[0].x = min.x + (max.x - min.x) / 2.0f;
	meusPontos[0].y = min.y + (max.y - min.y) / 2.0f;
	meusPontos[0].z = min.z + (max.z - min.z) / 2.0f;
	/* -----------------------------------
	   Leitura dos indices dos pontos que
	   definem os vertices dos triangulos.
	   ----------------------------------- */
	fscanf(dados, "%d", &numTriangulos);				// Lemos o numero de triangulos.
	// Alocamos memoria para os triangulos que vamos ler, agora que sabemos quantos serao.
	meusTriangulos = (TipoTriangulo *)malloc(sizeof(TipoTriangulo) * (numTriangulos + 1));
	for (i = 1; i <= numTriangulos; i++)
	{
		fscanf(dados, "%d", &meusTriangulos[i].v1);
		fscanf(dados, "%d", &meusTriangulos[i].v2);
		fscanf(dados, "%d", &meusTriangulos[i].v3);
	}
	fclose(dados);

}


/*===========================================================*/
/* Funcao que chama redraw caso rotacionar automatico esteja */
/* setado. Endereco passado como a Idle Function, funcao que */
/* o laco do GLUT chama quando nao esta fazendo outra coisa. */
void Display(void)
/*===========================================================*/
{
	if (rotacionar)
	{
		Redraw();
	}
}

/*==========================================================*/
/*	'main()' - Open a window and display some text.			*/
int                /* O - Exit status						*/
main(int  argc,    /* I - Number of command-line arguments	*/
	char *argv[]) /* I - Command-line arguments			*/
/*==========================================================*/
{
	/* Initialize GLUT state - glut will take any command line arguments that pertain to it or
	 X Windows - look at its documentation at http://reality.sgi.com/mjk/spec3/spec3.html */
	glutInit(&argc, argv);
	/*	Select type of Display mode:
		Double buffer
		RGBA color
		Alpha components supported
		Depth buffer */
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);

	/* get a 640 x 480 window */
	glutInitWindowSize(640, 480);

	/*	The window starts at the upper left corner of the screen	*/
	/*	Aparentemente esta funcao so faz sentido no X-Windows. Em	*/
	/*	MS-Windows a janela aparece sempre aa esquerda em cima de	*/
	/*	qualquer forma.												*/
	glutInitWindowPosition(0, 0);

	/* Abrimos aqui uma janela, Open a window						*/
	/* A variavel window guarda o numero da janela. Pode ser util.	*/
	window = glutCreateWindow("ine5341 Computação Gráfica UFSC - Rotação de Objetos Facetados e Modelos de Arame");

	/*	Register the function called when our window is resized.	*/
	glutReshapeFunc(Resize);

	/*	Register the function to do all our OpenGL drawing.			*/
	glutDisplayFunc(Redraw);

	/* Register the function called when the keyboard is pressed.	*/
	glutKeyboardFunc(tecla);

	/* Resgitramos a funcao que é chamada quando uma tecla especial */
	/* foi teclada, como setas e teclas de funcao.					*/
	glutSpecialFunc(teclas_de_seta);

	/* Criamos o fonte de bitmap que sera utilizado na aplicacao.	*/
	Font = FontCreate(wglGetCurrentDC(), "Arial", 22, 0, 0);

	/* Funcao chamada sempre que o Loop do GLUT esta ocioso			*/
	/* Esta funcao eh responsavel pelos efeitos de animacao.		*/
	glutIdleFunc(Display);

	/* Chamamos a funcao que realiza o resto das inicializacoes.	*/
	InitGL(640, 480);

	leiaDados();

	/* Iniciamos a maquina de processamento de eventos do GLUT.		*/
	glutMainLoop();
	return (0);
}


/*==========================================*/
void desenhaTexto()
/*==========================================*/
{
	glEnable(GL_COLOR_MATERIAL);
	glColor3f(0.0, 0.5, 1.0);
	glRasterPos3i(-150.0f, -100.0f, -250.0f);
	FontPrintf(Font, 1, "         Reconstrução 3D de cabeça a partir de uma tomografia.");
	glRasterPos3i(-150.0f, -113.0f, -250.0f);
	FontPrintf(Font, 1, "   [F1] Facetas  [F2] Arame  [F3] Rotaciona/Pára  [F4] Perspectiva");
	glDisable(GL_COLOR_MATERIAL);

}


/*==========================================*/
void desenhaMenu()
/*==========================================*/
{
	glEnable(GL_COLOR_MATERIAL);
	glColor3f(0.7f, 0.7f, 0.7f);

	// Desenhamos conjunto de quadrilateros para fazer uma tela de um menu.
	// A distancia Z foi determinada experimentalmente para fazer o menu ter
	// a mesma aparencia tanto em modo perspectiva como em projecao ortogonal.
	glBegin(GL_QUADS);
	glVertex3f(-158.0f, -118.0f, -289.0f);
	glVertex3f(158.0f, -118.0f, -289.0f);
	glVertex3f(158.0f, -90.0f, -289.0f);
	glVertex3f(-158.0f, -90.0f, -289.0f);
	glEnd();

	glDisable(GL_COLOR_MATERIAL);
}


/*==========================================*/
void desenhaModelo()
/*==========================================*/
{
	int	trianguloAtual = 1;								// Contador para o triangulo que estamos
														// renderizando no momento. Inicia em 1
														// porque a posicao 0 da lista de triangulos
														// nos reservamos para dados adicionais e 
														// tambem para manter compatibilidade com
														// dados exportados para VRML.

	glTranslatef(0.0f, -40.0f, -350.0f);				// Posicao inicial para desenhar objeto.
	if (linhas)
	{
		/* -------------------------------------------------------------- */
		/*		  Renderiza conjunto de dados como MODELO DE ARAME.       */
		/* -------------------------------------------------------------- */
		glEnable(GL_LIGHTING);
		glLightfv(GL_LIGHT0, GL_AMBIENT, diffuseLight);
		glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);
		glLightfv(GL_LIGHT0, GL_EMISSION, emissiveLight);
		glEnable(GL_LIGHT0);

		glRotatef(rtri, 0.0f, 1.0f, 0.0f);			// Rotaciona incrementalmente no eixo Y
		glRotatef(-20.0f, 1.0f, 0.0f, 0.0f);		// Rotaciona 20 gr.para frente no eixo X

		/* -------------------------------------------------------------- */
		/* Esta linha eh importante: aqui trasladamos o sistema de coor-  */
		/* denadas de uma distancia equivalente aa posicao do centro do   */
		/* objeto exatamente no sentido contrario ao da posicao do centro.*/
		/* Dessa forma colocamos o centro do objeto, nao importa onde es- */
		/* teja, exatamente sobre o eixo de rotacao e o objeto girarah em */
		/* torno de seu centro.											  */
		/* -------------------------------------------------------------- */
		glTranslatef(-meusPontos[0].x, 0.0f, -meusPontos[0].z);


		glEnable(GL_COLOR_MATERIAL);
		glColor3f(0.75f, 0.0f, 0.0f);
		for (trianguloAtual = 1; trianguloAtual <= numTriangulos; trianguloAtual++)
		{
			// Observe que para cada triangulo repetimos a chamada a glBegin. Temos de fazer
			// isto assim pois o objeto GL_LINE_LOOP automaticamente fecha um poligono com
			// o primeiro ponto. Se colocarmos o glBegin do lado de fora do laco, teremos cada
			// triangulo interligado com o anteriormente desenhado, mesmo se este nao for vizinho.
			glBegin(GL_LINE_LOOP);
			// Start Drawing A Wire Frame
			glVertex3f(meusPontos[meusTriangulos[trianguloAtual].v1].x,
				meusPontos[meusTriangulos[trianguloAtual].v1].y,
				meusPontos[meusTriangulos[trianguloAtual].v1].z);

			glVertex3f(meusPontos[meusTriangulos[trianguloAtual].v2].x,
				meusPontos[meusTriangulos[trianguloAtual].v2].y,
				meusPontos[meusTriangulos[trianguloAtual].v2].z);

			glVertex3f(meusPontos[meusTriangulos[trianguloAtual].v3].x,
				meusPontos[meusTriangulos[trianguloAtual].v3].y,
				meusPontos[meusTriangulos[trianguloAtual].v3].z);
			// Fecha automaticamente com o primeiro vertice. 
			glEnd();
			glDisable(GL_COLOR_MATERIAL);
		}
	}
	else
	{
		/* -------------------------------------------------------------- */
		/*		  Renderiza conjunto de dados como MODELO DE FACETAS.     */
		/* -------------------------------------------------------------- */
		glRotatef(rtri, 0.0f, 1.0f, 0.0f);			// Rotate On The Y axis
		glRotatef(-20.0f, 1.0f, 0.0f, 0.0f);		// Rotaciona no eixo X

		/* -------------------------------------------------------------- */
		/* Esta linha eh importante: aqui trasladamos o sistema de coor-  */
		/* denadas de uma distancia equivalente aa posicao do centro do   */
		/* objeto exatamente no sentido contrario ao da posicao do centro.*/
		/* Dessa forma colocamos o centro do objeto, nao importa onde es- */
		/* teja, exatamente sobre o eixo de rotacao e o objeto girarah em */
		/* torno de seu centro.											  */
		/* -------------------------------------------------------------- */
		glTranslatef(-meusPontos[0].x, 0.0f, -meusPontos[0].z);

		glEnable(GL_LIGHTING);
		glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
		glLightfv(GL_LIGHT0, GL_SPECULAR, diffuseLight);
		glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
		glEnable(GL_LIGHT0);
		glEnable(GL_COLOR_MATERIAL);
		glColor3f(0.75f, 0.3f, 0.3f);						    // Set Triangle To Red
		glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, diffuseLight);
		glMateriali(GL_FRONT_AND_BACK, GL_SHININESS, 50);


		glBegin(GL_TRIANGLES);	// Observe que aqui o laco para-faca esta DENTRO do glBegin.
								// Podemos fazer assim porque OpenGL assume que cada conjunto
								// de tres pontos eh um triangulo independente.
		for (trianguloAtual = 1; trianguloAtual <= numTriangulos; trianguloAtual++)
		{
			/* Calcula a normal aos Pontos que vao definir a proxima faceta */
			calculaNormal(meusPontos[meusTriangulos[trianguloAtual].v3],
				meusPontos[meusTriangulos[trianguloAtual].v2],
				meusPontos[meusTriangulos[trianguloAtual].v1],
				&normal);

			/*Vou setar normal... */
			glNormal3f(normal.x, normal.y, normal.z);

			glVertex3f(meusPontos[meusTriangulos[trianguloAtual].v3].x,
				meusPontos[meusTriangulos[trianguloAtual].v3].y,
				meusPontos[meusTriangulos[trianguloAtual].v3].z);
			glVertex3f(meusPontos[meusTriangulos[trianguloAtual].v2].x,
				meusPontos[meusTriangulos[trianguloAtual].v2].y,
				meusPontos[meusTriangulos[trianguloAtual].v2].z);
			glVertex3f(meusPontos[meusTriangulos[trianguloAtual].v1].x,
				meusPontos[meusTriangulos[trianguloAtual].v1].y,
				meusPontos[meusTriangulos[trianguloAtual].v1].z);
		}
		glEnd();
		glDisable(GL_LIGHT0);
		glDisable(GL_LIGHTING);
		glDisable(GL_COLOR_MATERIAL);


	}

	// Increase The Rotation Variable For The Triangle ( NEW )
	rtri += 2.0f;											
}


/*==========================================*/
/*	'Redraw()' - Redraw the window...		*/
void Redraw(void)
/*==========================================*/
{
	/* Clear the window to black */
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);


	glPushMatrix();
	desenhaModelo();
	glPopMatrix();


	desenhaMenu();

	desenhaTexto();

	glutSwapBuffers();

	glFinish();
}



/*==========================================*/
/*		'Resize()' - Resize the window...   */
void Resize(int width,  /* I - Width of window   */ int height) /* I - Height of window  */
/*==========================================*/
{
	/* Save the new width and height */
	Width = width;
	Height = height;

	/* Reset the viewport... */
	glViewport(0, 0, width, height);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (ortogonal)
	{
		glOrtho(-160.0f, 160.0f, -120.0f, 120.0f, -100.0, 1000.0);
	}
	else
	{
		gluPerspective(45.0f, (GLfloat)width / (GLfloat)height, 0.1f, 1000.0f);
	}
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity(); // Reset The Modelview Matrix

}
