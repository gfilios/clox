//
// Created by Georg Filios on 31.12.21.
//

#include "vm.h"
#include "common.h"
#include "value.h"
#include <stdio.h>
#include "debug.h"

VM vm;

static void resetStack(){
    vm.stackTop = vm.stack;
}


void initVM(){

}

void freeVM(){

}

static void debug_trace_execution(){
    printf(" ");
    for (Value* slot = vm.stack;slot<vm.stackTop;slot++){
        printf("[ ");
        printValue(*slot);
        printf(" ]\t\t\t\t\t\t\t\t// current Stack");
    }
    printf("\n");
    disassembleInstruction(vm.chunk,(int)(vm.ip - vm.chunk->code));
}


static InterpretResult run() {
#define READ_BYTE() (*vm.ip++)
#define READ_CONSTANT() (vm.chunk->constants.values[READ_BYTE()])
    resetStack();
    for (;;) {
#ifdef DEBUG_TRACE_EXECUTION
        debug_trace_execution();
#endif
        uint8_t instruction;
        switch (instruction=READ_BYTE()) {
            case OP_CONSTANT: {
                Value constant = READ_CONSTANT();
                push(constant);
                break;
            }
            case OP_RETURN:
                printValue(pop());
                printf("\n");
                return INTERPRET_OK;
        }
    }
#undef READ_CONSTANT
#undef READ_BYTE
}

InterpretResult interpret(Chunk* chunk){
    vm.chunk = chunk;
    vm.ip = vm.chunk->code;
    return run();
}

void push(Value value){
    *vm.stackTop = value;
    vm.stackTop++;
}

Value pop(){
    vm.stackTop--;
    return *vm.stackTop;
}

