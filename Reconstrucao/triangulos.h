/*-------------------------------------------------------
	INE 5341 - COMPUTACAO GRAFICA - INE/CTC/UFSC - 2001
  
	HEADERFILE QUE DEFINE OS TADs QUE SERAO UTILIZADOS 
	PARA ARMAZENAR AS ESTRUTURAS DE TRIANGULOS E SEUS
	PONTOS PARA MONATGEM DE MODELOS DE ARAME E FACETAS.

	Aldo v. Wangenheim (awangenh@inf.ufsc.br) Maio, 2001

---------------------------------------------------------*/

#ifndef _TRIANGULOS_
#define _TRIANGULOS_


/* ------------
   Tipo Abstrato de Dados TipoPontos

   Uma estrutura de pontos armazena uma lista de pontos x,y,z como GLfloats.
   Usaremos a estrutura da seguinte forma:
	- Será definido um vetor cujos elementos serao do tipo TipoPontos.
	- Os pontos serao indexados a partir do indice 1.
	- O elemento 0 do vetor contera o ponto médio de cada coordenada x,y,z. 
	  Isto sera util para calcular o ponto em torno do qual serao realizadas
	  rotacoes.
   ------------*/

struct Pontos
	{
   		GLfloat x;
		GLfloat y;
		GLfloat	z;
	};

typedef struct Pontos TipoPontos;


/* ------------
   Tipo Abstrato de Dados TipoTriangulo

   Uma estrutura de triangulos armazena uma lista de vertices v1,v2,v3
   como inteiros. Os vertices representam os indices do ponto correspondente
   na lista de pontos.
   Usaremos a estrutura da seguinte forma:
	- Será definido um vetor cujos elementos serao do tipo TipoTriangulos.
	- Os triangulos serao indexados a partir do indice 1.
	- O elemento 0 do vetor contera em v1 o numero de triangulos, em v2 o numero de pontos
	  do vetor de pontos correspondente e em v3 um numero inteiro que eh o seu nome, no
	  caso de termos mais de uma estrutura.
   ------------*/


struct Triangulo
	{
   		int v1;
		int v2;
		int	v3;
	};

typedef	struct Triangulo TipoTriangulo;


#endif
