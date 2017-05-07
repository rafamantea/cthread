/*	07/05/2017
* 	Arquivo referente a primeira parte do trabalho.
*/
#include <stdio.h>
#include "include/support.h"
#include "include/cdata.h"
#include "processador.h"

#define NUM_MAX_PROCESSOS 	30

#define CRIAR_PROCESSO 		0
#define	APTO_TO_EXECUTANDO	1
#define	TERMINA_PROCESSO	2
#define	EXECUTANDO_TO_BLOQUEADO	3
#define	EXECUTANDO_TO_APTO	4
#define	BLOQUEADO_TO_APTO	5

void imprimir(int i, int r, int a, int e, int b, int t, char frase[]);

// function that handles the remainder
int handleRemainder(int remainder);

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
		printf("Erro ao criar sFila2 apto\n");
		return 0;
	}
	if( CreateFila2( iterador_executando ) ) {
		printf("Erro ao criar sFila2 executando\n");
		return 0;
	}	
	if( CreateFila2( iterador_bloqueado ) ) {
		printf("Erro ao criar sFila2 bloqueado\n");
		return 0;
	}

	// frases usadas na saída
	char fraseGeral[] = "Nenhum evento";
	char frase0[] = "criacao de um elemento TCB";
	char frase1[] = "de apto para executando";
	char frase2[] = "terminar execucao de processo";
	char frase3[] = "de executando para bloqueado";
	char frase4[] = "de executando para apto";
	char frase5[] = "de bloqueado para apto";
	char *frase;
	frase = fraseGeral;

	// variaveis auxiliares para a parte1 do trabalho
	int iteracao = 1; 
	int r=0, a=0, e=0, b=0, t=0; 
	int flag_acao = -1;
	int terminar_execucao = 0; // TRUE or FALSE		

	int process_id = 1;	// gerador de id unico para cada TCB

	while( !terminar_execucao ){	// Loop onde tudo acontece (trabalho parte 1)
		
		r = Random2();	// gerar numero aleatorio
		r = r%12;

		flag_acao = handleRemainder(r); // tratar o numero aleatorio

		if (flag_acao == CRIAR_PROCESSO) {
			if( process_id <= NUM_MAX_PROCESSOS) { // limitar o número máximo de processos pelo ID
				
				TCB_t* tcb = (TCB_t*)criarTCB(process_id); // criar processo
				process_id++;
				// inserir na fila de apto
				if( criarProcesso(iterador_apto, tcb) ) {
					printf("Erro ao inserir elemento na fila de aptos\n");
					return 1; // erro
				}
				a++;	// mais um elemento em aptos
				frase = frase0;
			}
		}

		else if(flag_acao == APTO_TO_EXECUTANDO){
			if(e == 0 && a > 0) { // executando esta livre e fila apto está vazia
				if( apto_to_executando(iterador_apto, iterador_executando) ) {
					printf("Erro ao retirar de apto e inserir em executando\n");
					return 1; // erro
				}
				e++;
				a--;
				frase = frase1;
			}
		}

		else if(flag_acao == TERMINA_PROCESSO){
			if( e > 0) { // há processo executando
				if ( libera_executando(iterador_executando) ) {
					printf("Erro ao retirar elementos da fila de executando\n");
					return 1; // erro
				}
				e--;
				t++;
				frase = frase2;
			}
		}

		else if(flag_acao == EXECUTANDO_TO_BLOQUEADO) {
			if( e > 0) {
				if ( executando_to_bloqueado(iterador_executando, iterador_bloqueado) ) {
					printf("Erro ao retirar de executando e inserir em bloqueado\n");
					return 1; // erro
				}
				e--;
				b++;
				frase = frase3;
			}
		}
		
		else if(flag_acao == EXECUTANDO_TO_APTO) {
			if( e > 0) {
				if ( executando_to_apto(iterador_executando, iterador_apto) ) {
					printf("Erro ao retirar de executando e inserir em apto\n");
					return 1; // erro
				}
				e--;
				a++;
				frase = frase4;
			}
		}

		else if(flag_acao == BLOQUEADO_TO_APTO) {
			if( b > 0) {
				if ( bloqueado_to_apto(iterador_bloqueado, iterador_apto) ) {
					printf("Erro ao retirar de bloqueado e inserir em apto\n");
					return 1; // erro
				}
				b--;
				a++;
				frase = frase5;
			}
		}		

		imprimir(iteracao, r, a, e, b, t, frase);	// Imprimir os valores da execução

		frase = fraseGeral; // Quando nenhuma opcao eh selecionada
		iteracao++;

		// condicao de parada
		if ( process_id > NUM_MAX_PROCESSOS && (a==0) && (e==0) && (b==0) ) 
			terminar_execucao = 1;
	}
	return 0;
}

/*	
*	i: iteração
*	r: resto
*	a: elementos em apto
*	e: elementos em executando
*	b: elementos em bloqueado
*	t: elementos terminados
*/
void imprimir(int i, int r, int a, int e, int b, int t, char frase[]){
	printf("iteracao %d:	resto: %d	acao: %s\n", i, r, frase);
	printf("	Elementos em apto: %d\n", a);
	printf("	Elementos em executando: %d\n", e);
	printf("	Elementos em bloqueado: %d\n", b);
	printf("	Elementos em terminados: %d\n", t);
	printf("\n");
}

/*
*	0 or 6: 	criar TCB e colocar em apto (inicio do processo)
*	1 or 7:		de apto para executando
*	2 or 8:		terminar processo
*	3 or 9:		executando to bloqueado
*	4 or 10:	executando to apto
*	5 or 11:	bloqueado to apto
*/
int handleRemainder(int n) {

	if(n == 6 || n == 0) {
		return CRIAR_PROCESSO;
		//Criar elemento TCB
		//Inserir na fila APTO
	} else if(n == 1 || n == 7) {
		return APTO_TO_EXECUTANDO;
		//IF filaDeApto == 'vazia'
			//Retirar um elemento TCB da fila de APTO
			//Inserir na fila EXECUTANDO
		
	} else if(n == 2 || n == 8) {
		return TERMINA_PROCESSO;
		//IF filaExecutando != 'vaiza'
			//Retirar o elemento TCB da fila EXECUTANDO
			//Liberar espaço alocado pelo elemento TCB
		
	} else if(n == 3 || n == 9) {
		return EXECUTANDO_TO_BLOQUEADO;
		//IF filaExecutando != 'vazia'
			//Retirar o elemento TCB da fila EXECUTANDO
			//Inserir na fila BLOQUEADO
	} else if(n == 4 || n == 10) {
		return EXECUTANDO_TO_APTO;
		//IF filaExecutando != 'vazia'
			//Retirar o elemento TCB da fila EXECUTANDO
			//Inserir na fila APTO
	} else if(n == 5 || n == 11) {
		return BLOQUEADO_TO_APTO;
		//IF filaBloqueado != 'vazia'
			//Retirar um elemento da fila BLOQUEADO
			//Inserir na fila de APTO
	} else {
		return -1;
	}

}