#ifndef AALOCATOR_H
#define AALOCATOR_H

#include <stdint.h>
#include <stdio.h>

#include "/home/xtonior/Documents/Projects/C/MyLibs/Node/node.h"

typedef struct Arena
{
    uint8_t *pool;
    size_t size;
    size_t used;
} Arena;

Arena *CreateArena(size_t size);
void *AllocateFromArena(Arena *arena, size_t size);
int FreeArena(struct Arena* arena);

#endif