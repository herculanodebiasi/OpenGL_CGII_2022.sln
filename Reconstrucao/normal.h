#ifndef _NORMAL_H_
#  define _NORMAL_H_

#include "triangulos.h"

#  ifdef __cplusplus
extern "C" {
#  endif /* __cplusplus */

void reduzParaUnitario(TipoPontos *vector);
void calculaNormal(TipoPontos p1, TipoPontos p2, TipoPontos	p3, TipoPontos *retorno);

#  ifdef __cplusplus
}
#  endif /* __cplusplus */
#endif /* !_NORMAL_H_ */