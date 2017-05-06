#include "include/cdata.h"
#include "include/support.h"
#include "processador.h"

// #include <ucontext.h>

#include <stdio.h>

typedef struct {
	int peso;
	int dados;
} ESPACO;


int main(){

	//TCB_t t;

	//t.tid = 1;

	//printf("%d\n", t.tid);

	// Cria fila do iterador
	FILA2 fila1_APTO;
	PFILA2 iterador1_APTO;
	iterador1_APTO = &fila1_APTO;

	if( CreateFila2( iterador1_APTO ) ) {
		printf("Erro ao criar sFila2\n");
		return 0;
	}

	printf("\n\nsFila2 criada com sucesso\n\n");


	// criar tcb
	TCB_t* tcb = criarTCB(456);

	//NODE2 nodo1;

	//nodo1.node = tcb;

	printf("%d\n", adicionarNaFilaAptos(iterador1_APTO, tcb));

	// colocar no primeiro elemento
	FirstFila2(iterador1_APTO);

	PNODE2 recebedor;
	recebedor = GetAtIteratorFila2(iterador1_APTO);

	printf("%d\n\n", ((TCB_t*)(recebedor->node))->tid);


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
