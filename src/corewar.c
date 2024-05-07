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

static
void destroy_champions(cpu_t *cpu)
{
    if (cpu == NULL)
        return;
    for (size_t i = 0; i < NB_CHAMPIONS; i += 1) {
        if (cpu->champions[i]->name != NULL)
            free(cpu->champions[i]->name);
        if (cpu->champions[i]->file_stream != NULL)
            fclose(cpu->champions[i]->file_stream);
        if (cpu->champions[i] != NULL)
            free(cpu->champions[i]);
    }
}

int execute_corewar(char const *const *argv)
{
    cpu_t *cpu = malloc(sizeof(cpu_t));

    if (cpu == NULL)
        return FAILURE;
    if (initialize_vm(cpu, argv) == FAILURE)
        return FAILURE;
    printf("PRINT CHAMPIONS\n");
    for (size_t i = 0; i < NB_CHAMPIONS; i += 1) {
        if (cpu->champions[i]->name != NULL)
            printf("coubeh = %s\n", cpu->champions[i]->name);
        printf("load address = %d\n", cpu->champions[i]->load_address);
    }
    destroy_champions(cpu);
    free(cpu);
    return SUCCESS;
}
