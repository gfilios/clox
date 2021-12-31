//
// Created by Georg Filios on 30.12.21.
//

#ifndef CLOX_CHUNK_H
#define CLOX_CHUNK_H

#include "common.h"
#include "value.h"

typedef enum {
    OP_CONSTANT,
    OP_NEGATE,
    OP_RETURN
} OpCode;

typedef struct {
    int count;
    int capacity;
    u_int8_t* code;
    int* lines;
    ValueArray constants;
} Chunk;

void initChunk(Chunk* chunk);
void freeChunk(Chunk* chunk);
void writeChunk(Chunk* chunk, uint8_t byte, int line);
int addConstant(Chunk *chunk, Value value);

#endif //CLOX_CHUNK_H
