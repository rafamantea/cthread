/*	13/05/2017
* 	Arquivo referente a segunda parte do trabalho.
*/
#include <stdio.h>
#include "include/support.h"
#include "include/cdata.h"
#include "processador.h"
#include <ucontext.h>

#define ID_PA 1
#define ID_PG 2
#define ID_FIBO 3
#define ID_TRI 4


void calculaPA();
void calculaPG();
void calculaFibo();
void calculaTri();

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
	
	TCB_t* tcb_pa = (TCB_t*)criarTCB(ID_PA);
	TCB_t* tcb_pg = (TCB_t*)criarTCB(ID_PG);
	TCB_t* tcb_fibo = (TCB_t*)criarTCB(ID_FIBO);
	TCB_t* tcb_tri = (TCB_t*)criarTCB(ID_TRI);
	
	//Inicializar contextos!
	getcontext(&context_pa);
	getcontext(&context_pg);
	getcontext(&context_fibo);
	getcontext(&context_tri);
	
	//Setar o uc_link dos contextos
//	context_pa.uc_link = ...
//	context_pg.uc_link = ...
//	context_fibo.uc_link = ...
//	context_tri.uc_link =  ...
	
	makecontext(&context_pa, (void (*)(void))calculaPA, 0);
	makecontext(&context_pg, (void (*)(void))calculaPG, 0);
	makecontext(&context_fibo, (void (*)(void))calculaFibo, 0);
	makecontext(&context_tri, (void (*)(void))calculaTri, 0);
	
	
	//Inserir na fila PA
	if( criarProcesso(iterador_fila, tcb_pa) ) {
		printf("Erro ao inserir PA na fila\n");
		return 1; // erro
	}
	//Inserir na fila PG
	if( criarProcesso(iterador_fila, tcb_pg) ) {
		printf("Erro ao inserir PG na fila\n");
		return 1; // erro
	}
	
	//Inserir na fila FIBO
	if( criarProcesso(iterador_fila, tcb_fibo) ) {
		printf("Erro ao inserir FIBO na fila\n");
		return 1; // erro
	}
	
	//Inserir na fila TRI
	if( criarProcesso(iterador_fila, tcb_tri) ) {
		printf("Erro ao inserir TRI na fila\n");
		return 1; // erro
	}
	return 0;
}

void calculaPA() {
	int i;
	int result = 1;
	for(i=0; i < 8; i++) {
		result += 4;
		// 1. Imprimir valor na tela
		// 2. Trocar o contexto para o próximo na fila de contextos.
		// 3. Retornar ao final da fila.
	}
	// 4. (Saiu do laço) Não volta mais para o fim da fila, e libera a estrutura TCB
}

void calculaPG() {
	int i;
	int result = 1;
	for(i=0; i< 10; i++) {
		result *= 2;
		// 1. Imprimir valor na tela
		// 2. Trocar o contexto para o próximo na fila de contextos.
		// 3. Retornar ao final da fila.
	}
	// 4. (Saiu do laço) Não volta mais para o fim da fila, e libera a estrutura TCB
}

void calculaFibo() {
	
}

void calculaTri() {
	
}

}