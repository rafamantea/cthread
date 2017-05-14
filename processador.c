/*	07/05/2017
* 	Implementação das funções da máquina de estados que representa o processador.
*/

/*
*	CASO 0 e 6: 	Alocar espaço para um novo TCB e inserir na fila de aptos.
*
*	CASO 1 e 7:  	Retirar um elemento TCB da fila de apto e inserir na fila de executando
*					se a fila de executando estiver vazia, caso contrário, nada deverá acontecer.
*
*	CASO 2 e 8:		Retirar o elemento TCB da fila de executando e liberar o espaço alocado pelo elemento TCB
*					(simula o término de uma thread). Se a fila de executando estiver vazia, nada deve ser feito. 
*
*	CASO 3 e 9:		Retirar o elemento TCB da fila de executando e inserir na fila de bloqueado (simula uma
*					thread sendo bloqueada). Se a fila de executando estiver vazia, nada deve ser feito.
*
*	CASO 4 e 10:	Retirar o elemento TCB da fila de executando e inserir na fila de apto (simula a cedência
*					voluntária do processador). Se a fila de executando estiver vazia, nada deve ser feito. 
*
*	CASO 5 e 11:	Retirar um elemento da fila de bloqueado e inserir na fila de apto. Se a fila de 
*					bloqueado estiver vazia, nada deverá ser feito.
*
*/

#include "include/cdata.h"
#include "include/support.h"
#include "processador.h"
#include <stdio.h>
#include <stdlib.h>
#include <ucontext.h>

int insertTCB_at_queue(PFILA2 fila, TCB_t* tcb) {
	PNODE2 pnodo = malloc(sizeof(NODE2));	// alocar espaço para um novo nodo na fila
	pnodo->node = tcb;

	if ( AppendFila2(fila, pnodo) ){
		printf( "Erro ao inserir TCB na fila");
		return 1;
	}
	return 0;
}

int criarProcesso(PFILA2 aptos, TCB_t* tcb) {

	PNODE2 pnodo = malloc(sizeof(NODE2));	// alocar espaço para um novo nodo na fila
	pnodo->node = tcb;

	if (adicionarNaFilaAptos(aptos, pnodo) ){
		printf( "Erro ao inserir elemento em apto");
		return 1;
	}
	return 0;
}

TCB_t* criarTCB(int tid) {
	TCB_t* tcb = malloc(sizeof(TCB_t));
    tcb->tid = tid;	
    tcb->state = PROCST_CRIACAO;
    // salvar contexto no TCB

	
	return tcb;
}

int adicionarNaFila(PFILA2 fila, PNODE2 pnodo) {
	return AppendFila2(fila, pnodo);
}

int adicionarNaFilaAptos(PFILA2 aptos, PNODE2 pnodo) {
	((TCB_t*)(pnodo->node))->state = PROCST_APTO;
	return adicionarNaFila(aptos, pnodo);
}

int adicionarNaFilaExecutando(PFILA2 executando, PNODE2 pnodo) {
	((TCB_t*)(pnodo->node))->state = PROCST_EXEC;
	return adicionarNaFila(executando, pnodo);
}

int apto_to_executando(PFILA2 iterador_apto, PFILA2 iterador_executando) {
	FirstFila2(iterador_apto); // iterador no inicio da fila
	PNODE2 pnodo = GetAtIteratorFila2(iterador_apto);
	
	if( DeleteAtIteratorFila2(iterador_apto) ) {
		printf("Nao conseguiu retirar elemento de apto\n");
		return 1; // erro
	}
	if ( adicionarNaFilaExecutando(iterador_executando, pnodo)) {
		printf("Erro ao inserir em executando\n");
		return 1; // erro
	}
	return 0;
}

int executando_to_bloqueado(PFILA2 iterador_executando, PFILA2 iterador_bloqueado) {
	FirstFila2(iterador_executando);
	PNODE2 pnodo = GetAtIteratorFila2(iterador_executando);

	if( DeleteAtIteratorFila2(iterador_executando) ) {
		printf("Nao conseguiu retirar elemento de executando\n");
		return 1; // erro
	}
	if ( adicionarNaFilaExecutando(iterador_bloqueado, pnodo)) {
		printf("Erro ao inserir em bloqueado\n");
		return 1; // erro
	}
	return 0;
}

int executando_to_apto(PFILA2 iterador_executando, PFILA2 iterador_apto) {
	FirstFila2(iterador_executando);
	PNODE2 pnodo = GetAtIteratorFila2(iterador_executando);

	if( DeleteAtIteratorFila2(iterador_executando) ) {
		printf("Nao conseguiu retirar elemento de executando\n");
		return 1; // erro
	}
	if ( adicionarNaFilaExecutando(iterador_apto, pnodo)) {
		printf("Erro ao inserir em bloqueado\n");
		return 1; // erro
	}
	return 0;
}

int bloqueado_to_apto(PFILA2 iterador_bloqueado, PFILA2 iterador_apto) {
	FirstFila2(iterador_bloqueado);
	PNODE2 pnodo = GetAtIteratorFila2(iterador_bloqueado);

	if( DeleteAtIteratorFila2(iterador_bloqueado) ) {
		printf("Nao conseguiu retirar elemento de executando\n");
		return 1; // erro
	}
	if ( adicionarNaFilaExecutando(iterador_apto, pnodo)) {
		printf("Erro ao inserir em bloqueado\n");
		return 1; // erro
	}
	return 0;
}

int libera_executando(PFILA2 executando) {
	FirstFila2(executando); // iterador no inicio da fila (só pra garantir)
	if( DeleteAtIteratorFila2(executando) ) {
		printf("Nao conseguiu retirar elemento da fila de executando\n");
		return 1; // erro
	}
	return 0;
}

