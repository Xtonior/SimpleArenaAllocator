#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "aallocator.h"

Arena *CreateArena(size_t size)
{
    Arena *arena = (Arena *)malloc(sizeof(Arena));

    if (!arena) return NULL;

    arena->pool = (uint8_t *)malloc(size);

    if (!arena->pool)
    {
        free(arena);
        return NULL;
    }

    arena->size = size;
    arena->used = 0;

    return arena;
}

void *AllocateFromArena(Arena *arena, size_t size)
{
    if (arena->used + size > arena->size)
    {
        printf("Not enough space in arene: pool: %zu, used: %zu\n", arena->size, arena->used);
        return NULL;
    }

    void *ptr = arena->pool + arena->used; 
    arena->used += size;

    return ptr;
}

int FreeArena(struct Arena* arena)
{
    if (arena == NULL || arena->pool == NULL)
        return 0;

    free(arena->pool);
    free(arena);

    return 0;
}