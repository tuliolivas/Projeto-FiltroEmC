#ifndef PJ_H_INCLUDED
#define PJ_H_INCLUDED

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define QTDIMG 656

struct pgm{
	int tipo;
	int c;
	int r;
	int mv;
	unsigned char *pData;
};

void readPGMImage(struct pgm *, char *);
void viewPGMImage(struct pgm *);
void writePGMImage(struct pgm *, char *);
//funções criadas
void lbp(struct pgm *, unsigned int *);
void writeHistograma(unsigned int *h, char *rotulo);
void limparBuffer (void);
#endif