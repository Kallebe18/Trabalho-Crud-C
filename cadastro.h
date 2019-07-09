#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#ifdef __unix__
#elif defined(_WIN32) || defined(WIN32)
    #define OS_Windows
#endif

void cadastra(void){
    FILE * pont_arq = NULL;
    char caminho_arq[100];
    int fim = 0;
    while(pont_arq == NULL){
	printf("\nDigite o nome do caminho do arquivo a ser criado: ");
	scanf(" %[^\n]", caminho_arq);
	if(!(strcmp(caminho_arq, "fim"))){
	    fim = 1;
	    break;
	}
	pont_arq = fopen(caminho_arq, "wb");
    }
    unsigned int matricula=-1;
    if(!(fim)){
    while(matricula != 0){
	#ifdef OS_Windows
	    system("cls");
	#else
	    system("clear");
	#endif

	int tamanho;
	char nome[100], situacao[100], line[100], nota[10];
	float notas_p[6], notas_l[6], nt, nf, mp=0, ml=0;
	unsigned int num_aus, i;
	printf("MATRICULA: ");
	scanf("%u", &matricula);
	if(matricula == 0){
	    break;
	}
	printf("NOME: ");
	scanf(" %[^\n]", nome);
	printf("NOTAS PROVA: ");
	for(i=0; i<6; i++){
	    scanf("%f", &notas_p[i]);
	    mp += notas_p[i];
	}
	mp /= 6;
	printf("NOTAS LISTA: ");
	for(i=0; i<6; i++){
	    scanf("%f", &notas_l[i]);
	    ml += notas_l[i];
	}
	ml /= 6;
	printf("NOTA TRABALHO: ");
	scanf("%f", &nt);
	printf("NUMERO DE AUSENCIAS: ");
	scanf("%u", &num_aus);
	nf = mp*0.8 + ml*0.1 + nt*0.1;
	if(nf >= 6 && num_aus < 32) strcpy(situacao, "Aprovado\n");
	else if(nf < 6 && num_aus < 32) strcpy(situacao, "Reprovado por nota\n");
	else if(nf >= 6 && num_aus >= 32) strcpy(situacao, "Reprovado por ausência\n");
	else {
	    strcpy(situacao, "Reprovado por ausencia e por nota\n");
	}
	sprintf(line, "===================================\n");
	tamanho = sizeof(line);
	fwrite(&line, sizeof(char), tamanho, pont_arq);
	sprintf(line, "MATRICULA: %u\n", matricula);
	fwrite(&line, sizeof(char), 100, pont_arq);
	sprintf(line, "NOME: %s\n", nome);
	fwrite(&line, sizeof(char), 100, pont_arq);
	sprintf(line, "NOTAS PROVA: ");
	for(i=0; i<6; i++){
	    sprintf(nota, "%.2f ", notas_p[i]); 
	    strcat(line, nota);
	}
	strcat(line, "\n");
	fwrite(&line, sizeof(char), 100, pont_arq);
	sprintf(line, "NOTAS LISTA: ");
	for(i=0; i<6; i++){
	    sprintf(nota, "%.2f ", notas_l[i]);
	    strcat(line, nota);
	}
	strcat(line, "\n");
	fwrite(&line, sizeof(char), 100, pont_arq);
	sprintf(line, "NOTA TRABALHO: %.2f\n", nt);
	fwrite(&line, sizeof(char), 100, pont_arq);
	sprintf(line, "NOTA FINAL: %.2f\n", nf);
	fwrite(&line, sizeof(char), 100, pont_arq);
	sprintf(line, "NUMERO DE AUSENCIAS: %u\n", num_aus);
	fwrite(&line, sizeof(char), 100, pont_arq);
	sprintf(line, "SITUACAO: %s", situacao);
	fwrite(&line, sizeof(char), 100, pont_arq);
	sprintf(line, "===================================\n");
	fwrite(&line, sizeof(char), tamanho, pont_arq);
    }
    fclose(pont_arq);
    }
}
