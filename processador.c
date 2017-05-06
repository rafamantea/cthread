/*
* 	Implementação das funções da máquina de estados que representa o processador.
*/

// função para definir evento

// funções para cada evento

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
#include <stdio.h>
#include <stdlib.h>

/*int adicionarNaFila(PFILA2* fila, int* tamanho_fila, TCB_t* tcb){
	
    if (fila == NULL){
        fila = malloc(sizeof(TCB_t));
        tamanho_fila++;

        int inicializar_fila = CreateFila2(fila);
		
        if (inicializar_fila == -1){
            perror("Erro ao inicializar fila!\n");
			
			return -1;
        }
		
        return AppendFila2(fila, tcb);
    }
    else{
        fila = realloc(fila, sizeof(TCB_t)*(tamanho_fila+1));
        tamanho_fila++;
		
        return AppendFila2(fila, tcb);
    }
}*/

int criarProcesso(PFILA2 aptos, TCB_t* tcb) {

	PNODE2 pnodo = malloc(sizeof(NODE2));	// alocar espaço para um novo nodo na fila
	pnodo->node = tcb;

	adicionarNaFilaAptos(aptos, pnodo);

}

TCB_t* criarTCB(int tid) {
	TCB_t* tcb = malloc(sizeof(TCB_t));
    tcb->tid = tid;	
    tcb->state = PROCST_CRIACAO;
	
	return tcb;
}

int adicionarNaFila(PFILA2 fila, PNODE2 pnodo) {

	//PNODE2 pnodo = malloc(sizeof(NODE2));	// alocar espaço para um novo nodo na fila
	//pnodo->node = tcb;

	/*
	*	Como um novo processo é colocado na fila de aptos? Isso depende do escalonador 
	*/
	return AppendFila2(fila, pnodo);
}

int adicionarNaFilaAptos(PFILA2 aptos, PNODE2 pnodo) {
	((TCB_t*)(pnodo->node))->state = PROCST_APTO;
	return adicionarNaFila(aptos, pnodo);
}

/*int adicionarNaFilaBloqueados(PFILA2* bloqueados, int* tamanho_bloqueados, TCB_t* tcb) {
	adicionarNaFila(bloqueados, tamanho_bloqueados, tcb);
	tcb->state = PROCST_BLOQ;
}
*/
int adicionarNaFilaExecutando(PFILA2 executando, PNODE2 pnodo) {
	((TCB_t*)(pnodo->node))->state = PROCST_EXEC;
	return adicionarNaFila(executando, pnodo);
}

int apto_to_executar(PFILA2 apto, PFILA2 executando) {
	FirstFila2(apto); // iterador no inicio da fila
	PNODE2 pnodo = GetAtIteratorFila2(apto);
	if( DeleteAtIteratorFila2(apto) ) {
		printf("Nao conseguiu retirar elemento da fila de aptos\n");
		return 1; // erro
	}
	if ( adicionarNaFilaExecutando(executando, pnodo)) {
		printf("Erro ao inserir em executando\n");
		return 1;
	}
	return 0;
}
