//
// Created by Georg Filios on 31.12.21.
//

#ifndef CLOX_COMPILER_H
#define CLOX_COMPILER_H
#define IS_LOCAL isLocal()

#include "vm.h"
#include "object.h"

ObjFunction* compile(const char* source);

#endif //CLOX_COMPILER_H
