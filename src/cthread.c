#include "../include/support.h"
#include "../include/cdata.h"
#include "../include/cthread.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ucontext.h>

#define VERY_HIGH 0
#define HIGH 1
#define MEDIUM 2
#define LOW 3

//Filas 
FILA2 ready_very_high;
FILA2 ready_high;
FILA2 ready_medium;
FILA2 ready_low;

FILA2 blocked;


//Iteradores das filas
PFILA2 it_ready_very_high;
PFILA2 it_ready_high;
PFILA2 it_ready_medium;
PFILA2 it_ready_low;

PFILA2 it_blocked;

//Contador de threads para TID
tid_count = 0;

TCB_t *current_thread_tcb;
u_context *current_thread_context;
u_context *final_context;

/*
*
*		INICIALIZAÇÕES
**************************************
*
*/

void initialize() {
	init_queues();
	init_final_context();
	init_current_thread_context();
	init_main_thread_context();
	
}

int init_queues() {
	it_ready_very_high = &ready_very_high;
	it_ready_high = &ready_high;
	it_ready_medium = &ready_medium;
	it_ready_low = &ready_low;
	it_blocked = &blocked;
	
	if( CreateFila2( it_ready_very_high ) ) {
		printf("Erro ao criar fila apto - VERY HIGH\n");
		return 1;
	}	
	if( CreateFila2( it_ready_high ) ) {
		printf("Erro ao criar fila apto - HIGH\n");
		return 1;
	}	
	if( CreateFila2( it_ready_medium ) ) {
		printf("Erro ao criar fila apto - MEDIUM\n");
		return 1;
	}	
	if( CreateFila2( it_ready_low ) ) {
		printf("Erro ao criar fila apto - LOW\n");
		return 1;
	}
	if( CreateFila2( it_blocked ) ) {
		printf("Erro ao criar fila bloqueados\n");
		return 1;
	}
	
	return 0;
}

void init_current_thread_context() {
    char stack[SIGSTKSZ];
	getcontext(&current_thread_context);
    current_thread_context.uc_link = &final_context;
    current_thread_context.uc_stack.ss_sp = stack;
    current_thread_context.uc_stack.ss_size = sizeof(stack);
}

void init_main_thread_context() {	
	current_thread_context = (TCB_t*)criarTCB(0, current_thread_context);
}

void init_final_context() {
    char stack[SIGSTKSZ];
	getcontext(&final_context);
    final_context.uc_stack.ss_sp = stack;
    final_context.uc_stack.ss_size = sizeof(stack);
    makecontext(&final_context, (void (*)(void))finish_callback, 0);
}

/*
*
*		PRIMITIVAS CTHREAD
************************************
*
*/

int ccreate (void *(*start)(void *), void *arg, int prio) {
    char *stack = malloc(sizeof(char) * SIGSTKSZ);
    ucontext_t *context = malloc(sizeof(ucontext_t));
    getcontext(context);

    context->uc_link = &final_context;
    context->uc_stack.ss_sp = stack;
    context->uc_stack.ss_size = SIGSTKSZ;

    TCB_t *tcb = (TCB_t*)criarTCB(++tid_count, context);
	tcb->ticket = prio;

    makecontext(&tcb->context, (void (*)(void)) start, 1, arg);
	add_ready_by_priority(tcb, prio);

    return tcb->tid;
}

int csetprio(int tid, int prio) {
	
}

int csignal() {
	
}

int cyield(void) {
	
}

int cjoin(int tid) {
	
}

int csem_init (csem_t *sem, int count) {
	
}

int cwait (csem_t *sem) {
	
}

int csignal (csem_t *sem) {
	
}

int cidentify (char *name, int size){
    if(name == NULL){
        name = malloc(sizeof(char) * size);
    }

    if(size <= 0){
        return -1;
    }

    char students[] = "Rafael Pinheiro Amantea - 228433\n Mauricio Carmelo - xxxxxx\n";
    int i = 0;

    while (i < size && i < sizeof(students)){
        name[i] = students[i];
        i++;
    }

    return 0;
}


/*
*
*		AUXILIARES
************************************
*
*/

int add_ready_by_priority(int prio, TCB_t* tcb) {
	switch(prio) {
		case VERY_HIGH:
			return insertTCB_at_queue(ready_very_high, tcb);
		case HIGH:
			return insertTCB_at_queue(ready_high, tcb);
		case MEDIUM:
			return insertTCB_at_queue(ready_medium, tcb);
		case LOW:
			return insertTCB_at_queue(ready_low, tcb);
		default:
			return 1;
	}
}

int queue_has_tcb(PFILA2 queue, int tid){
    TCB_t* tcb;

    if (queue == NULL){
        return 1;
    }
    if(FirstFila2(queue) == 0){

        tcb = (TCB_t*)GetAtIteratorFila2(queue);
        while(tcb != NULL && tcb->tid != tid){
            if(NextFila2(queue) == 0){
                tcb = (TCB_t*)GetAtIteratorFila2(queue);
                if (tcb == NULL){
                    return 1;
                }
            }
            else{
                return 1;
            }
        }
        if (tcb->tid == tid){
            return 0;
        }
    }
    return 1;
}

TCB_t * get_tcb(PFILA2 queue, int tid) {
	TCB_t* tcb;

	if(FirstFila2(queue) == 0){
		tcb = (TCB_t*)GetAtIteratorFila2(queue);
		while(tcb != NULL && tcb->tid != tid){
			if(NextFila2(queue) == 0){
				tcb = (TCB_t*)GetAtIteratorFila2(queue);
			}
		}
		if (tcb->tid == tid){
			return tcb;
		}
	}
	return NULL;
}

TCB_t * get_tcb_by_tid(int tid) {
	if(queue_has_tcb(ready_very_high, tid) {
		return get_tcb(ready_very_high, tid);
	
	} else if(queue_has_tcb(ready_high, tid)) {
		return get_tcb(ready_high, tid);
		
	} else if(queue_has_tcb(ready_medium, tid)) {
		return get_tcb(ready_medium, tid);
		
	} else if(queue_has_tcb(ready_low, tid)) {
		return get_tcb(ready_low, tid);
		
	} else if(queue_has_tcb(blocked, tid)) {
		return get_tcb(blocked, tid);
	}
	
	return NULL;
}

void finish_callback() {
	
}
