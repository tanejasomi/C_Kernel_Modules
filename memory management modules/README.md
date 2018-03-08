#Memory Management Modules

Program to write special version of malloc and free library routines that checks on common heap allocation and usage mistakes.
 
Four major defined functions
1) malloc2(): Allocates memory and record tuples(addr,len) for the memory allocated in the heap.
2) free2(): Performs checks to verify if operation is legal and free allocated memory. 
3) realloc2(): Checks for validations if operation is safe then reallocated memory to point to different pointer.
4) memcheck2(): verify if address range is safe to use.


