/**
 * @brief: process.h  process management hearder file
 * @author Irene Huang
 * @author Thomas Reidemeister
 * @date 2011/01/18
 * NOTE: Assuming there are only two user processes in the system
 */

#ifndef _PROCESS_H_
#define _PROCESS_H_

#include "rtx.h"

#define INITIAL_xPSR 0x01000000  // user process initial xPSR value

extern void __rte(void);			// pop exception stack frame
extern void __sys_rte(void);

extern int k_release_processor(void);
#define release_processor() _release_processor((U32)k_release_processor)
//extern int __SVC_0 _release_processor(U32 p_func);
int __SVC_0 _release_processor(U32 p_func);

extern int k_set_process_priority(int, int);
#define set_process_priority(process_ID, priority) _set_process_priority((U32)k_set_process_priority, process_ID, priority)
int __SVC_0 _set_process_priority(U32 p_func, int process_ID, int priority);

extern int k_get_process_priority(int);
#define get_process_priority(process_ID) _get_process_priority((U32)k_get_process_priority, process_ID)
int __SVC_0 _get_process_priority(U32 p_func, int process_ID);


// --------------------------------------------------------
// Data structures
// --------------------------------------------------------

 
typedef struct processEntry {
// process id
  uint32_t pid;	
  
  //Priority of the process 			
  uint32_t priority;
  
  // Size of the process stack 		  
  uint32_t stack_size;
  
  // stack pointer to the start(top) of the process stack  
  uint32_t* start_sp;

  // Where process begins
  uint32_t* process;
        
  //need another variable for i-process (indicates if this is an i-process or not)  
} ProcessEntry;

void init_processe_table(void);

//extern ProcessControlBlock pcb_array[NUM_USR_PROCESSES];

extern ProcessControlBlock * pCurrentProcessPCB;  // always point to the current process

// -----------------------------------------------------
// Public routines
// -----------------------------------------------------
int is_ready_or_new(proc_state_t state );
int is_usr_proc(int process_id);
uint8_t is_i_proc(int proc_id);
ProcessControlBlock * get_process_pointer_from_id(int);
ProcessControlBlock * get_interrupted_process(void);
ListNode* get_node_of_process(int);	

// initialize all procs in the system								
void process_init(void);	    

// pick the pid of the next to run process
ProcessControlBlock* scheduler(ProcessControlBlock* pOldPCB, ProcessControlBlock* pNewPCB);				
int k_release_processor(void);		// kernel release_process API
// Switch contexts from the passed-in PCB to the pCurrentPCB
void context_switch(ProcessControlBlock*, ProcessControlBlock*);

int has_blocked_processes(void); // check if there are blocked processes
void block_current_process(void); // Put current process in a blocking state, as well as enqueue in the blocked queue


ProcessControlBlock* getBlockedProcess(void); //Gets the highest priority blocked process
ProcessControlBlock* getRunningProcess(void); //Gets a running process from all processes array

// ------------------------------------------------------
// External routines
// ------------------------------------------------------

// User Processes
extern void test_process_1 (void);
extern void test_process_2 (void);
extern void test_process_3 (void);
extern void test_process_4 (void);
extern void test_process_5 (void);
extern void test_process_6 (void);

extern void nullProc(void);				// null process

#endif // ! _PROCESS_H_
