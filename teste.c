
#include <stdio.h>
#include <stdlib.h>
#include "include/support.h"
#include "include/cdata.h"
#include "processador.h"
#include <ucontext.h>

typedef struct {
	int peso;
	int dados;
} ESPACO;


int main(){

	ucontext_t contexto;
	//TCB_t t;

	//t.tid = 1;

	//printf("%d\n", t.tid);

	// Cria fila do iterador
	//FILA2 fila1_APTO;
	//FILA2 fila1_EXECUTANDO;
	FILA2 fila;

	//PFILA2 iterador1_APTO;
	//PFILA2 iterador1_EXECUTANDO;
	PFILA2 iterador_fila;

	//iterador1_APTO = &fila1_APTO;
	//iterador1_EXECUTANDO = &fila1_EXECUTANDO;
	iterador_fila = &fila;

	/*if( CreateFila2( iterador1_APTO ) ) {
		printf("Erro ao criar sFila2\n");
		return 0;
	}
	if( CreateFila2( iterador1_EXECUTANDO ) ) {
		printf("Erro ao criar sFila2\n");
		return 0;
	}*/
	if( CreateFila2( iterador_fila ) ) {
		printf("Erro ao criar sFila2\n");
		return 0;
	}

	// criar tcb
	TCB_t* tcb = criarTCB(1, contexto);
	insertTCB_at_queue(iterador_fila, tcb);
	tcb = criarTCB(2, contexto);
	insertTCB_at_queue(iterador_fila, tcb);
	tcb = criarTCB(3, contexto);
	insertTCB_at_queue(iterador_fila, tcb);
	tcb = criarTCB(4, contexto);
	insertTCB_at_queue(iterador_fila, tcb);

	// criar nodo
	//NODE2 nodo1;
	//nodo1.node = tcb;

	//printf("%d\n", adicionarNaFilaAptos(iterador1_APTO, &nodo1));
	// colocar no primeiro elemento
	FirstFila2(iterador_fila);
	

	//PNODE2 nodo_atual;
	//nodo_atual = GetAtIteratorFila2(iterador_fila);	

	/*while( nodo_atual != NULL ) {
		printf("%d\n\n", ((TCB_t*)(nodo_atual->node))->tid);
		DeleteAtIteratorFila2(iterador_fila);
		FirstFila2(iterador_fila);
		nodo_atual = GetAtIteratorFila2(iterador_fila);		
	}*/
	NextFila2(iterador_fila);
	NextFila2(iterador_fila);
	NextFila2(iterador_fila);
	//NextFila2(iterador_fila);


	if(NextFila2(iterador_fila) == -3)
		printf("Fim da fila!\n");
	

	//apto_to_executar(iterador1_APTO, iterador1_EXECUTANDO);

	//FirstFila2(iterador1_EXECUTANDO);
	//recebedor = GetAtIteratorFila2(iterador1_EXECUTANDO);
	//printf("%d\n\n", ((TCB_t*)(recebedor->node))->tid);

	//libera_executando(iterador1_EXECUTANDO);











	//PNODE2 recebedor;
	//recebedor = GetAtIteratorFila2(iterador1_APTO);


	// Cria três estruturas
	/*ESPACO espaco1;
	ESPACO espaco2;
	ESPACO espaco3;

	espaco1.peso = 1;
	espaco2.peso = 2;
	espaco3.peso = 3;

	// Cria tres nodos
	NODE2 nodo1;
	nodo1.node = &espaco1;

	NODE2 nodo2;
	nodo2.node = &espaco2;

	NODE2 nodo3;
	nodo3.node = &espaco3;	
	

	// coloca nodo na fila
	printf("%d\n", AppendFila2(iterador1_APTO, &nodo1));

	printf("%d\n", AppendFila2(iterador1_APTO, &nodo2));

	printf("%d\n", AppendFila2(iterador1_APTO, &nodo3));


	// colocar no primeiro elemento
	FirstFila2(iterador1_APTO);

	// pegar e endereco do elemento
	PNODE2 recebedor;
	recebedor = GetAtIteratorFila2(iterador1_APTO);

	printf("%d\n\n", ((ESPACO*)(recebedor->node))->peso);

	LastFila2(iterador1_APTO); // seta iterador para ultimo da fila
	recebedor = GetAtIteratorFila2(iterador1_APTO); // pega endereco do nodo

	printf("%d\n\n", ((ESPACO*)(recebedor->node))->peso); // imprime peso

	DeleteAtIteratorFila2(iterador1_APTO); // deleta elemento


	LastFila2(iterador1_APTO); // seta iterador para ultimo da fila
	recebedor = GetAtIteratorFila2(iterador1_APTO); // pega endereco do nodo
	printf("%d\n\n", ((ESPACO*)(recebedor->node))->peso);*/ // imprime peso


	//printf("Resultado da setagem: %d\n", FirstFila2(iterador1_APTO));
	//PNODE2 nodo_retorno = GetAtIteratorFila2(iterador1_APTO);
	//printf("valor armazenado: %d\n", nodo_retorno->node );




}
