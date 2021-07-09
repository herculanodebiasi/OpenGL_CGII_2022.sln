#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>

GLfloat angle, fAspect;

GLfloat n[6][3] = {  /* Normals for the 6 faces of a cube. */
  {-1.0, 0.0, 0.0}, {0.0, 1.0, 0.0}, {1.0, 0.0, 0.0},
  {0.0, -1.0, 0.0}, {0.0, 0.0, 1.0}, {0.0, 0.0, -1.0} };
GLint faces[6][4] = {  /* Vertex indices for the 6 faces of a cube. */
  {0, 1, 2, 3}, {3, 2, 6, 7}, {7, 6, 5, 4},
  {4, 5, 1, 0}, {5, 6, 2, 1}, {7, 4, 0, 3} };
GLfloat v[8][3];  /* Will be filled in with X,Y,Z vertexes. */

void drawBox(void)
{
	int i;

	for (i = 0; i < 6; i++) {
		glBegin(GL_QUADS);
			glNormal3fv(&n[i][0]);
			glVertex3fv(&v[faces[i][0]][0]);
			glVertex3fv(&v[faces[i][1]][0]);
			glVertex3fv(&v[faces[i][2]][0]);
			glVertex3fv(&v[faces[i][3]][0]);
		glEnd();
	}
}

void Desenha(void)
{
	float tamanho = .75;
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//glColor3f(0.0f, 0.0f, 1.0f);

	drawBox();

	// Desenha um cubo
	//glMatrixMode(GL_MODELVIEW);
	//glLoadIdentity();
	//gluLookAt(0, 80, 200, 0, 0, 0, 0, 1, 0);
	//glRotatef(45, 0.0f, 1.0f, 0.0f);

	/*
	glBegin(GL_QUADS);			
		// Face posterior
		glNormal3f(1.0, 0.0, 0.0);	// Normal da face
		glVertex3f(tamanho, tamanho, tamanho);
		glVertex3f(tamanho, -tamanho, tamanho);
		glVertex3f(tamanho, -tamanho, -tamanho);
		glVertex3f(tamanho, tamanho, -tamanho);

		// Face frontal
		glNormal3f(0.0, 0.0, -1.0); 	// Normal da face
		glVertex3f(tamanho, tamanho, -tamanho);
		glVertex3f(tamanho, -tamanho, -tamanho);
		glVertex3f(-tamanho, -tamanho, -tamanho);
		glVertex3f(-tamanho, tamanho, -tamanho);

		// Face lateral esquerda
		glNormal3f(-1.0, 0.0, 0.0); 	// Normal da face
		glVertex3f(-tamanho, tamanho, -tamanho);
		glVertex3f(-tamanho, -tamanho, -tamanho);
		glVertex3f(-tamanho, -tamanho, tamanho);
		glVertex3f(-tamanho, tamanho, tamanho);
	
		// Face lateral direita
		glNormal3f(0.0, 0.0, 1.0);	// Normal da face
		glVertex3f(-tamanho, tamanho, tamanho);
		glVertex3f(-tamanho, -tamanho, tamanho);
		glVertex3f(tamanho, -tamanho, tamanho);
		glVertex3f(tamanho, tamanho, tamanho);

		// Face superior
		glNormal3f(0.0, 1.0, 0.0);  	// Normal da face
		glVertex3f(-tamanho, tamanho, -tamanho);
		glVertex3f(-tamanho, tamanho, tamanho);
		glVertex3f(tamanho, tamanho, tamanho);
		glVertex3f(tamanho, tamanho, -tamanho);
	
		// Face inferior
		glNormal3f(0.0, -1.0, 0.0); 	// Normal da face
		glVertex3f(-tamanho, -tamanho, tamanho);
		glVertex3f(-tamanho, -tamanho, -tamanho);
		glVertex3f(tamanho, -tamanho, -tamanho);
		glVertex3f(tamanho, -tamanho, tamanho);
	glEnd();
	*/
	glutSwapBuffers();
}

