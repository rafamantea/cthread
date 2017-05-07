#include "include/support.h"
#include "include/cdata.h"

TCB_t* criarTCB(int tid);

int criarProcesso(PFILA2 aptos, TCB_t* tcb);

int adicionarNaFila(PFILA2 fila, PNODE2 pnodo);

int adicionarNaFilaAptos(PFILA2 aptos, PNODE2 pnodo);

// esse métodos estão removendo sempre do início da fila.
int apto_to_executando(PFILA2 apto, PFILA2 executando);

int executando_to_bloqueado(PFILA2 iterador_executando, PFILA2 iterador_bloqueado);

int executando_to_apto(PFILA2 iterador_executando, PFILA2 iterador_apto);

int bloqueado_to_apto(PFILA2 iterador_bloqueado, PFILA2 iterador_apto);

int libera_executando(PFILA2 executando);