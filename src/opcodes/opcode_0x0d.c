/*
** EPITECH PROJECT, 2024
** coreware
** File description:
** opcode_0x0d.c
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
int check_second_param(champions_t *champion, size_t second_param)
{
    if (second_param >= REG_NUMBER) {
        champion->alive = FALSE;
        return FAILURE;
    }
    return SUCCESS;
}

static
void check_first_param(champions_t *champion, size_t first_param,
    size_t second_param)
{
    if (first_param >= REG_NUMBER || second_param >= REG_NUMBER) {
        champion->alive = FALSE;
        return;
        }
    champion->registers[second_param] = champion->registers[first_param];
}

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
    if (check_second_param(champion, second_param) == FAILURE)
        return SUCCESS;
    if (previons_bytes == 2)
        check_first_param(champion, first_param, second_param);
    if (previons_bytes != 2)
        champion->registers[second_param] =
            cpu->memory[champion->program_counter + first_param];
    champion->program_counter = (champion->program_counter + (bytes + 1))
        % MEM_SIZE;
    if (first_param == 0)
        champion->carry = true;
    return SUCCESS;
}

int execute_opcode_lld(cpu_t *cpu, champions_t *champion)
{
    if (cpu == NULL || champion == NULL)
        return display_error("Unable to retrieve structs for lld\n");
    champion->index = false;
    champion->carry = false;
    update_register(cpu, champion);
    return SUCCESS;
}
