#ifndef _SYSTEM_PROC_H_
#define _SYSTEM_PROC_H_

#define	MAX_NUMBER_OF_REGISTERABLE_COMMANDS             10
#define	MAX_COMMAND_LENGTH                              500

#include "rtx.h"

int get_seconds_from_formatted_time(char *);
void register_command(char *, int);
void unregister_all_commands(void);

ProcessControlBlock* get_waiting_sys_proc(void);

//-SYS PROCS-
void keyboard_command_decoder(void);
void crt_display(void);
//----------

void init_sys_procs(void);
ProcessControlBlock* get_kcd_pcb(void);
ProcessControlBlock* get_crt_pcb(void);
ProcessControlBlock* get_new_sys_proc(void);

#endif 
