//
// Created by Georg Filios on 30.12.21.
//

#ifndef CLOX_VALUE_H
#define CLOX_VALUE_H

typedef double Value;

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
