#include "include/cdata.h"
#include "include/support.h"

#include <ucontext.h>
#include <signal.h>
#include <stdio.h>

int main(){

	TCB_t t;

	t.tid = 1;

	printf("%d\n", t.tid);


}