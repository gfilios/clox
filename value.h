//
// Created by Georg Filios on 30.12.21.
//

#ifndef CLOX_VALUE_H
#define CLOX_VALUE_H
#include "common.h"

typedef enum {
    VAL_BOOL,
    VAL_NIL,
    VAL_NUMBER
} ValueType;

typedef struct {
     ValueType type;
     union {
         bool boolean;
         double number;
     } as;
} Value;
#define IS_BOOL(value) ((value).type == VAL_BOOL)
#define IS_NUMBER(value) ((value).type == VAL_NUMBER)
#define IS_NIL(value) ((value).type == VAL_NIL)
#define AS_BOOL(value)((value).as.boolean)
#define AS_NUMBER(value)((value).as.number)
#define BOOL_VAL(value)(Value){VAL_BOOL,{.boolean = value}}
#define NIL_VAL (Value){VAL_NIL,{.number = 0}}
#define NUMBER_VAL(value)(Value){VAL_NUMBER,{.number = value}}

typedef struct {
    int capacity;
    int count;
    Value* values;
} ValueArray;

void initValueArray(ValueArray* valueArray);
void freeValueArray(ValueArray* valueArray);
void writeValueArray(ValueArray* valueArray, Value value);
void printValue(Value value);

#endif //CLOX_VALUE_H
