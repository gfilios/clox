//
// Created by Georg Filios on 30.12.21.
//

#include "value.h"
#include <string.h>
#include <stdio.h>
#include "memory.h"


void initValueArray(ValueArray* valueArray){
    valueArray->count = 0;
    valueArray->capacity = 0;
    valueArray->values = NULL;
}

void writeValueArray(ValueArray* array, Value value){
    if (array->capacity<=array->count){
        int oldCapacity = array->capacity;
        array->capacity = GROW_CAPACITY(oldCapacity);
        array->values = GROW_ARRAY(Value, array->values, oldCapacity, array->capacity);
    }
    array->values[array->count] = value;
    array->count++;
}

void printValue(Value value){
    printf("%g",value);
}

void freeValueArray(ValueArray* array){
    FREE_ARRAY(Value, array->values, array->capacity);
    initValueArray(array);
}

