//
// Created by Georg Filios on 31.12.21.
//

#ifndef CLOX_VM_H
#define CLOX_VM_H

#include "chunk.h"
#define STACK_MAX 256

typedef struct {
    Chunk* chunk;
    uint8_t* ip;
    Value stack[STACK_MAX];
    Value* stackTop;
} VM;

typedef enum {
    INTERPRET_OK,
    INTERPRET_RUNTIME_ERROR,
    INTERPRET_COMPILE_ERROR
} InterpretResult;


void initVM();
void freeVM();
InterpretResult interpret(Chunk* chunk);
void push(Value value);
Value pop();

#endif //CLOX_VM_H