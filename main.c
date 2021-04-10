#include <sys/mman.h>
#include <unistd.h>
#include "mem.c"

int main()
{
        if ( Mem_Init(100) ) //process requests for 100 bytes
        {
                printf("\nMem_Init successful\n");
        }
        else
        {
                printf("\nMem_Init failed\n");
                return 1;
        }

        void *a = Mem_Alloc(30);
        void *b = Mem_Alloc(20);
        void *c = Mem_Alloc(5);
        void *d = Mem_Alloc(50);//I should get error coz iam exceeding size(100)provided by os
        //printf("Value : %d\n",*a);
        printf("Total Memory = %d\n",allotted);
        printf("Allocated Memory = %d\n",allocated);

        printf("Freeing 'a'\n");
        int x = Mem_Free(a);

        if(x == 1)
        {
                printf("No operation performed\n");
        }
        else if(x == 0)
        {
                printf("Mem_Free Success\n");
        }
        else if(x == -1)
        {
                printf("Mem_Free Failure\n");
        }
        printf("Total Memory = %d\n",allotted);
        printf("Allocated Memory = %d\n",allocated);

        printf("Freeing 'b'\n");
        x = Mem_Free(b);

        if(x == 1)
        {
                printf("No operation performed\n");
        }
        else if(x == 0)
        {
                printf("Mem_Free Success\n");
        }
        else if(x == -1)
        {
                printf("Mem_Free Failure\n");
        }
        printf("Total Memory = %d\n",allotted);
        printf("Allocated Memory = %d\n",allocated);
        printf("-------------\n");
        int valid = Mem_IsValid(a+20);
        if( valid == 1 )
                printf("\nMemory is valid\n");
        else
                printf("\nMemory is invalid\n");
        valid=Mem_IsValid(c+2);
        if(valid==1)
                printf("\n Memory is valid\n");
        else
                printf("\nMemory is invalid\n");

}
