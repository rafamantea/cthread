/*
* 	Arquivo referente a primeira parte do trabalho.
*/
#include <stdio.h>
#include "include/support.h"
#define NUM_MAX_PROCESSOS 	10

#define CRIAR_PROCESSO 		0
#define	APTO_TO_EXECUTAR	1
#define	TERMINA_PROCESSO	2
#define	EXECUTAR_TO_BLOQUEADO	3
#define	EXECUTAR_TO_APTO	4
#define	BLOQUEADO_TO_APTO	5

void imprimir(int i, int r, int a, int e, int b, int t);
/*
*	i: iteração
*	r: resto
*	a: elementos em apto
*	e: elementos em executando
*	b: elementos em bloqueado
*	t: elementos terminados
*/

// function that handles the remainder
int handleRemainder(int remainder);
/*
*	0: 
*	1:
*	2:
*	3:
*	4:
*	5:
*	6:
*/


int main(){

	/*	Alocar espaço para as filas 'apto', 'executanto', 'bloqueado'. 
	*	USANDO SUPPORT.O
	*/
	int r=0, a=0, e=0, b=0, t=0;
	int flag_acao = 0, num_processos;
	int iteracao = 1;
	
	int terminar_execucao = 0; // TRUE or FALSE

	if (iteracao > NUM_MAX_PROCESSOS) // Quando terminar *versão para teste*
			terminar_execucao = 1;
		
	while( !terminar_execucao ){	// Loop onde tudo acontece
		
		r = Random2();
		r = r%12;

		// passar as filas APTO, EXECUTAR, BLOQUEADO
		flag_acao = handleRemainder(r);

		if (flag_acao == CRIAR_PROCESSO) {
			if( num_processos < NUM_MAX_PROCESSOS) { // limitar o número máximo de processos 
				
				criarProcesso(); // Implementar essa função em processador.c
			}
		}

		else if(flag_acao == APTO_TO_EXECUTAR){
			if() { // ver se fila está vazia
				/*
				*	CHAMAR FUNÇÃO DO PROCESSADOR
				*/
			}
		}

		else if(flag_acao == TERMINA_PROCESSO){
			if() {
				/*

				*/
			}	
		}

		/*
		*	COLOCAR AS OUTRAS CONDIÇÕES.
		*/


		imprimir(iteracao, r, a, e, b, t);	// Imprimir os valores da execução

		iteracao++;

		if (iteracao > NUM_MAX_PROCESSOS) // Quando terminar *versão para teste*
			terminar_execucao = 1;
	}
}

void imprimir(int i, int r, int a, int e, int b, int t){
	printf("iteracao %d:	resto: %d	acao: NOME_ACAO\n", i, r);
	printf("	Elementos em apto: %d\n", a);
	printf("	Elementos em executando: %d\n", e);
	printf("	Elementos em bloqueado: %d\n", b);
	printf("	Elementos em terminados: %d\n", t);
	printf("\n");
}

int handleRemainder(int remainder) {

	if(n == 6 || n == 0) {
		return CRIAR_PROCESSO;
		//Criar elemento TCB
		//Inserir na fila APTO
	} else if(n == 1 || n == 7) {
		return APTO_TO_EXECUTAR;
		//IF filaDeApto == 'vazia'
			//Retirar um elemento TCB da fila de APTO
			//Inserir na fila EXECUTANDO
		
	} else if(n == 2 || n == 8) {
		return TERMINA_PROCESSO;
		//IF filaExecutando != 'vaiza'
			//Retirar o elemento TCB da fila EXECUTANDO
			//Liberar espaço alocado pelo elemento TCB
		
	} else if(n == 3 || n == 9) {
		return EXECUTAR_TO_BLOQUEADO;
		//IF filaExecutando != 'vazia'
			//Retirar o elemento TCB da fila EXECUTANDO
			//Inserir na fila BLOQUEADO
	} else if(n == 4 || n == 10) {
		return EXECUTAR_TO_APTO;
		//IF filaExecutando != 'vazia'
			//Retirar o elemento TCB da fila EXECUTANDO
			//Inserir na fila APTO
	} else if(n == 5 || n == 11) {
		return BLOQUEADO_TO_APTO;
		//IF filaBloqueado != 'vazia'
			//Retirar um elemento da fila BLOQUEADO
			//Inserir na fila de APTO
	}
}
