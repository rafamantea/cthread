#include "include/cdata.h"
#include "include/support.h"

/*
* 	Implementação das funções da máquina de estados que representa o processador.
*/


/* 
Função genérica para adicionar um elemento TCB na fila.

@params
	# fila: ponteiro para a fila.
	# tamanho_fila: ponteiro para o tamanho da fila.
	# tcb: ponteiro para o elemento TCB a ser adicionado na fila.

@return
	# -1: erro.
	# caso contrário: elemento inserido com sucesso.
*/
int adicionarNaFila(PFILA2* fila, int* tamanho_fila, TCB_t* tcb){
	
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
}

int adicionarNaFilaAptos(PFILA2* aptos, int* tamanho_aptos, TCB_t* tcb) {
	adicionarNaFila(aptos, tamanho_aptos, tcb);
	tcb->state = PROCST_APTO;
}

int adicionarNaFilaBloqueados(PFILA2* bloqueados, int* tamanho_bloqueados, TCB_t* tcb) {
	adicionarNaFila(bloqueados, tamanho_bloqueados, tcb);
	tcb->state = PROCST_BLOQ;
}

int adicionarNaFilaExecutando(PFILA2* executando, int* tamanho_executando, TCB_t* tcb) {
	adicionarNaFila(executando, tamanho_executando, tcb);
	tcb->state = PROCST_EXEC;
}

TCB_t* criarTCB(int tid) {
	TCB_t* tcb = malloc(sizeof(TCB_t));
    tcb->tid = tid;	
    tcb->state = PROCST_CRIACAO;
    tcb->context = current_context;
	
	return tcb;
}
