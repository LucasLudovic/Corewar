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
void update_program_counter(champions_t *champion, size_t nb_parameters)
{
    champion->program_counter += nb_parameters + CODING_BYTE + 1;
}

static
int check_single_instruction(cpu_t *cpu, champions_t *champion, int i)
{
    size_t nb_parameters = 0;

    if (champion->instructions == op_tab[i].code) {
        nb_parameters = op_tab[i].nbr_args;
        instruction_table[i](cpu, champion);
        update_program_counter(champion, nb_parameters);
        return SUCCESS;
    }
    return FAILURE;
}

int execute_instruction(cpu_t *cpu, champions_t *champion)
{
    if (cpu == NULL || champion == NULL || champion->instructions == 0)
        return display_error("Unable to execute instructions\n");
    for (size_t i = 0; op_tab[i].code != 0 && instruction_table[i] != NULL;
        i += 1) {
        if (check_single_instruction(cpu, champion, i) == SUCCESS)
            return SUCCESS;
    }
    return display_error("Unable to find the instruction\n");
}

int retrieve_instruction(cpu_t *cpu, champions_t *champion)
{
    if (cpu == NULL || champion == NULL)
        return display_error("Unable to retrieve instructions\n");
    champion->instructions = cpu->memory[champion->program_counter];
    return SUCCESS;
}
