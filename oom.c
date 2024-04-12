#include <stdio.h>
#include <stdlib.h>
#include <time.h>


typedef struct Node {
    struct Node *next;
    char data[1048576 - sizeof(struct Node *)];
} Node;

const double timer_seconds = 3.0;

int main() {
    clock_t start_time;
    Node *head = NULL;
    Node *current = NULL;
    size_t nodeCount = 0;
    void* leaker=NULL;
    int oomed=0;

    printf("hello I am C\n");
    printf("Allocating memory until a crash...\n");
    while (1) {
        Node *newNode = (Node *)malloc(sizeof(Node));
        if (newNode == NULL) {
            if(!oomed){
                printf("\nstarting timer %f\n",timer_seconds);
                start_time = clock();
                 oomed=1;
            }
            while(1){
                leaker=malloc(1);
                if(!leaker){
                    break;
                }
            }
            double time_passed=(clock()-start_time)/CLOCKS_PER_SEC;
            if ( time_passed>= timer_seconds) {
                printf("done ooming\n");
                break;
            }
            continue;
        }

        newNode->next = NULL;  // Set next pointer to null after allocation

        if (head == NULL) {
            head = newNode;
        } else {
            current->next = newNode;
        }
        current = newNode;
        nodeCount++;

        printf("\rTotal memory allocated: %lu megabytes ", nodeCount);
        if(oomed){
            printf("alocation sucessful!!!");
        }
    }

    // Cleanup, freeing all nodes
    Node *temp;
    while (head != NULL) {
        temp = head->next;
        free(head);
        head = temp;
    }

    printf("\nMemory has been released.\n");

    return 0;
}
