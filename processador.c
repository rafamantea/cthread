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

//#include "include/cdata.h"


