#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#ifdef __unix__
#elif defined(_WIN32) || defined(WIN32)
    #define OS_Windows
#endif

void consulta(void){
    FILE * pont_arq = NULL;
    char caminho_arq[100];
    int fim = 0;
    while(pont_arq == NULL){
	printf("Digite o caminho do arquivo a ser consultado: ");
	scanf(" %[^\n]", caminho_arq);
	if(!(strcmp(caminho_arq, "fim"))) {
	    fim = 1;
	    break;
	}
	pont_arq = fopen(caminho_arq, "rb");
    }
    char line[100], line2[100];
    unsigned int matricula = -1, achou = 0;
    if(!(fim)){
	while(matricula != 0){
	    printf("MATRICULA: ");
	    scanf("%u", &matricula);

	    #ifdef OS_Windows
		system("cls");
	    #else
		system("clear");
	    #endif

	    sprintf(line2, "MATRICULA: %u\n", matricula);
	    while(fread(line, sizeof(char), 100, pont_arq)){
		if(!(strcmp(line, line2))){
		    printf("==================================\n");
		    achou = 1;
		}
		if(achou) {
		    printf("%s", line);
		    achou++;
		}
		if(achou == 10) achou = 0;
	    }
	    rewind(pont_arq);
	}
    }
    fclose(pont_arq);
}
