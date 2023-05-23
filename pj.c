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
	int contc = 1, contl = 1,  n;
	for(int i=0;i<(a->r)*(a->c);i++){
		n=0;    
		if(!((contc-1<1) || (*(a->pData+(i-1)) < *(a->pData+i)))){
			n+=128;
		}
		if(!((contl+1>a->r) || (contc-1<1) || (*(a->pData+i+(a->c-1)) < *(a->pData+i)))){
			n+=64;
		}
		if(!((contl+1>a->r) || (*(a->pData+i+a->c) < *(a->pData+i)))){
		  n+=32;
		}
		if(!((contl+1>a->r) || (contc+1>a->c) || (*(a->pData+i+(a->c+1))<*(a->pData+i)))){
			n+=16;
		}
		if(!((contc+1>a->c) || (*(a->pData+i+1)<*(a->pData+i)))){
			n+=8;
		}
		if(!((contl-1<1) || (contc+1>a->c) || (*(a->pData+i-(a->c-1))<(*(a->pData+i))))){
			n+=4;
		}
		if(!((contl-1<1) || (*(a->pData+i-a->c))<(*(a->pData+i)))){
			n+=2;
		}
		if(!((contl-1<1) || (contc-1<1) || (*(a->pData+i-(a->c+1)))<(*(a->pData+i)))){
			n+=1;
		}
    	(*(ph+n))++;
    	if(contc%(a->c)==0){
     		contl++;
			  contc=1;
    	}
    	else contc++;
	}
}

void writeHistograma(unsigned int *h, char *rotulo){
	FILE *fp;
	char ch;

	if (!(fp = fopen("Histograma.csv","a"))){
		perror("Erro.");
		exit(1);
	}

	for (int i = 0; i < 257; i++)
	{
		if (i == 256)
		{
			fprintf(fp, "%c\n", *rotulo);
			break;
		}
		
		fprintf(fp, "%u;", *(h + i));
	}

	fclose(fp);

}

void limparBuffer (void){
  char c;
  while((c=getchar())!='\n' && c!=EOF);
}