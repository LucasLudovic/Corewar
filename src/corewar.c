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
    while (cpu->champions != NULL) {
        printf("name = %s\n", cpu->champions->name);
        printf("load address = %d\n", cpu->champions->load_address);
        cpu->champions = cpu->champions->next;
    }
    free(cpu);
    return SUCCESS;
}
