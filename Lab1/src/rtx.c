/* @brief: rtx.c kernel API implementations, this is a skeleton only
 * @author: Yiqing Huang
 * @date: 2012/01/08
 */

#include "rtx.h"
#include "utils.h"

//Variable declarations 


LinkedList ready_queue[NUM_PRIORITIES];
LinkedList blocked_memory_queue[NUM_PRIORITIES];
LinkedList blocked_receive_queue[NUM_PRIORITIES];

unsigned int free_mem = (unsigned int) &Image$$RW_IRAM1$$ZI$$Limit;


// -------------------------------------------------------------------------
//           Helpers
// -------------------------------------------------------------------------


/*void enqueue(QueueHead* qHead, ProcessControlBlock* pcb) {
	ProcessControlBlock* oldTail = (*qHead).tail;
	(*qHead).tail = pcb;
	(*pcb).next = NULL; // TODO what if pcb is NULL?


	if (oldTail != NULL) {
		(*oldTail).next = pcb;
	}

	if ((*qHead).head == NULL) {
	 	(*qHead).head = pcb;
	}
}*/

void enqueue_ll(LinkedList* listHead, ListNode* node) {
	ListNode* oldTail = (*listHead).tail;
	(*listHead).tail = node;
	(*node).next = NULL; // TODO what if pcb is NULL?

	if (oldTail != NULL) {
		(*oldTail).next = node;
	}

	if ((*listHead).head == NULL) {
	 	(*listHead).head = node;
	}
}

/*ProcessControlBlock* dequeue(QueueHead* qHead) {
	ProcessControlBlock* firstIn = (*qHead).head;
	if (firstIn == NULL) return NULL;
	
	(*qHead).head = (*firstIn).next;
	(*firstIn).next = NULL;

	if ((*qHead).head == NULL) {
	 	(*qHead).tail = NULL;
	}

	return firstIn;
}*/

ListNode* dequeue_ll(LinkedList* qHead) {
	ListNode* firstIn = (*qHead).head;
	if (firstIn == NULL) return NULL;
	
	(*qHead).head = (*firstIn).next;
	(*firstIn).next = NULL;

	if ((*qHead).head == NULL) {
	 	(*qHead).tail = NULL;
	}

	return firstIn;
}


ListNode* remove_node(LinkedList* qHead, void* node_data) {
	ListNode* curr = (*qHead).head;	

	if (curr->data == node_data) {
		if (curr->next == NULL) {
		 	qHead->tail = NULL;
		}
		qHead->head = curr->next;
		return curr;
	}

	while (curr != NULL) {
		if (curr->next->data == node_data) { 
			ListNode *return_node;
			if (node_data == qHead->tail->data) {
				assert(qHead->tail->next == NULL, "ERROR: Tail next is not null.");
				qHead->tail = curr;
			}
			return_node = curr->next;
			curr->next = curr->next->next;
			return return_node;
		}
		curr = curr->next;
	}
}

// --------------------------------------------------------------------------

