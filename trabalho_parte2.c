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
	
	TCB_t* tcb_pa = (TCB_t*)criarTCB(ID_PA);
	TCB_t* tcb_pg = (TCB_t*)criarTCB(ID_PG);
	TCB_t* tcb_fibo = (TCB_t*)criarTCB(ID_FIBO);
	TCB_t* tcb_tri = (TCB_t*)criarTCB(ID_TRI);
	
	//Inicializar contextos!
	
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

int calculaPA() {
	int i;
	int result = 1;
	for(i=0; i < 8; i++) {
		result += 4;
		// 1. Imprimir valor na tela
		// 2. Trocar o contexto para o próximo na fila de contextos.
		// 3. Retornar ao final da fila.
	}
	// 4. (Saiu do laço) Não volta mais para o fim da fila, e libera a estrutura TCB
	
	return result;
}

int calculaPG() {
	int i;
	int result = 1;
	for(i=0; i< 10; i++) {
		result *= 2;
		// 1. Imprimir valor na tela
		// 2. Trocar o contexto para o próximo na fila de contextos.
		// 3. Retornar ao final da fila.
	}
	// 4. (Saiu do laço) Não volta mais para o fim da fila, e libera a estrutura TCB
	
	return result;
}

int calculaFibo() {
	return 0;
}

int calculaTri() {
	return 0;
}

}