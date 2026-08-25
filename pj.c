#include "pj.h"

void readPGMImage(struct pgm *pio, char *filename){

	FILE *fp;
	char ch;

	if (!(fp = fopen(filename,"r"))){
		perror("Erro.");
		exit(1);
	}
  
	if ((ch = getc(fp)) !='P'){
    printf("%d", ch);
		puts("A imagem fornecida não está no formato pgm");
		exit(2);
	}
	
	pio->tipo = getc(fp)-48;
	
	fseek(fp,1, SEEK_CUR);

	while((ch=getc(fp))=='#'){
		while( (ch=getc(fp))!='\n');
	}

	fseek(fp,-1, SEEK_CUR);

	fscanf(fp, "%d %d",&pio->c,&pio->r);
	if (ferror(fp)){ 
		perror(NULL);
		exit(3);
	}	
	fscanf(fp, "%d",&pio->mv);
	fseek(fp,1, SEEK_CUR);

	pio->pData = (unsigned char*) malloc(pio->r * pio->c * sizeof(unsigned char));

	switch(pio->tipo){
		case 2:
			puts("Lendo imagem PGM (dados em texto)");
			for (int k=0; k < (pio->r * pio->c); k++){
				fscanf(fp, "%hhu", pio->pData+k);
			}
		break;	
		case 5:
			puts("Lendo imagem PGM (dados em binário)");
			fread(pio->pData,sizeof(unsigned char),pio->r * pio->c, fp);
		break;
		default:
			puts("Não está implementado");
	}
	
	fclose(fp);

}

void writePGMImage(struct pgm *pio, char *filename){
	FILE *fp;
	char ch;

	if (!(fp = fopen(filename,"wb"))){
		perror("Erro.");
		exit(1);
	}

	fprintf(fp, "%s\n","P5");
	fprintf(fp, "%d %d\n",pio->c, pio->r);
	fprintf(fp, "%d\n", 255);

	fwrite(pio->pData, sizeof(unsigned char),pio->c * pio->r, fp);

	fclose(fp);

}

void viewPGMImage(struct pgm *pio){
	printf("Tipo: %d\n",pio->tipo);
	printf("Dimensões: [%d %d]\n",pio->c, pio->r);
	printf("Max: %d\n",pio->mv);

	for (int k=0; k < (pio->r * pio->c); k++){
		if (!( k % pio->c)) printf("\n");
		printf("%2hhu ",*(pio->pData+k));
	}	
	printf("\n");
}
//nossas funções
void lbp(struct pgm *a, unsigned int *ph) {
	int cols = a->c;
	int rows = a->r;

	for (int y = 0; y < rows; y++) {
		for (int x = 0; x < cols; x++) {
			int center = y * cols + x;
			unsigned char center_value = a->pData[center];
			unsigned int code = 0;
			int bit_index = 0;

			int offsets[8][2] = {
				{-1, -1}, {0, -1}, {1, -1},
				{1, 0},   {1, 1},  {0, 1},
				{-1, 1},  {-1, 0}
			};

			for (int k = 0; k < 8; k++) {
				int nx = x + offsets[k][0];
				int ny = y + offsets[k][1];

				if (nx >= 0 && nx < cols && ny >= 0 && ny < rows) {
					unsigned char neighbor_value = a->pData[ny * cols + nx];
					if (neighbor_value >= center_value) {
						code |= (1u << (7 - bit_index));
					}
				}

				bit_index++;
			}

			ph[code]++;
		}
	}
}

void writeHistograma(unsigned int *h, char *rotulo){
	FILE *fp;

	if (!(fp = fopen("Histograma.csv","a"))){
		perror("Erro.");
		exit(1);
	}

	for (int i = 0; i < 256; i++)
	{
		fprintf(fp, "%u;", h[i]);
	}

	fprintf(fp, "%c\n", *rotulo);
	fclose(fp);
}

void limparBuffer (void){
  char c;
  while((c=getchar())!='\n' && c!=EOF);
}