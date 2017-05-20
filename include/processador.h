#include "support.h"
#include "cdata.h"

int insertTCB_at_queue(PFILA2 fila, TCB_t* tcb);

TCB_t* criarTCB(int tid, ucontext_t contexto);

int criarProcesso(PFILA2 aptos, TCB_t* tcb);

int adicionarNaFila(PFILA2 fila, PNODE2 pnodo);

int adicionarNaFilaAptos(PFILA2 aptos, PNODE2 pnodo);

// esse métodos estão removendo sempre do início da fila.
int apto_to_executando(PFILA2 apto, PFILA2 executando);

int executando_to_bloqueado(PFILA2 iterador_executando, PFILA2 iterador_bloqueado);

int executando_to_apto(PFILA2 iterador_executando, PFILA2 iterador_apto);

int bloqueado_to_apto(PFILA2 iterador_bloqueado, PFILA2 iterador_apto);

int libera_executando(PFILA2 executando);