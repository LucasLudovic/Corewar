/*
** EPITECH PROJECT, 2024
** Corewar
** File description:
** P1 = P2, update the carry
*/

#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include "champions/champions.h"
#include "op.h"
#include "virtualmachine/initialize_vm.h"
#include "corewar.h"
#include "opcodes/opcodes.h"
#include "my.h"
#include "my_macros.h"

static
int update_register(cpu_t *cpu, champions_t *champion)
{
    size_t first_param = 0;
    size_t second_param = 0;
    int bytes = 1;
    int previons_bytes = 0;

    bytes = retrieve_first_parameter(cpu, champion, &first_param, bytes);
    previons_bytes = bytes;
    bytes = retrieve_second_parameter(cpu, champion, &second_param, bytes);
    if (previons_bytes == 2)
        champion->registers[second_param] = champion->registers[first_param];
    else
        champion->registers[second_param] =
            cpu->memory[champion->program_counter + first_param % IDX_MOD];
    champion->program_counter = (champion->program_counter + (bytes + 1))
        % MEM_SIZE;
    if (first_param == 0)
        champion->carry = true;
    return SUCCESS;
}

int execute_opcode_ld(cpu_t *cpu, champions_t *champion)
{
    if (cpu == NULL || champion == NULL)
        return display_error("Unable to retrieve structs for ld\n");
    champion->index = false;
    champion->carry = false;
    update_register(cpu, champion);
    return SUCCESS;
}