// Inicializa parâmetros de rendering
void Inicializa(void)
{
	/* Setup cube vertex data. */
	v[0][0] = v[1][0] = v[2][0] = v[3][0] = -1;
	v[4][0] = v[5][0] = v[6][0] = v[7][0] = 1;
	v[0][1] = v[1][1] = v[4][1] = v[5][1] = -1;
	v[2][1] = v[3][1] = v[6][1] = v[7][1] = 1;
	v[0][2] = v[3][2] = v[4][2] = v[7][2] = 1;
	v[1][2] = v[2][2] = v[5][2] = v[6][2] = -1;

	GLfloat luzAmbiente[4] = { 1., 0., 0., 1.0 };
	GLfloat luzDifusa[4] = { 1., 1., 0., 1. };		// "cor" 
	GLfloat luzEspecular[4] = { 1.0, 1.0, 1.0, 1.0 };	// "brilho" 
	GLfloat posicaoLuz[4] = { 1.0, 1.0, 1.0, 0.0 };

	// Capacidade de brilho do material
	GLfloat especularidade[4] = { 1.0, 1.0, 1.0, 1.0 };
	GLint especMaterial = 60;

	// Especifica que a cor de fundo da janela será preta
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	// Habilita o modelo de colorização de Gouraud
	glShadeModel(GL_SMOOTH);
	
	// Define a refletância do material 
	glMaterialfv(GL_FRONT, GL_SPECULAR, especularidade);

	// Define a concentração do brilho
	glMateriali(GL_FRONT, GL_SHININESS, especMaterial);

	// Ativa o uso da luz ambiente 
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, luzAmbiente);

	// Define os parâmetros da luz de número 0
	glLightfv(GL_LIGHT0, GL_AMBIENT, luzAmbiente);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, luzDifusa);
	glLightfv(GL_LIGHT0, GL_SPECULAR, luzEspecular);
	glLightfv(GL_LIGHT0, GL_POSITION, posicaoLuz);
	
	// Habilita a definição da cor do material a partir da cor corrente
	glEnable(GL_COLOR_MATERIAL);
	
	//Habilita o uso de iluminação
	glEnable(GL_LIGHTING);
	
	// Habilita a luz de número 0
	glEnable(GL_LIGHT0);
	
	// Habilita o depth-buffering
	glEnable(GL_DEPTH_TEST);

	angle = 40;	
}

// Função usada para especificar o volume de visualização
void EspecificaParametrosVisualizacao(void)
{
	// Especifica sistema de coordenadas de projeção
	glMatrixMode(GL_PROJECTION);
	// Inicializa sistema de coordenadas de projeção
	glLoadIdentity();

	// Especifica a projeção perspectiva
	gluPerspective(angle, fAspect, 1, 10);

	// Especifica sistema de coordenadas do modelo
	glMatrixMode(GL_MODELVIEW);
	// Inicializa sistema de coordenadas do modelo
	glLoadIdentity();

	// Especifica posição do observador e do alvo
	gluLookAt(0, 0, 5, 0, 0, 0, 0, 1, 0);
	glTranslatef(0.0, 0.0, -1.0);
	glRotatef(60, 1.0, 0.0, 0.0);
	glRotatef(-20, 0.0, 0.0, 1.0);
}

// Função callback chamada quando o tamanho da janela é alterado 
void AlteraTamanhoJanela(GLsizei w, GLsizei h)
{
	// Para previnir uma divisão por zero
	if (h == 0) h = 1;

	// Especifica o tamanho da viewport
	glViewport(0, 0, w, h);

	// Calcula a correção de aspecto
	fAspect = (GLfloat)w / (GLfloat)h;

	EspecificaParametrosVisualizacao();
}

// Função callback chamada para gerenciar eventos do mouse
void GerenciaMouse(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON)
		if (state == GLUT_DOWN) {  // Zoom-in
			if (angle >= 10) angle -= 5;
		}

	if (button == GLUT_RIGHT_BUTTON)
		if (state == GLUT_DOWN) {  // Zoom-out
			if (angle <= 130) angle += 5;
		}

	EspecificaParametrosVisualizacao();
	glutPostRedisplay();
}

// Programa Principal 
int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(800, 600);
	glutCreateWindow("Visualizacao 3D");
	glutDisplayFunc(Desenha);
	glutReshapeFunc(AlteraTamanhoJanela);
	glutMouseFunc(GerenciaMouse);
	Inicializa();
	glutMainLoop();
}