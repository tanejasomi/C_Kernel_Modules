#Performance Analysis modules

Purpose:is to understand:
1) Efficiency isssues in writing programs
2) Process of measurement and benchmarking
3) Linux I/O librbay routines are structured
4) Timing system calls

Description:
Given programs measures the time to write large file using two different output routine
1) directly calling the UNIX write system call 
2) using the standard I/O library routine fwrite.

Command to compile:
 gcc -o sysCallPerformance sysCallPerformance.c
execute:
 ./sysCallPerformance 
