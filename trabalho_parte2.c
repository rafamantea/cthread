/*	13/05/2017
* 	Arquivo referente a segunda parte do trabalho.
*/
#include <stdio.h>
#include <stdlib.h>
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

// Variáveis globais

FILA2 fila;					// insert
PFILA2 iterador_fila;		// insert

int main(){
	// Declaracao das filas e dos iteradores de filas
	//FILA2 fila; 			// remove
	//PFILA2 iterador_fila;	//remove

	// Declaração de contextos
	ucontext_t main_context, context_pa, context_pg, context_fibo, context_tri; //insert
	//ucontext_t *context_pa = malloc(sizeof(ucontext_t));	//remove
	//ucontext_t *context_pg = malloc(sizeof(ucontext_t));	//remove
	//ucontext_t *context_fibo = malloc(sizeof(ucontext_t));//remove
	//ucontext_t *context_tri = malloc(sizeof(ucontext_t));	//remove

	// Pilha para cada contexto
	char context_pa_stack[SIGSTKSZ];  /* Pilha para o contexto even */
	char context_pg_stack[SIGSTKSZ];  /* Pilha para o contexto even */
	char context_fibo_stack[SIGSTKSZ];  /* Pilha para o contexto even */
	char context_tri_stack[SIGSTKSZ];  /* Pilha para o contexto even */	
	
	//Inicializar contextos!
	getcontext(&context_pa);
	getcontext(&context_pg);
	getcontext(&context_fibo);
	getcontext(&context_tri);
	
	//Setar o uc_link dos contextos (todos voltam pro main_context)
	context_pa.uc_link = &main_context;
	context_pg.uc_link = &main_context;
	context_fibo.uc_link = &main_context;
	context_tri.uc_link =  &main_context;

	// Setar pilha e tamanho da pilha dos contextos
	context_pa.uc_stack.ss_sp = context_pa_stack;
	context_pa.uc_stack.ss_size = sizeof(context_pa_stack);
	context_pg.uc_stack.ss_sp = context_pg_stack;
	context_pg.uc_stack.ss_size = sizeof(context_pg_stack);
	context_fibo.uc_stack.ss_sp = context_fibo_stack;
	context_fibo.uc_stack.ss_size = sizeof(context_fibo_stack);
	context_tri.uc_stack.ss_sp = context_tri_stack;
	context_tri.uc_stack.ss_size = sizeof(context_tri_stack);
	
	// Função a ser executada em cada fluxo de controle
	makecontext(&context_pa, (void (*)(void))calculaPA, 0);
	makecontext(&context_pg, (void (*)(void))calculaPG, 0);
	makecontext(&context_fibo, (void (*)(void))calculaFibo, 0);
	makecontext(&context_tri, (void (*)(void))calculaTri, 0);






	// Atribuir enderecos aos ponteiros
	iterador_fila = &fila;
	
	// Criar a fila
	if( CreateFila2( iterador_fila ) ) {
		printf("Erro ao criar sFila2 apto\n");
		return 0;
	}	
	
	// Criar TCBs
	TCB_t* tcb_pa = (TCB_t*)criarTCB(ID_PA, context_pa);
	TCB_t* tcb_pg = (TCB_t*)criarTCB(ID_PG, context_pg);
	TCB_t* tcb_fibo = (TCB_t*)criarTCB(ID_FIBO, context_fibo);
	TCB_t* tcb_tri = (TCB_t*)criarTCB(ID_TRI, context_tri);
	
	
	//Inserir na fila PA
	if( insertTCB_at_queue(iterador_fila, tcb_pa) ) {	//insert
		printf("Erro ao inserir PA na fila\n");
		return 1; // erro
	}
	//Inserir na fila PG
	if( insertTCB_at_queue (iterador_fila, tcb_pg) ) {	//insert
		printf("Erro ao inserir PG na fila\n");
		return 1; // erro
	}
	
	//Inserir na fila FIBO
	if( insertTCB_at_queue(iterador_fila, tcb_fibo) ) {	//insert
		printf("Erro ao inserir FIBO na fila\n");
		return 1; // erro
	}
	
	//Inserir na fila TRI
	if( insertTCB_at_queue(iterador_fila, tcb_tri) ) {	//insert
		printf("Erro ao inserir TRI na fila\n");
		return 1; // erro
	}

	getcontext(&main_context);











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
