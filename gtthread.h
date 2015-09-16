#ifndef GTTHREAD_H
#define GTTHREAD_H

#include "steque.h"
#include <ucontext.h>

/* Define gtthread_t and gtthread_mutex_t types here */
typedef unsigned long int gtthread_t;
typedef struct gtthread{
	gtthread_t threadID;
	ucontext_t uctx_threadContext;
	unsigned int running;
	unsigned int blocked;
	unsigned int completed;
	unsigned int exited;
	void* exitval;
	struct gtthread *next;
}gtthread;

gtthread *mainThread, *currentThread, *nextThread, *Front, *Rear;

typedef struct gtthread_mutex_t{
	gtthread_t owner;
	unsigned int lock;
	unsigned int id;
}gtthread_mutex_t;

void gtthread_init(long period);
int  gtthread_create(gtthread_t *thread,
                     void *(*start_routine)(void *),
                     void *arg);
int  gtthread_join(gtthread_t thread, void **status);
void gtthread_exit(void *retval);
void gtthread_yield(void);
int  gtthread_equal(gtthread_t t1, gtthread_t t2);
int  gtthread_cancel(gtthread_t thread);
gtthread_t gtthread_self(void);


int  gtthread_mutex_init(gtthread_mutex_t *mutex);
int  gtthread_mutex_lock(gtthread_mutex_t *mutex);
int  gtthread_mutex_unlock(gtthread_mutex_t *mutex);
int  gtthread_mutex_destroy(gtthread_mutex_t *mutex);
#endif
