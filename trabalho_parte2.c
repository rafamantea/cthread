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
void nextcontext();

// Variáveis globais

FILA2 fila;					// insert
PFILA2 iterador_fila;		// insert

int main(){

	// Declaração de contextos
	ucontext_t main_context, context_pa, context_pg, context_fibo, context_tri; //insert
	
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

	int returned = 0;
	getcontext(&main_context);

	/* Laço que não deixa continuar o fluxo da main até que a fila esteja vazia
	*/

	if( NextFila2(iterador_fila) != -1) {

		if (returned == 1) { 	// se alguma funcao terminou, remover da fila
			FirstFila2(iterador_fila);
			DeleteAtIteratorFila2(iterador_fila);
		}
		returned = 1;
		if( NextFila2(iterador_fila) == -1 ){
			printf("\nTerminando a main\n");
			return 0; //fim
		}

		//chama o primeiro nodo da fila
		FirstFila2(iterador_fila);
		PNODE2 nodo_atual;
		nodo_atual = GetAtIteratorFila2(iterador_fila);

		// seta para o contexto do TCB no primeiro nodo da fila
		setcontext( &(((TCB_t*)(nodo_atual->node))->context) );
		printf("\nIsso nunca pode aparecer na tela\n");
		return -1; // erro
	}

	printf("\nTerminando a main\n");

	//termina
	return 0;
}

void calculaPA() {
	int i;
	int result = 1;
	for(i=1; i <= 8; i++) {
		printf("PA termo %d\t: %d\n", i, result);
		result += 4;		
		nextcontext();
	}
}

void calculaPG() {
	int i;
	int result = 1;
	for(i=1; i <= 10; i++) {
		printf("PG termo %d\t: %d\n", i, result);
		result *= 2;		
		nextcontext();
	}
}

void calculaFibo() {
	int i, result = 1;
	int f0 = 0;
	int f1 = 1;
	for (i=1; i <= 12; i++) {
		printf("Fibo termo %d\t: %d\n", i, result);
		result = f0 + f1;
		f0 = f1;
		f1 = result;
		nextcontext();
	}
}

void calculaTri() {
	int i, result = 1;
	
	for(i=1; i <= 6; i++) {
		result = (i * (i + 1)) / 2;
		printf("Tri termo %d\t: %d\n", i, result);
		nextcontext();
	}
}

void nextcontext(){
	PNODE2 pnodo1, pnodo2;
	FirstFila2(iterador_fila);
	pnodo1 = GetAtIteratorFila2(iterador_fila);
	//se tiver só uma thread na fila
	if( NextFila2(iterador_fila) == -3 ){
		//volta pro mesmo contexto
		setcontext(&(((TCB_t*)(pnodo1->node))->context));
	}

	//pegar primeiro nodo da fila
	FirstFila2(iterador_fila);
	
	//deletar o primeiro da fila
	DeleteAtIteratorFila2(iterador_fila);

	//coloca no fim da fila
	AppendFila2(iterador_fila, pnodo1);

	LastFila2(iterador_fila);

	//pegar o novo primeiro
	FirstFila2(iterador_fila);
	pnodo2 = GetAtIteratorFila2(iterador_fila);

	//trocar contexto
	swapcontext( &(((TCB_t*)(pnodo1->node))->context), &(((TCB_t*)(pnodo2->node))->context) );
}





