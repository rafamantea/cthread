/*
* 	Arquivo referente a primeira parte do trabalho.
*/
#include <stdio.h>
#include "include/support.h"
#include "include/cdata.h"

#define NUM_MAX_PROCESSOS 	10

#define CRIAR_PROCESSO 		0
#define	APTO_TO_EXECUTAR	1
#define	TERMINA_PROCESSO	2
#define	EXECUTAR_TO_BLOQUEADO	3
#define	EXECUTAR_TO_APTO	4
#define	BLOQUEADO_TO_APTO	5



void imprimir(int i, int r, int a, int e, int b, int t, char frase[]);
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

	// Declaracao das filas e dos iteradores de filas
	FILA2 apto;
	FILA2 executando;
	FILA2 bloqueado;

	PFILA2 iterador_apto;
	PFILA2 iterador_executando;
	PFILA2 iterador_bloqueado;

	// Atribuir enderecos aos ponteiros
	iterador_apto = &apto;
	iterador_executando = &executando;
	iterador_bloqueado = &bloqueado;

	// Criar as filas
	if( CreateFila2( iterador_apto ) ) {
		printf("Erro ao criar sFila2 'apto'\n");
		return 0;
	}

	printf("\n\nFila de aptos criada\n\n");

	if( CreateFila2( iterador_executando ) ) {
		printf("Erro ao criar sFila2 'executando'\n");
		return 0;
	}
	printf("Fila executando criada\n\n");
	
	if( CreateFila2( iterador_bloqueado ) ) {
		printf("Erro ao criar sFila2 'bloqueado'\n");
		return 0;
	}
	printf("Fila bloqueado criada\n\n");

	char *frase;
	char frase1[] = "Criar processo e inserir em apto";
	char frase2[] = "De apto para executando";

	int iteracao = 1; // i
	int r=0, a=0, e=0, b=0, t=0; 
	int flag_acao = -1;
	int process_id = 1;	
	int terminar_execucao = 0; // TRUE or FALSE

	if (iteracao > NUM_MAX_PROCESSOS) // Quando terminar *versão para teste*
			terminar_execucao = 1;
		
	while( !terminar_execucao ){	// Loop onde tudo acontece
		
		r = Random2();
		r = r%12;

		// passar as filas APTO, EXECUTAR, BLOQUEADO
		flag_acao = handleRemainder(r);

		if (flag_acao == CRIAR_PROCESSO) {
			if( process_id <= NUM_MAX_PROCESSOS) { // limitar o número máximo de processos pelo ID
				
				TCB_t* tcb = (TCB_t*)criarTCB(process_id); // criar processo
				process_id++;
				// inserir na fila de apto
				if( criarProcesso(iterador_apto, tcb) ) {
					printf("Erro ao inserir elemento na fila de aptos\n");
					return 0;
				}
				a++;	// mais um elemento em aptos
				frase = frase1;
			}
		}

		else if(flag_acao == APTO_TO_EXECUTAR){
			if(e == 0 && a > 0) { // ver se fila está vazia
				if( apto_to_executar(iterador_apto, iterador_executando) ) {
					printf("Erro ao retirar de apto e inserir em executando\n");
					return 0;
				}
				e++;
				a--;
				frase = frase2;
			}
		}

		//else if(flag_acao == TERMINA_PROCESSO){
		//	if() {
				/*

				*/
		//	}	
		//}

		/*
		*	COLOCAR AS OUTRAS CONDIÇÕES.
		*/


		imprimir(iteracao, r, a, e, b, t, frase);	// Imprimir os valores da execução

		frase = NULL;
		iteracao++;

		if (process_id > NUM_MAX_PROCESSOS) // Quando terminar *versão para teste*
			terminar_execucao = 1;
	}
}

void imprimir(int i, int r, int a, int e, int b, int t, char frase[]){
	printf("iteracao %d:	resto: %d	acao: %s\n", i, r, frase);
	printf("	Elementos em apto: %d\n", a);
	printf("	Elementos em executando: %d\n", e);
	printf("	Elementos em bloqueado: %d\n", b);
	printf("	Elementos em terminados: %d\n", t);
	printf("\n");
}

int handleRemainder(int n) {

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