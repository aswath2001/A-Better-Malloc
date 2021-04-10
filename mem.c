#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/mman.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<stdint.h>
#include"mem.h"

struct node
{
        int size;
        int is_free;
        struct node *next;
        void *dataptr;
}*head;


int Mem_Init(int SizeOfRegion)
{
        if(SizeOfRegion<=0)
        {
                printf("\n---Invalid Size---\n");
                return -1;
        }

        int fd = open("/dev/zero",O_RDWR);
        ptr = mmap(NULL,2*SizeOfRegion,PROT_READ|PROT_WRITE,MAP_PRIVATE,fd,0);

        allotted = SizeOfRegion;

        if(ptr == MAP_FAILED)
        {
                printf("\n---Mmap Error---\n");
                return -1;
        }
        head = (struct node*)(ptr + SizeOfRegion);

        head->size = 0;
        head->is_free = 1;
        head->next = NULL;
        head->dataptr = ptr;
        return 1;
}

void *Mem_Alloc(int size)
{
        struct node *temp;
        struct node *curr = head;

        if(size > 0)
        {
                if(size > allotted)
                {
                        printf("\n---Not Enough Space Available(1)---\n");
                        return NULL;
                }
                else if(allocated + size > allotted)
                {
                        printf("\n---Not enough Space Available(2)---\n");
                        return NULL;
                }
                else
                {
                        while(curr != NULL)
                        {
                                if(curr->is_free == 1)
                                {
                                        if(curr->size == 0)
                                        {
                                                curr->size = size;
                                                curr->is_free = 0;
                                                allocated += size;

                                                temp = curr + sizeof(curr);
                                                temp->size = 0;
                                                temp->is_free = 1;
                                                temp->next = NULL;
                                                temp->dataptr = curr->dataptr + curr->size;
                                                curr->next = temp;
                                                return curr->dataptr;
                                        }
                                        else if(curr->size >= size)
                                        {
                                                curr->is_free = 0;
                                                allocated += size;
                                                return curr->dataptr;
                                        }
                                        else
                                        {
                                                curr = curr->next;
                                        }
                                }
                                else
                                {
                                        curr = curr->next;
                                }
                        }
                        printf("\n---Not Enough Space Available---(3)\n");
                        return NULL;
                }
        }
        else
        {
                printf("\n---Size should be positive---\n");
                return NULL;
        }
}


int Mem_Free(void *ptr1)
{
        if(ptr1 == NULL || ptr1 > ptr+allotted)
        {
                printf("\n---Not Allocated---\n");
                return 1;
        }


        int flag=0;
        struct node *curr=head;

        if(ptr1>=curr->dataptr)
        {
                while(curr!=NULL)
                {
                        if(ptr1>=curr->dataptr && ptr1< (curr->next)->dataptr)
                        {
                                printf("\n---Located the data pointer---\n");
                                flag++;
                                break;
                        }
                        curr=curr->next;
                }
        }
        else
        {
                printf("\n---Memory not allocated---\n");
                return -1;
        }
        if(flag==0)
        {
                return -1;
        }
        if(curr->is_free==1)
        {
                return -1;
        }
        if(ptr1==curr->dataptr)
        {
                allocated-=curr->size;
                curr->size=0;
                curr->is_free=1;
        }
        else
        {
                struct node *temp;
                temp = (struct node*)ptr1;
                temp->size = (uintptr_t)ptr1-(uintptr_t)curr->dataptr;
                temp->size=curr->size - temp->size;
                curr->size=curr->size - temp->size;
                temp->is_free = 1;
                temp->next = curr->next;
                temp->dataptr = ptr1 ;
                allocated-=temp->size;
                curr->next=temp;
        }
        //printf("\n---Allocated: %d---\n",allocated);
        MergeUnAllocated();
        return 0;
}
void MergeUnAllocated()
{
        struct node *n=head;
        while(n!=NULL)
        {
                if(n->next!=NULL)
                {
                        if(n->is_free == 1 && (n->next)->is_free == 1)
                        {
                                n->size=n->size+(n->next)->size;
                                n->next = (n->next)->next;
                        }
                        else
                        {
                                n=n->next;
                        }
                }
                else
                {
                        n=n->next;
                }
        }
}
void traverse()
{
        struct node *n=head;
        while(n!=NULL)
        {
                printf("\n---Dataptr:%p ;Size:%d ;Status:%d---\n",n->dataptr,n->size,n->is_free);
                n=n->next;
        }
}
int Mem_GetSize(void *ptr1)
{
        if(ptr1 == NULL || ptr1 > ptr+allotted)
        {
                return -1;
        }
        int flag=0;
        struct node *curr=head;
        while(curr!=NULL)
        {
                if(ptr1>=curr->dataptr && ptr1< (curr->next)->dataptr)
                {
                         printf("Located the datapointer");
                         if(curr->is_free==1)
                         {
                                return -1;
                         }
                         return curr->size;
                }
                else
                {
                        curr=curr->next;
                }
        }
        return -1;
}
int Mem_IsValid(void *ptr1)
{
        int s=Mem_GetSize(ptr1);
        if(s==-1)
        {
                return 0;
        }
        return 1;
}





