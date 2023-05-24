/* Projeto - Filtro em C*/
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#include "pj.h"

int main(void){
  DIR *d;
  struct pgm imgIn;
  struct dirent *dir;
  unsigned int hist[256];
  char r, nomeFinal[200];
  clock_t begin, end;
	double time_per_img, time_total=0; 
   
  d = opendir("./imagens");
  if (d)  {
    while ((dir = readdir(d)) != NULL){
      //filtro os dados ("." e "..") gerados da abertura de diretorio
      if((strcmp(dir->d_name, ".")==0 || strcmp(dir->d_name, "..")==0)) continue;
      printf("%s\n", dir->d_name);
			// formata uma string e guardar o resultado em um array, uma especie de concatenação
      //feito isso para passar o caminho correto para a leitura do arquivo
      sprintf(nomeFinal, "imagens/%s", dir->d_name);
      // Leitura da Imagem -PGM
      readPGMImage(&imgIn, nomeFinal);
      //zero o vetor do histograma
      for(int j=0;j<256;j++)  hist[j]=0;
      //inicia a contagem de tempo da função de LBP (Local Binary Patterns)      
      begin = clock();
      lbp(&imgIn,  hist);
      end = clock();
      //encerra a contagem de tempo, calcula a media e o tempo total				
			time_per_img = (double)(end - begin) / CLOCKS_PER_SEC;				
			time_total += time_per_img;
      //captura o rotulo
      r = *(dir->d_name);
      //escreve o histograma
      writeHistograma(hist, &r);
    }
    closedir(d);
    printf("Tempo médio: %lf\n",time_total/QTDIMG);
		printf("Tempo Total: %lf\n",time_total);
  }
  return(0);
}