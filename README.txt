This project is the real-time operating system, developed by James Hudon, Greta Cutulenco, Robert Elder and Artem Pasyechnyk for the SE-350 course at the University of Waterloo.

The operating system was developed for LPC1768 based MCB1700 microcontroller boards,
using the Keil uVision application as an IDE/Simulator for debugging purposes.

The RTX provides a basic multiprogramming environment with 5 priority levels, preemption,
simple memory management, message-based inter-process communication, a basic timing service, system console I/O and debugging support. Our RTX is suitable for embedded computers which operate in real time. A cooperative, non-malicious software environment is assumed. Applications and non-kernel RTX processes execute in the unprivileged level of LPC1768. The RTX kernel will execute in the privileged level. For both kernel and non-kernel code, the MSP (Main Stack Pointer) is used to track execution (as opposed to the Process Stack Pointer (PSP)).



The information of the IDE this was developed on is as follows.

IDE-Version:
Keil (mu)Vision V4.23.00.0
Copyright (C) 2011 ARM Ltd and ARM Germany GmbH. All rights reserved.

Tool Version Numbers:
Toolchain:        MDK-Lite  Version: 4.23
Toolchain Path:    C:\Keil\ARM\BIN40
C Compiler:         Armcc.Exe       V4.1.0.894 [Evaluation]
Assembler:          Armasm.Exe       V4.1.0.894 [Evaluation]
Linker/Locator:     ArmLink.Exe       V4.1.0.894 [Evaluation]
Librarian:             ArmAr.Exe       V4.1.0.894 [Evaluation]
Hex Converter:      FromElf.Exe       V4.1.0.894 [Evaluation]
CPU DLL:               SARMCM3.DLL       V4.23
Dialog DLL:         DARMP1.DLL       V1.22.0.6
Target DLL:             UL2CM3.DLL       V1.95
Dialog DLL:         TARMP1.DLL       V1.22.0.6

Documentation about how to configure the editor to run this code can be found in the files from learn folder.
