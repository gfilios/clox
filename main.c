#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "chunk.h"
#include "common.h"
#include "debug.h"
#include "vm.h"


static FILE *openFile(const char *path);

static size_t getFileSize(FILE *file);

static char *allocateBufferForFile(const char *path, size_t fileSize);

static void readFileIntoBuffer(const char *path, FILE *file, size_t fileSize, char *buffer);

static void repl(){
    char line[1024];
    for(;;){
        printf("> ");
        if (!fgets(line,sizeof(line), stdin)){
            printf("\n");
            break;
        }
        interpret(line);
    }
}

static char* readFile(const char* path){
    FILE *file = openFile(path);
    size_t fileSize = getFileSize(file);
    char *buffer = allocateBufferForFile(path, fileSize);
    readFileIntoBuffer(path, file, fileSize, buffer);
    fclose(file);
    return buffer;
}

static void readFileIntoBuffer(const char *path, FILE *file, size_t fileSize, char *buffer) {
    size_t bytes_read = fread(buffer, sizeof (char), fileSize, file);
    if (bytes_read<fileSize) {
        fprintf(stderr, "Could not read file \"%s\".\n", path);
        exit(74);
    }
    buffer[bytes_read]='\0';
}

static char *allocateBufferForFile(const char *path, size_t fileSize) {
    char * buffer = (char*) malloc(fileSize + 1);
    if (buffer==NULL){
        fprintf(stderr, "Not enough memory to read \"%s\".\n", path);
        exit(74);
    }
    return buffer;
}

static size_t getFileSize(FILE *file) {
    fseek(file, 0L, SEEK_END);
    size_t fileSize = ftell(file);
    rewind(file);
    return fileSize;
}

static FILE *openFile(const char *path) {
    FILE* file = fopen(path, "rb");
    if (file == NULL) {
        fprintf(stderr, "Could not open file \"%s\".\n", path);
        exit(74);
    }
    return file;
}

static void runFile(const char* path){
    char *source = readFile(path);
    InterpretResult result = interpret(source);
    free(source);
    if (result==INTERPRET_COMPILE_ERROR) exit(65);
    if (result==INTERPRET_RUNTIME_ERROR) exit(70);

}

int main(int argc, const char* argv[]) {

    initVM();

    if (argc == 1) {
        repl();
    } else if (argc == 2) {
        runFile(argv[1]);
    } else {
        fprintf(stderr, "Usage: clox [path]\n");
        exit(64);
    }

    freeVM();
    return 0;
}
