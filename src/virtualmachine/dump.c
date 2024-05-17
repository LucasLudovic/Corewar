/*
** EPITECH PROJECT, 2024
** corewar
** File description:
** dump.c
*/

#include "my.h"
#include "virtualmachine/initialize_vm.h"

void display_memory(cpu_t *cpu)
{
    for (size_t i = 0; i < MEM_SIZE; i += 1) {
        my_print_hexa_maj(cpu->memory[i]);
        if (i % 32 == 0 && i != 0)
            my_putchar('\n');
    }
    my_putchar('\n');
}

int dump_memory(cpu_t *cpu)
{
    if (cpu->dump != -1) {
        if (cpu->dump == 0) {
            display_memory(cpu);
            return SUCCESS;
        }
        cpu->dump -= 1;
    }
    return FAILURE;
}
