/*
** EPITECH PROJECT, 2024
** 42sh
** File description:
** Execute the virtual machine
*/

#include <stdint.h>
#include "instructions/instructions.h"
#include "champions/champions.h"
#include "virtualmachine/initialize_vm.h"
#include "my_macros.h"
#include "my.h"

static
int execute_single_champion(cpu_t *cpu, champions_t *champion)
{
    if (champion->nbr_cycles == cpu->nb_cycle) {
        if (execute_instruction(cpu, champion) == FAILURE)
            return FAILURE;
        if (retrieve_instruction(cpu, champion) == FAILURE)
            return FAILURE;
    }
    return SUCCESS;
}

static
void execute_champions(cpu_t *cpu)
{
    for (size_t i = 0; cpu->champions[i] != NULL && i < NB_CHAMPIONS; i += 1)
        execute_single_champion(cpu, cpu->champions[i]);
}

int execute_arena(cpu_t *cpu)
{
    if (cpu == NULL)
        return display_error("Unable to access cpu informations\n");
    while (cpu->state != CPU_HALTED) {
        execute_champions(cpu);
        cpu->nb_cycle += 1;
    }
    return SUCCESS;
}
