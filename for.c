#include <windows.h>
#include <stdio.h>

int main() {

    const SIZE_T allocation_size = 1024 * 1024 * 10;  // Allocate 10 megabytes at a time
    long long int count=0;
    void* block=NULL;

    for(long long int i=0;i<1000000000000;i++) {
        block=malloc(allocation_size);
        if (block == NULL) {
            printf("\nfailed keeping on keeping on mohahaha\n");
            
        }
        else{
            count+=1;
        }
        count+= allocation_size;
        printf("\rRequested %zu bytes so far", allocation_size*count);

    }

    return 1;
}
