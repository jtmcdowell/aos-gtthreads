/**********************************************************************
gtthread_sched.c.  

This file contains the implementation of the scheduling subset of the
gtthreads library.  A simple round-robin queue should be used.
 **********************************************************************/
/*
  Include as needed
*/

#include "gtthread.h"
#include <ucontext.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/time.h>

/* 
   Students should define global variables and helper functions as
   they see fit.
 */

static steque_t thread_queue;
static steque_t scheduler_queue;
//ucontext_t uctx_currentContext;
static long int TID = 0; // thread ID's

typedef struct gtthread_init_t {
gtthread_t threadID;
ucontext_t uctx_context;
void *retval; // return value from thread
int retcode; // return code from thread
char cancelreq; // cancel request from another thread
char completed; // flag indicating if this is completed or not
steque_t holding_queue; // queue for threads waiting to join mainThread
} gtthread_init_t;



/*
  The gtthread_init() function does not have a corresponding pthread equivalent.
  It must be called from the main thread before any other GTThreads
  functions are called. It allows the caller to specify the scheduling
  period (quantum in micro second), and may also perform any other
  necessary initialization.  If period is zero, then thread switching should
  occur only on calls to gtthread_yield().

  Recall that the initial thread of the program (i.e. the one running
  main() ) is a thread like any other. It should have a
  gtthread_t that clients can retrieve by calling gtthread_self()
  from the initial thread, and they should be able to specify it as an
  argument to other GTThreads functions. The only difference in the
  initial thread is how it behaves when it executes a return
  instruction. You can find details on this difference in the man page
  for pthread_create.
 */
void gtthread_init(long period){
  /* Initialize the main thread,
  the scheduler queues and context.
  Establish main thread as the initial
  thread. */
  gtthread_init_t *mainThread;
  if ((mainThread = malloc(sizeof(gtthread_init_t))) != NULL){
    steque_init(&thread_queue);
    steque_init(&scheduler_queue);
    mainThread->threadID = TID++;
    mainThread->cancelreq = 0;
    mainThread->completed = 0;
    steque_init(&mainThread->holding_queue);
    getcontext(&mainThread->uctx_context);
    mainThread->uctx_context.uc_stack.ss_sp = (char *) malloc(SIGSTKSZ);
    mainThread->uctx_context.uc_stack.ss_size = SIGSTKSZ;
    steque_enqueue(&thread_queue, mainThread);
    steque_enqueue(&scheduler_queue, mainThread);
    printf("mainThread created with ID = %ld\n", TID);
    //int value = steque_isempty(&thread_queue);
    //printf("Is thread_queue empty?  %d\n", value);
  }
}


/*
  The gtthread_create() function mirrors the pthread_create() function,
  only default attributes are always assumed.
 */
int gtthread_create(gtthread_t *thread,
        void *(*start_routine)(void *),
        void *arg){
  gtthread_init_t *newThread;
  if ((newThread = malloc(sizeof(gtthread_init_t))) != NULL){
    newThread->threadID = TID++;
    *thread = newThread->threadID;
    newThread->cancelreq = 0;
    newThread->completed = 0;
    steque_init(&newThread->holding_queue);
    getcontext(&newThread->uctx_context);
    newThread->uctx_context.uc_stack.ss_sp = (char *) malloc(SIGSTKSZ);
    newThread->uctx_context.uc_stack.ss_size = SIGSTKSZ;
    //self = (gtthread_init_t *) steque_front(&scheduler_queue);
    newThread->uctx_context.uc_link = &self->context;
    if (getcontext(&uctx_context) == -1 ){
      perror("getcontext");
      exit(EXIT_FAILURE);
    }
    makecontext(&newThread->uctx_context, (void (*)(void)));
    steque_enqueue(&thread_queue, newThread);
    steque_enqueue(&scheduler_queue, newThread);
  }
}


/*
  The gtthread_join() function is analogous to pthread_join.
  All gtthreads are joinable.
 */
int gtthread_join(gtthread_t thread, void **status){


}

/*
  The gtthread_exit() function is analogous to pthread_exit.
 */
void gtthread_exit(void* retval){



}


/*
  The gtthread_yield() function is analogous to pthread_yield, causing
  the calling thread to relinquish the cpu and place itself at the
  back of the schedule queue.
 */
void gtthread_yield(void){


}

/*
  The gtthread_equal() function is analogous to pthread_equal,
  returning non-zero if the threads are the same and zero otherwise.
 */
int  gtthread_equal(gtthread_t t1, gtthread_t t2){


}

/*
  The gtthread_cancel() function is analogous to pthread_cancel,
  allowing one thread to terminate another asynchronously.
 */
int  gtthread_cancel(gtthread_t thread){

}

/*
  Returns calling thread.
 */
gtthread_t gtthread_self(void){

}
