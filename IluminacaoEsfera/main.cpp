#include <stdlib.h>
#include <GL/glut.h>

float lightDiffuse[] = { 1.0f, 1.0f, 0.0f, 1.0f };    //yellow diffuse : color where light hit directly the object's surface
float lightAmbient[] = { 1.0f, 0.0f, 0.0f, 1.0f };    //red ambient : color applied everywhere
float lightPosition[] = { 2.0f, 2.0f, -7.0f, 1.0f };

// Função responsável pela especificação dos parâmetros de iluminação
void DefineIluminacao(void)
{
	//Ambient light component
	glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmbient);
	//Diffuse light component
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDiffuse);
	//Light position
	glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);

	//Enable the first light and the lighting mode
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHTING);
}

// Desenha a esfera na posição atual
void DesenhaCena(void)
{
	int size = 4;
	glEnable(GL_LIGHTING);
	glLoadIdentity();
	glTranslatef(lightPosition[0], lightPosition[1], lightPosition[2]);
	glColor3f(1.0f, 1.0f, 0.0f);
	glutSolidSphere(0.1f, 15, 15);

	//restore default settings
	glColor3f(1.0f, 1.0f, 1.0f);
	glLoadIdentity();

	glTranslatef(0.0f, 0.0f, 0.0f);
	glRotatef(15.0f, 1.0f, 0.0f, 0.0f);
	glRotatef(30.0f, 0.0f, 1.0f, 0.0f);

	glBegin(GL_QUADS);
		//Quad 1
		glNormal3f(1.0f, 0.0f, 0.0f);   //N1
		glTexCoord2f(0.0f, 1.0f); glVertex3f(size / 2, size / 2, size / 2);   //V2
		glTexCoord2f(0.0f, 0.0f); glVertex3f(size / 2, -size / 2, size / 2);   //V1
		glTexCoord2f(1.0f, 0.0f); glVertex3f(size / 2, -size / 2, -size / 2);   //V3
		glTexCoord2f(1.0f, 1.0f); glVertex3f(size / 2, size / 2, -size / 2);   //V4
		//Quad 2
		glNormal3f(0.0f, 0.0f, -1.0f);  //N2
		glTexCoord2f(0.0f, 1.0f); glVertex3f(size / 2, size / 2, -size / 2);   //V4
		glTexCoord2f(0.0f, 0.0f); glVertex3f(size / 2, -size / 2, -size / 2);   //V3
		glTexCoord2f(1.0f, 0.0f); glVertex3f(-size / 2, -size / 2, -size / 2);   //V5
		glTexCoord2f(1.0f, 1.0f); glVertex3f(-size / 2, size / 2, -size / 2);   //V6
		//Quad 3
		glNormal3f(-1.0f, 0.0f, 0.0f);  //N3
		glTexCoord2f(0.0f, 1.0f); glVertex3f(-size / 2, size / 2, -size / 2);   //V6
		glTexCoord2f(0.0f, 0.0f); glVertex3f(-size / 2, -size / 2, -size / 2);   //V5
		glTexCoord2f(1.0f, 0.0f); glVertex3f(-size / 2, -size / 2, size / 2);   //V7
		glTexCoord2f(1.0f, 1.0f); glVertex3f(-size / 2, size / 2, size / 2);   //V8
		//Quad 4
		glNormal3f(0.0f, 0.0f, 1.0f);   //N4
		glTexCoord2f(0.0f, 1.0f); glVertex3f(-size / 2, size / 2, size / 2);   //V8
		glTexCoord2f(0.0f, 0.0f); glVertex3f(-size / 2, -size / 2, size / 2);   //V7
		glTexCoord2f(1.0f, 0.0f); glVertex3f(size / 2, -size / 2, size / 2);   //V1
		glTexCoord2f(1.0f, 1.0f); glVertex3f(size / 2, size / 2, size / 2);   //V2
		//Quad 5
		glNormal3f(0.0f, 1.0f, 0.0f);   //N5
		glTexCoord2f(0.0f, 1.0f); glVertex3f(-size / 2, size / 2, -size / 2);   //V6
		glTexCoord2f(0.0f, 0.0f); glVertex3f(-size / 2, size / 2, size / 2);   //V8
		glTexCoord2f(1.0f, 0.0f); glVertex3f(size / 2, size / 2, size / 2);   //V2
		glTexCoord2f(1.0f, 1.0f); glVertex3f(size / 2, size / 2, -size / 2);   //V4
		//Quad 6
		glNormal3f(1.0f, -1.0f, 0.0f);  //N6
		glTexCoord2f(0.0f, 1.0f); glVertex3f(-size / 2, -size / 2, size / 2);   //V7
		glTexCoord2f(0.0f, 0.0f); glVertex3f(-size / 2, -size / 2, -size / 2);   //V5
		glTexCoord2f(1.0f, 0.0f); glVertex3f(size / 2, -size / 2, -size / 2);   //V3
		glTexCoord2f(1.0f, 1.0f); glVertex3f(size / 2, -size / 2, size / 2);   //V1
	glEnd();
}

// Função responsável por inicializar parâmetros e variáveis
void Inicializa(void)
{
	glShadeModel(GL_SMOOTH);						//Smooth color shading
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);			//Clearing color
	glClearDepth(1.0);								//Enable Clearing of the Depth buffer
	glDepthFunc(GL_LEQUAL);							//Type of Depth test
	glEnable(GL_DEPTH_TEST);						//Enable Depth Testing

	//Define the correction done to the perspective calculation (perspective looks a it better)
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	//DefineIluminacao();
}

// Programa Principal 
int main(int argc, char** argv) {
	glutInit(&argc, argv);

	// Define o modo de operação da GLUT
	glutInitDisplayMode(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Especifica a posição inicial da janela GLUT
	glutInitWindowPosition(5, 5);

	// Especifica o tamanho inicial em pixels da janela GLUT
	glutInitWindowSize(450, 450);

	// Cria a janela passando como argumento o título da mesma
	glutCreateWindow("Exemplo de motion blur");

	// Registra a função callback de redesenho da janela de visualização
	glutDisplayFunc(DesenhaCena);

	// Chama a função responsável por fazer as inicializações 
	Inicializa();

	// Inicia o processamento e aguarda interações do usuário
	glutMainLoop();

	return 0;
}
