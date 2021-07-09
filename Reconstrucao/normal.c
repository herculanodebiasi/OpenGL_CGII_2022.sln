/* ===================================================== */
/* Arquivo normal.c										 */
/*														 */
/* Contem um conjunto de funcoes que implementa:		 */
/*														 */
/* Calculo de um vetor de comprimento unitario a partir  */
/* de um vetor qualquer:								 */
/*		void reduzParaUnitario()						 */
/*														 */
/* Calculo do vetor normal a um plano definido por 3	 */
/* pontos quaisquer. Usado para calcular a normal a uma  */
/* faceta de uma superficie qualquer para podermos tirar */
/* o melhor da iluminacao atraves de reflexos realistas. */
/*		void calculaNormal()							 */
/*														 */
/* Fonte:												 */
/*		OpenGL Super Bible, Capitulo 6					 */
/*		Program by Richard S. Wright Jr.				 */
/* Adaptacao:											 */
/*		Aldo von Wangenheim, awangenh@inf.ufsc.br		 */
/*		Florianopolis, Ilha de Santa Catarina,			 */
/*		Maio/Junho de 2001								 */
/*														 */
/* ===================================================== */

#include <math.h>
#include <gl/glut.h>
#include "triangulos.h"

void 
reduzParaUnitario(	TipoPontos	*vector	)
	{
	GLfloat length;
	
	// Calculate the length of the vector		
	length = (GLfloat) sqrt((vector->x * vector->x) + 
					 	    (vector->y * vector->y) +
						    (vector->z * vector->z));

	// Keep the program from blowing up by providing an exceptable
	// value for vectors that may calculated too close to zero.
	if (length == 0.0f)
		length =  1.0f;

	// Dividing each element by the length will result in a
	// unit normal vector.
	vector->x = vector->x / length;
	vector->y = vector->y / length;
	vector->z = vector->z / length;
	}


/* ===================================================== */
void 
calculaNormal(	TipoPontos	p1,
				TipoPontos	p2,
				TipoPontos	p3,
				TipoPontos	*retorno	)

/* Assume que p1, p2, & p3 estão especificados em        */
/* sentido anti-horario. Se voce passar os parametros em */
/* outra ordem, o vetor vai apontar para o lado errado.  */
/* ===================================================== */
	{
	TipoPontos v1,v2;

	// Calcula dois vetores a partir dos tres pontos.
	v1.x = p1.x - p2.x;
	v1.y = p1.y - p2.y;
	v1.z = p1.z - p2.z;

	v2.x = p2.x - p3.x;
	v2.y = p2.y - p3.y;
	v2.z = p2.z - p3.z;

	// Take the cross product of the two vectors to get
	// the normal vector which will be stored in out
	retorno->x = v1.y * v2.z - v1.z * v2.y;
	retorno->y = v1.z * v2.x - v1.x * v2.z;
	retorno->z = v1.x * v2.y - v1.y * v2.x;

	// Normaliza o vector, reduzindo comprimento para um
	reduzParaUnitario(retorno);
}
