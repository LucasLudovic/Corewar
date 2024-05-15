/*
** EPITECH PROJECT, 2024
** 42sh
** File description:
** Execute the virtual machine
*/

#include <stdint.h>
#include "instructions/instructions.h"
#include "champions/champions.h"
#include "op.h"
#include "virtualmachine/initialize_vm.h"
#include "my_macros.h"
#include "my.h"

static
int execute_single_champion(cpu_t *cpu, champions_t *champion)
{
    if (champion->nbr_cycles == cpu->nb_cycle) {
        if (execute_instruction(cpu, champion) == FAILURE)
            return FAILURE;
        if (retrieve_instruction(cpu, champion) == FAILURE) {
            return FAILURE;
        }
    }
    return SUCCESS;
}

static
void execute_champions(cpu_t *cpu)
{
    for (size_t i = 0; cpu->champions[i] != NULL && i < NB_CHAMPIONS; i += 1) {
        if (cpu->champions[i]->alive == TRUE &&
            execute_single_champion(cpu, cpu->champions[i]) == FAILURE)
            cpu->champions[i]->alive = FALSE;
    }
}

static
void retrieve_champions_first_instructions(cpu_t *cpu)
{
    for (size_t i = 0; cpu->champions[i] != NULL && i < NB_CHAMPIONS; i += 1) {
        if (retrieve_instruction(cpu, cpu->champions[i]) == FAILURE)
            cpu->champions[i]->alive = FALSE;
    }
}

int execute_arena(cpu_t *cpu)
{
    cpu->cycle_max = CYCLE_TO_DIE;
    if (cpu == NULL)
        return display_error("Unable to access cpu informations\n");
    retrieve_champions_first_instructions(cpu);
    while (cpu->state != CPU_HALTED) {
        execute_champions(cpu);
        cpu->nb_cycle += 1;
        if (cpu->nb_cycle > cpu->cycle_max) {
            cpu->cycle_max -= CYCLE_DELTA;
            cpu->nb_cycle = 0;
        }
        if (cpu->cycle_max <= 0)
            cpu->state = CPU_HALTED;
    }
    return SUCCESS;
}
