#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#ifdef __unix__
#elif defined(_WIN32) || defined(WIN32)
    #define OS_Windows
#endif

int lista(void){
    FILE * pont_arq = NULL;
    char caminho_arq[100];
    int fim = 0;
    while(pont_arq == NULL){
	printf("Digite o caminho do arquivo a ser listado: ");
	scanf(" %[^\n]", caminho_arq);
	if(!(strcmp(caminho_arq, "fim"))){
	    fim = 1;
	    break;
	}
	pont_arq = fopen(caminho_arq, "rb");
    }
    if(!(fim)){
    char line[100];
    int contador = 0;
    while(fread(&line, sizeof(char), 100, pont_arq)){
	contador++;
    }
    rewind(pont_arq);
    char alunos[contador][100];

    contador = 0;
    while(fread(&line, sizeof(char), 100, pont_arq)){
	strcpy(alunos[contador], line);
	contador++;
    }

    int op = -1, i, j, k, l, m;
    while(op != 5){
	#ifdef OS_Windows
	    system("cls");
	#else
	    system("clear");
	#endif

	printf("=========================================================\n");
	printf("1 - Listar os alunos por ordem crescente de matricula\n");
	printf("2 - Listar os alunos por ordem alfabetica de nome\n");
	printf("3 - Listar os alunos por ordem crescente de nota final\n");
	printf("4 - Terminar e voltar para processar nova turma\n");
	printf("5 - Terminar a execucao do modulo\n");
	printf("=========================================================\n");
	scanf("%d", &op);
	if(op == 1){
	    char temp[100];
	    for(i=0; i<contador-1; i++){
		if(strstr(alunos[i], "MATRICULA") != NULL){
		    int tam, som = 0;
		    tam = strlen(alunos[i]);
		    for(j=0; j<tam; j++){
			som += (int)alunos[i][j];
		    }
		    for(k=i+1; k<contador; k++){
			if(strstr(alunos[k], "MATRICULA") != NULL){
			    int som2 = 0;
			    tam = strlen(alunos[k]);
			    for(l=0; l<tam; l++){
				som2 += (int)alunos[k][l];
			    }
			    if(som > som2){
				for(l=0; l<8; l++){
				    strcpy(line, alunos[i+l]);
				    strcpy(temp, alunos[k+l]);
				    strcpy(alunos[k+l], alunos[i+l]);
				    strcpy(alunos[i+l], temp);
				}
			    }
			}
		    }
		}
	    }
	    for(i=0; i<contador; i++){
		printf("%s", alunos[i]);
	    }
	}
	if(op == 2){
	    char temp[100];
	    for(i=0; i<contador-1; i++){
		if(strstr(alunos[i], "NOME") != NULL){
		    for(k=i+1; k<contador; k++){
			if(strstr(alunos[k], "NOME") != NULL){
			    if(strcmp(alunos[i], alunos[k]) > 0){
				for(l=0; l<8; l++){
				    strcpy(line, alunos[i+l]);
				    strcpy(temp, alunos[k+l]);
				    strcpy(alunos[k+l], alunos[i+l]);
				    strcpy(alunos[i+l], temp);
				}
			    }
			}
		    }
		}
	    }
	    for(i=0; i<contador; i++){
		printf("%s", alunos[i]);
	    }	
	}
	if(op == 3){
	    char temp[100];
	    for(i=0; i<contador-1; i++){
		if(strstr(alunos[i], "NOTA FINAL") != NULL){
		    int tam, som = 0;
		    tam = strlen(alunos[i]);
		    for(j=0; j<tam; j++){
			som += (int)alunos[i][j];
		    }
		    for(k=i+1; k<contador; k++){
			if(strstr(alunos[k], "NOTA FINAL") != NULL){
			    int som2 = 0;
			    tam = strlen(alunos[k]);
			    for(l=0; l<tam; l++){
				som2 += (int)alunos[k][l];
			    }
			    if(som2 < som){
				for(l=-5; l<3; l++){
				    strcpy(line, alunos[i+l]);
				    strcpy(temp, alunos[k+l]);
				    strcpy(alunos[k+l], alunos[i+l]);
				    strcpy(alunos[i+l], temp);
				}
			    }
			}
		    }
		}
	    }
	    for(i=0; i<contador; i++){
		printf("%s", alunos[i]);
	    }
	}
	if(op == 4){
	    return 1;
	}
	printf("PRESSIONE QUALQUER TECLA PARA CONTINUAR\n");
	getchar();
	getchar();
    }
    }
    return 0;
}
