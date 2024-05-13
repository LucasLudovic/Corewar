/*
** EPITECH PROJECT, 2024
** Corewar
** File description:
** Principal function of the corewar
*/

#include <stdlib.h>
#include <stdio.h>
#include "champions/champions.h"
#include "my.h"
#include "corewar.h"
#include "my_macros.h"
#include "virtualmachine/set_load_address.h"
#include "virtualmachine/initialize_vm.h"

static
void destroy_champions(cpu_t *cpu)
{
    if (cpu == NULL)
        return;
    for (size_t i = 0; i < NB_CHAMPIONS && cpu->champions[i] != NULL; i += 1) {
        if (cpu->champions[i]->name != NULL)
            free(cpu->champions[i]->name);
        if (cpu->champions[i]->file_stream != NULL)
            fclose(cpu->champions[i]->file_stream);
        if (cpu->champions[i]->header != NULL)
            free(cpu->champions[i]->header);
        if (cpu->champions[i] != NULL)
            free(cpu->champions[i]);
    }
}

int execute_corewar(char const *const *argv)
{
    cpu_t cpu = { 0 };

    if (initialize_vm(&cpu, argv) == FAILURE) {
        destroy_champions(&cpu);
        return display_error("Unable to initialize the cpu\n");
    }
    if (retrieve_champions_instructions(&cpu) == FAILURE)
        return FAILURE;
    if (set_load_address(&cpu) == FAILURE)
        return display_error("Unable to load address\n");
    if (execute_arena(&cpu) == FAILURE)
        return FAILURE;
    for (size_t i = 0; i < NB_CHAMPIONS && cpu.champions[i] != NULL; i += 1) {
        if (cpu.champions[i]->name != NULL)
            printf("champions n°%ld = %s\n", i, cpu.champions[i]->name);
        printf("load address = %d\n", cpu.champions[i]->load_address);
        printf("prog number = %ld\n", cpu.champions[i]->program_counter);
    }
    destroy_champions(&cpu);
    return SUCCESS;
}
