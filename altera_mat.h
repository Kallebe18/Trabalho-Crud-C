#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#ifdef __unix__
#elif defined(_WIN32) || defined(WIN32)
    #define OS_Windows
#endif

void altera(void){
    FILE * pont_arq = NULL;
    char caminho_arq[100];
    int fim = 0;
    while(pont_arq == NULL){
	printf("Digite o diretorio do arquivo a ser alterado: ");
	scanf(" %[^\n]", caminho_arq);
	if(!(strcmp(caminho_arq, "fim"))){
	    fim = 1;
	    break;
	}
	pont_arq = fopen(caminho_arq, "rb");
    }
    unsigned int matricula = -1;
    char line[100], line2[100];
    if(!(fim)){
    while(matricula != 0){
	#ifdef OS_Windows
	    system("cls");
	#else
	    system("clear");
	#endif

	pont_arq = fopen(caminho_arq, "rb");
	int contador=0, pos_mat, i;
	printf("MATRICULA A SER ALTERADA: ");
	scanf("%u", &matricula);
	sprintf(line2, "MATRICULA: %u\n", matricula);
	if(matricula == 0){
	    break;
	}
	while(fread(&line, sizeof(char), 100, pont_arq)){
	    if(!(strcmp(line, line2))) {
		pos_mat = contador;
	    }
	    contador++;
	}
	char alunos[contador][100];
	rewind(pont_arq);
	int contador2 = 0;
	while(fread(&line, sizeof(char), 100, pont_arq)){
	    strcpy(alunos[contador2], line);
	    contador2++;
	}

	rewind(pont_arq);
	
	fclose(pont_arq);
	pont_arq = fopen(caminho_arq, "wb");

	printf("\nALTERANDO DADOS DA MATRICULA %u", matricula);
	char nome[100], situacao[100], nota[10];
	float notas_p[6], notas_l[6], nt, nf, ml=0, mp=0;
	unsigned int num_aus;
	int condicao;

	printf("\nMATRICULA: ");
	scanf("%u", &matricula);
	sprintf(line2, "MATRICULA: %u\n", matricula);
	strcpy(alunos[pos_mat], line2);

	printf("NOME: ");
	scanf(" %[^\n]", nome);
	sprintf(line2, "NOME: %s\n", nome);
	strcpy(alunos[pos_mat+1], line2);

	printf("NOTAS PROVA: ");
	sprintf(line2, "NOTAS PROVA: ");
	for(i=0; i<6; i++){
	    scanf("%f", &notas_p[i]);
	    sprintf(nota, "%.2f ", notas_p[i]);
	    strcat(line2, nota);
	    mp += notas_p[i];
	}
	mp /= 6;
	strcat(line2, "\n");
	strcpy(alunos[pos_mat+2], line2);

	condicao = 0;
	printf("NOTAS LISTA: ");
	sprintf(line2, "NOTAS LISTA: ");
	for(i=0; i<6; i++){
	    scanf("%f", &notas_l[i]);
	    sprintf(nota, "%.2f ", notas_l[i]);
	    strcat(line2, nota);
	    ml += notas_l[i];
	}
	ml /= 6;
	strcat(line2, "\n");
	strcpy(alunos[pos_mat+3], line2);

	printf("NOTA TRABALHO: ");
	scanf("%f", &nt);
	sprintf(line2, "NOTA TRABALHO: %.2f\n", nt);
	strcpy(alunos[pos_mat+4], line2);

	nf = mp*0.8 + ml*0.1 + nt*0.1;
	sprintf(line2, "NOTA FINAL: %.2f\n", nf);
	strcpy(alunos[pos_mat+5], line2);

	printf("NUMERO AUSENCIAS: ");
	scanf("%u", &num_aus);
	sprintf(line2, "NUMERO AUSENCIAS: %u\n", num_aus);
	strcpy(alunos[pos_mat+6], line2);

	if(nf >= 6 && num_aus < 32) strcpy(situacao, "SITUACAO: Aprovado\n");
	else if(nf < 6 && num_aus < 32) strcpy(situacao, "SITUACAO: Reprovado por nota\n");
	else if(nf >= 6 && num_aus >= 32) strcpy(situacao, "SITUACAO: Reprovado por ausência\n");
	else {
	    strcpy(situacao, "SITUACAO: Reprovado por ausencia e por nota\n");
	}
	strcpy(line2, situacao);
	strcpy(alunos[pos_mat+7], line2);
	
	for(i=0; i<contador2; i++){
	    fwrite(&alunos[i], sizeof(char), 100, pont_arq);
	}

	rewind(pont_arq);
    }
    fclose(pont_arq);
    }
}
