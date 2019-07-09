#include <stdio.h>
#include <stdlib.h>
#include "cadastro.h"
#include "consulta_mat.h"
#include "altera_mat.h"
#include "listagem.h"
#ifdef __unix__
#elif defined(_WIN32) || defined(WIN32)
    #define OS_Windows
#endif

void main(void){
    int op = -1;
    while(op != 5){
	#ifdef OS_Windows
	    system("cls");
	#else
	    system("clear");
	#endif

	printf("==========================================\n");
	printf("1 - Cadastrar uma turma\n");
	printf("2 - Consultar um aluno\n");
	printf("3 - Alterar dados de um aluno\n");
	printf("4 - Listar dados de uma turma\n");
	printf("5 - Terminar a execucao\n");
	printf("==========================================\n");
	printf(">>> ");
	scanf("%d", &op);
	if(op == 1) cadastra();
	if(op == 2) consulta();
	if(op == 3) altera();
	if(op == 4) {
	    int retorno;
	    while(retorno != 0) retorno = lista();
	}
    }
}
