/**
 * @brief:  main_svc.c, demonstrate svc as a gateway to os functions
 * @author: Yiqing Huang
 * @date: 2012/01/08
 * NOTE: standard C library is not allowed in the final kernel code
 *       it is OK if you only use the C library for debugging purpose 
 *       during the development/prototyping phase
 */

#include <LPC17xx.h>
#include <system_LPC17xx.h>
#ifdef DEBUG_0
#include <stdio.h>
#else
#define NULL 0
#endif // DEBUG_0
#include "uart_polling.h"
#include "rtx.h"
#include "utils.h"

extern int NUM_PROCESSES;
extern void process_init(void);
extern int get_process_priority(int);
extern int set_process_priority(int, int);

void run_memory_tests(){

	int testCases = 100;
	int currentTestCase = 0;
	int tmpCounter = 0;
	int testValue1 = 6;
	int testValue2 = 57;
	int * pTestPointer1 = 0;
	int * pTestPointer2 = 0;

	int numberOfPointersYouCanPutInOneBlockOfMemory = MEMORY_BLOCK_SIZE / sizeof(int);

	//Allocate one block of memory
	pTestPointer1 = request_memory_block();
	assert((int)pTestPointer1, "Request memory returned null");
	*pTestPointer1 = testValue1;
	assert((*pTestPointer1) == testValue1, "the first memory test failed.");

	//Allocate a second block of memory
	pTestPointer2 = request_memory_block();
	assert((int)pTestPointer2, "Request memory returned null");
	*pTestPointer2 = testValue2;
	assert((*pTestPointer2) == testValue2, "the second memory test failed.");

	// Make sure this memory block is clean, even thought I think it already is
	for(tmpCounter = 0; tmpCounter < numberOfPointersYouCanPutInOneBlockOfMemory; tmpCounter++){
		pTestPointer1[tmpCounter] = 0;
	}

	for(currentTestCase = 0; currentTestCase < testCases; currentTestCase++){
		// Randomly pick an int that we will consider to be a pointer to another memory block
		int currentMemoryBlockIndex = get_random() % numberOfPointersYouCanPutInOneBlockOfMemory;
		//  Treat the int at that location as a pointer to memory somewhere
		int ** pointerToCurrentMemoryBlockPointer = (int**)&(pTestPointer1[currentMemoryBlockIndex]);
		//  If that address points to nothing, allocate new memory and put the pointer there
		if(*pointerToCurrentMemoryBlockPointer == (int *)0){
			*pointerToCurrentMemoryBlockPointer = (int *)request_memory_block();
			//uart0_put_string("Test case ");print_unsigned_integer(currentTestCase);	uart0_put_string(" of "); print_unsigned_integer(testCases);uart0_put_string(": ");
			//uart0_put_string("Allocated memory block: ");print_unsigned_integer((int)(*pointerToCurrentMemoryBlockPointer));uart0_put_string("\n\r");
			for(tmpCounter = 0; tmpCounter < numberOfPointersYouCanPutInOneBlockOfMemory; tmpCounter++){
				// Fill this new block of memory with the ints that are the address of the block itself plus the offset(tmpCounter) of the that int 
				(*pointerToCurrentMemoryBlockPointer)[tmpCounter] = ((int)(*pointerToCurrentMemoryBlockPointer)) + tmpCounter;
			}		
		}else{
			//  This block does point to something, verify that the data there is in the expected format, then delete it
			for(tmpCounter = 0; tmpCounter < numberOfPointersYouCanPutInOneBlockOfMemory; tmpCounter++){
				// Is what we put there still the same?
				assert((*pointerToCurrentMemoryBlockPointer)[tmpCounter] == ((int)(*pointerToCurrentMemoryBlockPointer)) + tmpCounter,"Memory test failure: block failed sanity check.");
			}
			//  Delete this block
			//uart0_put_string("Test case ");print_unsigned_integer(currentTestCase);	uart0_put_string(" of "); print_unsigned_integer(testCases);uart0_put_string(": ");
			//uart0_put_string("Memory block ");print_unsigned_integer((int)(*pointerToCurrentMemoryBlockPointer));uart0_put_string(" looks OK, releasing.\n\r");
			release_memory_block(*pointerToCurrentMemoryBlockPointer);
			*pointerToCurrentMemoryBlockPointer = 0;
		}
	}

	uart0_put_string("Memory test passed. \n\r");
}

void run_priority_tests() {
	int procIndex;

	for(procIndex = 0; procIndex < NUM_PROCESSES; ++procIndex) {
		if(procIndex == 0) {
		  	assert(get_process_priority(procIndex) == 4, "Null process priority is invalid. Test failed.");
		} else {
	 		assert(get_process_priority(procIndex) == procIndex - 1, "Process priority is invalid. Test failed.");
		}
	}

	for(procIndex = 1; procIndex < NUM_PROCESSES - 1; ++procIndex) {
		assert(set_process_priority(procIndex, 3) == 0 && get_process_priority(procIndex) == 3, "Could not set process priority. Test failed.");
	}
	
	uart0_put_string("Priority test passed. \n\r");
}

void print_some_numbers(){
	int i;

	for(i = 0; i < 10; i++){
		print_unsigned_integer(get_random() % 200);
		uart0_put_string("\n\r");
	}

	for(i = 0; i < 10; i++){
		print_signed_integer((get_random() % 200) * -1);
		uart0_put_string("\n\r");
	}

	uart0_put_string("Print stuff test passed. \n\r");
}

int main() 
{
	 
	volatile unsigned int ret_val = 1234;
	
	SystemInit();	// initialize the system

	// Disable interrupt requests
	__disable_irq();

	// Initialize UART output
	uart0_init();   

	// Initialize stack and PCB for processes
	process_init();
	// Enable interrupt requests
	__enable_irq();
	
	// transit to unprivileged level, default MSP is used
	__set_CONTROL(__get_CONTROL() | BIT(0));  

	run_memory_tests();
    print_some_numbers();
	run_priority_tests();

	ret_val = release_processor();
	uart0_put_string("\nShould never reach here!!!\n\r");
	
	return -1;	
}
