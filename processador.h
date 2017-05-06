#include "include/support.h"
#include "include/cdata.h"

TCB_t* criarTCB(int tid);

int criarProcesso(PFILA2 aptos, TCB_t* tcb);

int adicionarNaFila(PFILA2 fila, PNODE2 pnodo);

int adicionarNaFilaAptos(PFILA2 aptos, PNODE2 pnodo);

int apto_to_executar(PFILA2 apto, PFILA2 executando);

int libera_executando(PFILA2 executando);