#include <pthread.h>

#ifndef __EV_LOOP__
#define __EV_LOOP__

typedef struct task_ task_t;
typedef struct event_loop_ event_loop_t;

typedef void (*event_cbk)(void *);

struct task_ {
	event_cbk cbk;
	void *arg;
	struct task_ *left, *right;
};

typedef enum {
	EV_LOOP_IDLE,
	EV_LOOP_BUSY,
} EV_LOOP_STATE;

struct event_loop_ {
	/* head to the start of the task array */
	struct task_ *task_array_head;

	/*
       Mutex to enforce Mutual exclusion enqueue/dequeue
       operation in task array. Also used to update event loop
       attributes in mutual exclusive way
    */
	pthread_mutex_t ev_loop_mutex;

	/* state of event loop */
	EV_LOOP_STATE ev_loop_state;

	/* CV to suspended event loop thread */
	pthread_cond_t ev_loop_cv;

	/* Event loop thread */
	pthread_t *thread;

	/*
       Current task which event loop thread is executing
       * NULL if event loop is resting in peace
    */
	struct task_ *current_task;
};

void event_loop_init(event_loop_t *el);

void event_loop_run(event_loop_t *el);

task_t *task_create_new_job(event_loop_t *el, event_cbk cbk, void *arg);

#endif /* __EV_LOOP__ */
