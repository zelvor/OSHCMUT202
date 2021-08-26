
#include <stdlib.h>
#include "queue.h"
#include <pthread.h>

/* Remember to initilize the queue before using it */
void initialize_queue(struct pqueue_t * q) {
	q->head = q->tail = NULL;
	pthread_mutex_init(&q->lock, NULL);
}

/* Return non-zero if the queue is empty */
int empty(struct pqueue_t * q) {
	return (q->head == NULL);
}

/* Get PCB of a process from the queue (q).
 * Return NULL if the queue is empty */
struct pcb_t * de_queue(struct pqueue_t * q) {
	struct pcb_t * proc = NULL;
	// TODO: return q->head->data and remember to update the queue's head
	// and tail if necessary. Remember to use 'lock' to avoid race
	// condition
	
	// YOUR CODE HERE

	static pthread_mutex_t dequeue = PTHREAD_MUTEX_INITIALIZER;

  	// pthread_mutex_lock(&dequeue);

  	if (q->head == NULL || q->tail == NULL)
  	  return proc;
	
	  proc = q->head->data;
	  struct qitem_t *tmp = q->head;
	
	  q->head = q->head->next;
	  if (q->head == NULL)
	    q->tail = NULL;
	
	  free(tmp);
	  tmp = NULL;

	  // pthread_mutex_unlock(&dequeue);
	
	return proc;
}

/* Put PCB of a process to the queue. */
void en_queue(struct pqueue_t * q, struct pcb_t * proc) {
	// TODO: Update q->tail.
	// Remember to use 'lock' to avoid race condition
	
	// YOUR CODE HERE

	static pthread_mutex_t enqueue = PTHREAD_MUTEX_INITIALIZER;

	  // pthread_mutex_lock(&enqueue);

 	 struct qitem_t *qitem = (struct qitem_t *)malloc(sizeof(struct qitem_t));
  	 qitem->data = proc;
	  qitem->next = NULL;
	
	  if (q->head == NULL || q->tail == NULL)
	    q->head = q->tail = qitem;
	  else
	  {
	    q->tail->next = qitem;
	    q->tail = qitem;
	  }
	
	  // pthread_mutex_unlock(&enqueue);
	
}


