#include <windows.h>
#include <stdio.h>

int main() {
    const SIZE_T allocation_size = 1024 * 1024 * 10;  // Allocate 10 megabytes at a time
    SIZE_T total_requested = 0;
    LPVOID block;
    SYSTEM_INFO si;

    GetSystemInfo(&si); // Get system information including page size
    SIZE_T pageSize = si.dwPageSize;

    while (1) {
        block = VirtualAlloc(NULL, allocation_size, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
        if (block == NULL) {
            printf("\nVirtualAlloc failed: Last error: %lu\n", GetLastError());
            break;
        }
        total_requested += allocation_size;
        printf("\rRequested %zu bytes so far", total_requested);

        // Write to each page to ensure it's committed
        for (char *ptr = (char *)block; ptr < (char *)block + allocation_size; ptr += pageSize) {
            *ptr = 0xFF;  // Write a single byte to each page
        }
    }

    // Optionally, add a pause to observe the effects
    printf("\nMaximum allocation reached, pausing...\n");
    Sleep(3000);  // Sleep for 3 seconds

    return 0;
}
