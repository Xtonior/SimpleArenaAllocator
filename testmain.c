#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "aallocator.h"

int size = 134217728;

typedef struct HeavyData
{
    int data;
} HeavyData;

void benchMalloc()
{
    Node *head = NULL;
    Node *curr = NULL;

    clock_t start = clock(); 

    for (int i = 0; i < size; i++)
    {
        Node *node = (Node *)malloc(sizeof(Node));
        node->data = &i;
        node->next = NULL;

        if (head == NULL)
        {
            head = node;
            curr = head;
        }
        else
        {
            curr->next = node;
            curr = curr->next;
        }
    }

    clock_t end = clock(); 

    printf("Malloc Allocation Time: %.6f seconds\n", (double)(end - start) / CLOCKS_PER_SEC);

    clock_t start2 = clock();
    curr = head;
    while (curr != NULL)
    {
        HeavyData *next = curr->next;
        free(curr);
        curr = next;
    }
    clock_t end2 = clock();
    printf("Malloc Free Time: %.6f seconds\n", (double)(end2 - start2) / CLOCKS_PER_SEC);
}

void benchArena()
{
    int capacity = size;

    Arena *arena = CreateArena(capacity * sizeof(Node) + capacity * sizeof(int));

    Node *head = NULL;
    Node *curr = head;

    clock_t start = clock();
    for (int i = 0; i < size; i++) 
    {
        curr = AllocateFromArena(arena, sizeof(Node)); 
        curr->data = AllocateFromArena(arena, sizeof(int));
        *(int *)(curr->data) = i; 
        // printf("%d\n", *(int *)(curr->data)); 
        curr = curr->next;
    }
    
    clock_t end = clock();
    printf("Arena Allocation Time: %.6f seconds\n", (double)(end - start) / CLOCKS_PER_SEC);

    clock_t start2 = clock();
    FreeArena(arena);
    clock_t end2 = clock();
    printf("Arena Free Time: %.6f seconds\n", (double)(end2 - start2) / CLOCKS_PER_SEC);
    
}

int main()
{    
    printf("data amount: %d, data size: %d bytes\n", size, size * sizeof(HeavyData));
    benchMalloc();
    benchArena();
    return 0;
}