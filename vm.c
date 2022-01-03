//
// Created by Georg Filios on 31.12.21.
//

#include "vm.h"
#include "common.h"
#include "value.h"
#include <stdio.h>
#include <stdarg.h>
#include "debug.h"
#include "compiler.h"

VM vm;

static void resetStack() {
    vm.stackTop = vm.stack;
}

void initVM() {
}

void freeVM() {
}

static void runtimeError(const char *format, ...) {
    va_list args;
    va_start(args, format);
    vfprintf(stderr, format, args);
    va_end(args);
    fputs("\n", stderr);

    size_t instruction = vm.ip - vm.chunk->code - 1;
    int line = vm.chunk->lines[instruction];
    fprintf(stderr, "[line %d] in script\n", line);
    resetStack();
}

static void debug_trace_execution() {
    printf(" ");
    for (Value *slot = vm.stack; slot < vm.stackTop; slot++) {
        printf("[ ");
        printValue(*slot);
        printf(" ]");
    }
    printf("\t\t\t\t\t\t\t\t// current Stack\n");
    disassembleInstruction(vm.chunk, (int) (vm.ip - vm.chunk->code));
}

Value peek(int distance) {
    return vm.stackTop[-1 - distance];
}

static InterpretResult run() {
#define READ_BYTE() (*vm.ip++)
#define READ_CONSTANT() (vm.chunk->constants.values[READ_BYTE()])
#define BINARY_OP(valueType, op)    \
    do {                            \
        if(IS_NUMBER(peek(0))&&IS_NUMBER(peek(1))) {     \
            double b = AS_NUMBER(pop());                 \
            double a = AS_NUMBER(pop());                 \
            push(valueType( a op b));                     \
        }                                                \
    } while (false);

    resetStack();
    for (;;) {
#ifdef DEBUG_TRACE_EXECUTION
        debug_trace_execution();
#endif
        uint8_t instruction;
        switch (instruction = READ_BYTE()) {
            case OP_CONSTANT: {
                Value constant = READ_CONSTANT();
                push(constant);
                break;
            }
            case OP_ADD :BINARY_OP(NUMBER_VAL, +);
                break;
            case OP_SUBTRACT :BINARY_OP(NUMBER_VAL, -);
                break;
            case OP_MULTIPLY :BINARY_OP(NUMBER_VAL, *);
                break;
            case OP_DIVIDE :BINARY_OP(NUMBER_VAL, /);
                break;
            case OP_NEGATE:
                if (!IS_NUMBER(peek(0))) {
                    runtimeError("Operand must be a number.");
                    return INTERPRET_RUNTIME_ERROR;
                }
                push(NUMBER_VAL(-1 * AS_NUMBER(pop())));
                break;
            case OP_RETURN:printValue(pop());
                printf("\n");
                return INTERPRET_OK;
        }
    }
#undef BINARY_OP
#undef READ_CONSTANT
#undef READ_BYTE
}

InterpretResult interpret(const char *source) {
    Chunk chunk;
    initChunk(&chunk);
    if (!compile(source, &chunk)) {
        freeChunk(&chunk);
        return INTERPRET_COMPILE_ERROR;
    }
    vm.chunk = &chunk;
    vm.ip = vm.chunk->code;
    InterpretResult result = run();
    freeChunk(&chunk);
    return result;
}

void push(Value value) {
    *vm.stackTop = value;
    vm.stackTop++;
}

Value pop() {
    vm.stackTop--;
    return *vm.stackTop;
}

