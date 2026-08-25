/* Projeto - Filtro em C*/
#include <dirent.h> //só funciona no gcc
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
  char r, nomeFinal[512];
  clock_t begin, end;
  double time_per_img, time_total = 0.0;
  unsigned int qtd_imagens = 0;

  d = opendir("./Colon_TMA");
  if (d) {
    while ((dir = readdir(d)) != NULL) {
      if ((strcmp(dir->d_name, ".") == 0 || strcmp(dir->d_name, "..") == 0)) {
        continue;
      }

      printf("%s\n", dir->d_name);
      snprintf(nomeFinal, sizeof(nomeFinal), "Colon_TMA/%s", dir->d_name);

      readPGMImage(&imgIn, nomeFinal);

      for (int j = 0; j < 256; j++) {
        hist[j] = 0;
      }

      begin = clock();
      lbp(&imgIn, hist);
      end = clock();

      time_per_img = (double)(end - begin) / CLOCKS_PER_SEC;
      time_total += time_per_img;
      qtd_imagens++;

      r = *(dir->d_name);
      writeHistograma(hist, &r);
    }

    closedir(d);

    if (qtd_imagens > 0) {
      printf("Tempo médio: %lf\n", time_total / qtd_imagens);
    } else {
      printf("Tempo médio: 0.000000\n");
    }

    printf("Tempo Total: %lf\n", time_total);
  }

  return 0;
}
