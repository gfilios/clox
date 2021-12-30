//
// Created by Georg Filios on 30.12.21.
//

#ifndef CLOX_DEBUG_H
#define CLOX_DEBUG_H
#include "chunk.h"

void disassemble(Chunk *chunk, const char* name);
int disassembleInstruction(Chunk *chunk, int offset);

#endif //CLOX_DEBUG_H
