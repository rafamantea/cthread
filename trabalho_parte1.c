/*
* 	Arquivo referente a primeira parte do trabalho.
*/
#include <stdio.h>
#include "include/support.h"
#define NUM_MAX_PROCESSOS 10

void imprimir(int i, int r, int a, int e, int b, int t);
/*
*	i: iteração
*	r: resto
*	a: elementos em apto
*	e: elementos em executando
*	b: elementos em bloqueado
*	t: elementos terminados
*/
int main(){

	/*	Alocar espaço para as filas 'apto', 'executanto', 'bloqueado'. 
	*	USANDO SUPPORT.O
	*/
	int r=0, a=0, e=0, b=0, t=0;
	int iteracao = 1;
	
	int terminar_execucao = 0; // TRUE or FALSE

	if (iteracao > NUM_MAX_PROCESSOS) // Quando terminar *versão para teste*
			terminar_execucao = 1;
		
	while( !terminar_execucao ){	// Loop onde tudo acontece
		
		r = Random2();

		// Definir as condições do que acontece com a maquina de estados de acordo com o resto
			// Isso acontece no processador
		
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
