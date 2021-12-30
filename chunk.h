//
// Created by Georg Filios on 30.12.21.
//

#ifndef CLOX_CHUNK_H
#define CLOX_CHUNK_H

#include "common.h"
typedef enum {
    OP_RETURN
} OpCode;

typedef struct {
    int count;
    int capacity;
    u_int8_t* code;
} Chunk;

void initChunk(Chunk* chunk);
void freeChunk(Chunk* chunk);
void writeChunk(Chunk* chunk, uint8_t byte);
#endif //CLOX_CHUNK_H
