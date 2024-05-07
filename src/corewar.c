/*
** EPITECH PROJECT, 2024
** Corewar
** File description:
** Principal function of the corewar
*/

#include "corewar.h"
#include "my_macros.h"
#include "virtualmachine/initialize_vm.h"
#include <stdlib.h>
#include <stdio.h>

int execute_corewar(char const *const *argv)
{
    cpu_t *cpu = malloc(sizeof(cpu_t));

    if (cpu == NULL)
        return FAILURE;
    if (initialize_vm(cpu, argv) == FAILURE)
        return FAILURE;
    printf("PRINT CHAMPIONS\n");
    for (size_t i = 0; i < NB_CHAMPIONS; i += 1) {
        printf("coubeh %ld\n", i);
    }
    free(cpu);
    return SUCCESS;
}
