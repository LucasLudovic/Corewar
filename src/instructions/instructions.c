/*
** EPITECH PROJECT, 2024
** Corewar
** File description:
** Instructions for the champions
*/

#include "instructions/instructions.h"
#include "champions/champions.h"
#include "virtualmachine/initialize_vm.h"
#include "my_macros.h"
#include "my.h"
#include "op.h"

static
int check_single_instruction(cpu_t *cpu, champions_t *champion, int i)
{
    if (champion->instructions == op_tab[i].code) {
        instruction_table[i](cpu, champion);
        return SUCCESS;
    }
    return FAILURE;
}

int execute_instruction(cpu_t *cpu, champions_t *champion)
{
    if (cpu == NULL || champion == NULL)
        return display_error("Unable to execute instructions\n");
    for (size_t i = 0; op_tab[i].code != 0; i += 1) {
        if (check_single_instruction(cpu, champion, i) == SUCCESS) {
            return SUCCESS;
        }
    }
    champion->alive = FALSE;
    return FAILURE;
}

static
void retrieve_instruction_cycle(cpu_t *cpu, champions_t *champion)
{
    for (size_t i = 0; op_tab[i].code != 0; i += 1) {
        if (op_tab[i].code == champion->instructions) {
            champion->nbr_cycles = cpu->nb_cycle + op_tab[i].nbr_cycles;
            champion->nbr_cycles %= cpu->cycle_max;
        }
    }
}

int retrieve_instruction(cpu_t *cpu, champions_t *champion)
{
    if (cpu == NULL || champion == NULL)
        return display_error("Unable to retrieve instructions\n");
    champion->instructions = cpu->memory[champion->program_counter % MEM_SIZE];
    retrieve_instruction_cycle(cpu, champion);
    return SUCCESS;
}
