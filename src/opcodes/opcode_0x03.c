/*
** EPITECH PROJECT, 2024
** corewar
** File description:
** opcode_0x03.c
*/

#include "champions/champions.h"
#include "my_macros.h"
#include "op.h"
#include "virtualmachine/initialize_vm.h"
#include "my.h"
#include <stdint.h>

static
void assign_indirect(cpu_t *cpu, champions_t *champion,
    uint32_t *first_param, uint16_t *second_param)
{
    *second_param = *second_param << 2;
    *second_param += cpu->memory[(champion->program_counter + 4) % MEM_SIZE];
    if (*first_param >= REG_NUMBER) {
        champion->alive = FALSE;
        return;
    }
    cpu->memory[(champion->program_counter + *second_param % IDX_MOD)
        % MEM_SIZE] = champion->registers[*first_param];
}

static
int check_param(champions_t *champion, size_t first_param, size_t second_param)
{
    if (second_param >= REG_NUMBER || first_param >= REG_NUMBER) {
        champion->alive = FALSE;
        return FAILURE;
    }
    return SUCCESS;
}

static
void store_value(cpu_t *cpu, champions_t *champion, uint8_t coding_byte)
{
    uint64_t new_pc = champion->program_counter + CODING_BYTE;
    uint32_t first_param = 0;
    uint16_t second_param = 0;

    coding_byte = coding_byte << 2;
    coding_byte = coding_byte >> 6;
    first_param = cpu->memory[(champion->program_counter + 2) % MEM_SIZE];
    second_param = cpu->memory[(champion->program_counter + 3) % MEM_SIZE];
    if (coding_byte == 0x01) {
        new_pc += 2;
        if (check_param(champion, first_param, second_param) == FAILURE)
            return;
        champion->registers[second_param] = champion->registers[first_param];
    }
    if (coding_byte == 0x03) {
        new_pc += 3;
        assign_indirect(cpu, champion, &first_param, &second_param);
    }
    champion->program_counter = (new_pc + 1) % MEM_SIZE;
}

int execute_opcode_st(cpu_t *cpu, champions_t *champion)
{
    uint8_t coding_byte = cpu->memory[champion->program_counter + 1];

    if (cpu == NULL || champion == NULL)
        return display_error("Unable to retrieve structs for st\n");
    champion->index = false;
    store_value(cpu, champion, coding_byte);
    return SUCCESS;
}
