#include <stdio.h>
#include <stdlib.h>

#define MAX_STACK_SIZE 256
#define PROGRAM_FILE "program.avr"

typedef enum
{
    PUSH,
    POP,
    ADD
} InstructionSet;

typedef struct
{
    InstructionSet instruct;
    int value;
} Instruction;

typedef struct
{
    int stack[MAX_STACK_SIZE];
    int sp;
} VM;

VM *newVM()
{
    VM *vm = malloc(sizeof(VM));
    vm->sp = 0;
    return vm;
}

void push(VM *vm, int value)
{
    if (vm->sp == MAX_STACK_SIZE)
    {
        return;
    }
    vm->stack[vm->sp++] = value;
}

int pop(VM *vm)
{
    if (vm->sp == 0)
    {
        return 0;
    }
    return vm->stack[--vm->sp];
}

void add(VM *vm)
{
    int a = pop(vm);
    int b = pop(vm);
    push(vm, a + b);
}

void execute(VM *vm, Instruction *program, int program_size)
{
    for (int i = 0; i < program_size; i++)
    {
        switch (program[i].instruct)
        {
        case PUSH:
            push(vm, program[i].value);
            break;
        case POP:
            pop(vm);
            break;
        case ADD:
            add(vm);
            break;
        }
    }
}

void print_top_of_stack(VM *vm)
{
    printf("%d", vm->stack[vm->sp - 1]);
}

void write_instructions_to_file(Instruction *program, int program_size)
{
    FILE *file = fopen(PROGRAM_FILE, "wb");
    if (file == NULL)
    {
        printf("Unable to open file for writing\n");
        return;
    }

    fwrite(program, sizeof(Instruction), program_size, file);
    fclose(file);
}

Instruction *read_instructions_from_file(int *program_size)
{
    FILE *file = fopen(PROGRAM_FILE, "rb");
    if (file == NULL)
    {
        return NULL;
    }

    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    rewind(file);

    *program_size = file_size / sizeof(Instruction);

    Instruction *program = malloc(file_size);

    fread(program, sizeof(Instruction), *program_size, file);
    fclose(file);

    return program;
}

int main()
{
    VM *vm = newVM();

    Instruction program[] = {
        {PUSH, 3},
        {PUSH, 4},
        {ADD}};
#if 1
    execute(vm, program, 3);
    print_top_of_stack(vm);
#endif

#if 0
    write_instructions_to_file(program, 3);

    int program_size;
    Instruction *program_from_file = read_instructions_from_file(&program_size);

    execute(vm, program_from_file, program_size);
    print_top_of_stack(vm);
#endif
    free(vm);
    return 0;
}
