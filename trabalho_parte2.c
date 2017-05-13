/*	13/05/2017
* 	Arquivo referente a segunda parte do trabalho.
*/
#include <stdio.h>
#include "include/support.h"
#include "include/cdata.h"
#include "processador.h"
#include <ucontext.h>

int calculaPA();
int calculaPG();
int calculaFibo();
int calculaTri();

int main(){
	// Declaracao das filas e dos iteradores de filas
	FILA2 fila;
	PFILA2 iterador_fila;

	// Declaração de contextos
	ucontext_t *context_pa = malloc(sizeof(ucontext_t));
	ucontext_t *context_pg = malloc(sizeof(ucontext_t));
	ucontext_t *context_fibo = malloc(sizeof(ucontext_t));
	ucontext_t *context_tri = malloc(sizeof(ucontext_t));
	
	// Atribuir enderecos aos ponteiros
	iterador_fila = &fila;
	
	// Criar a fila
	if( CreateFila2( iterador_fila ) ) {
		printf("Erro ao criar sFila2 apto\n");
		return 0;
	}

	int tid = 1;
	TCB_t* tcb = (TCB_t*)criarTCB(tid);

	//Inserir processo na fila
	if( criarProcesso(iterador_apto, tcb) ) {
		printf("Erro ao inserir elemento na fila\n");
		return 1; // erro
	}

	return 0;
}

int calculaPA() {
	int i;
	int result = 1;
	for(i=0; i < 8; i++) {
		result += 4;
	}
	
	return result;
}

int calculaPG() {
	int i;
	int result = 1;
	for(i=0; i< 10; i++) {
		result *= 2;
	}
	
	return result;
}

int calculaFibo() {
	return 0;
}

int calculaTri() {
	return 0;
}

}