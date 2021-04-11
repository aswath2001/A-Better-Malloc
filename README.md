# A-Better-Malloc
Project to understand how memory allocator works

By 19PT04 and 19PT37

In this project, we will be implementing a memory allocator for the heap of a user-level process. Our functions will be similar to those provided by malloc() and free().

This memory allocator is usually provided as part of a standard library and is not part of the OS. To be clear, the memory allocator operates entirely within the address space of a single process and knows nothing about which physical pages have been allocated to this process or the mapping from logical addresses to physical addresses.

. First, when requesting memory from the OS, we must use mmap and we must call it only once

Our implementations of Mem_Alloc(int size) and Mem_Free(void *ptr) are identical, except the ptr passed to Mem_Free does not have to have been previously returned by Mem_Alloc; instead, ptr can point to any valid range of memory returned by Mem_Alloc.
For example, the following code sequence is valid with Our allocator, but not with the traditional malloc and free:
int *ptr;

// The returned memory object is between ptr and ptr+49
if ((ptr = (int *)Mem_Alloc(50 * sizeof(int))) == NULL) exit(1);

// Could replace 30 with any value from 0 to 49..
Mem_Free(ptr+30);  

We define each of these routines inside a header function mem.h.

int Mem_Init(int sizeOfRegion): Mem_Init is called one time by a process using our routines. sizeOfRegion is the number of bytes that we should request from the OS using mmap. 
void *Mem_Alloc(int size): Mem_Alloc() is similar to the library function malloc(). Mem_Alloc takes as input the size in bytes of the object to be allocated and returns a pointer to the start of that object. The function returns NULL if there is not enough free space within sizeOfRegion allocated by Mem_Init to satisfy this request.
int Mem_Free(void *ptr): Mem_Free frees the memory object that ptr falls within, according to the rules described above. Just like with the standard free(), if ptr is NULL, then no operation is performed. The function returns 0 on success and -1 if ptr to does not fall within a currently allocated object (note that this includes the case where the object was already freed with Mem_Free).
int Mem_IsValid(void *ptr): This function returns 1 if ptr falls within a currently allocated object and 0 if it does not.We may find this function useful when debugging your memory allocator.
int Mem_GetSize(void *ptr): If ptr falls within the range of a currently allocated object, then this function returns the size in bytes of that object; otherwise, the function returns -1. We may find this function useful when debugging your memory allocator

We are implementing this project using LinkedList datastructure.

To know about Our implementation details,Click this link below

https://drive.google.com/file/d/1aJ02rTpJc2NaLmc1EQa0N_DDLPmj11-L/view?usp=sharing
