#include <stdio.h>
#include <stdlib.h>

#define MAX_STACK_SIZE 256
#define MAX_MEMORY_SIZE 1024

typedef enum
{
    PUSH,
    POP,
    ADD,
    MUL,
    STORE,
    LOAD
} InstructionSet;

typedef struct
{
    InstructionSet instruct;
    int value;
} Instruction;

typedef struct
{
    int stack[MAX_STACK_SIZE];
    int memory[MAX_MEMORY_SIZE];
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

void mul(VM *vm)
{
    int a = pop(vm);
    int b = pop(vm);
    push(vm, a * b);
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
        case MUL:
            mul(vm);
            break;
        case STORE:
            if (vm->sp == 0 || program[i].value >= MAX_MEMORY_SIZE)
            {
                return;
            }
            vm->memory[program[i].value] = pop(vm);
            break;
        case LOAD:
            if (program[i].value >= MAX_MEMORY_SIZE)
            {
                return;
            }
            push(vm, vm->memory[program[i].value]);
            break;
        }
    }
}
void print_top_of_stack(VM *vm)
{
    printf("%d", vm->stack[vm->sp - 1]);
}

int main()
{
    VM *vm = newVM();

    Instruction program[] = {
        {PUSH, 5},
        {PUSH, 4},
        {ADD},
        {STORE, 0},
        {PUSH, 8},
        {PUSH, 2},
        {ADD},
        {LOAD, 0},
        {MUL}};

    execute(vm, program, 9);
    print_top_of_stack(vm);
    free(vm);
    return 0;
}
