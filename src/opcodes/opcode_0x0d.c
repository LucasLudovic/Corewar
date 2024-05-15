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
#include "my.h"
#include "my_macros.h"

static
void compute_register_value(champions_t *champion,
    uint32_t first_param, uint8_t second_param)
{
    champion->registers[second_param] = champion->program_counter;
    champion->registers[second_param] += (first_param);
    champion->carry = !champion->carry;
}

static
void assign_indirect(cpu_t *cpu, champions_t *champion,
    uint32_t *first_param, uint8_t *second_param)
{
    *first_param = *((uint16_t *)(&(
        cpu->memory[(champion->program_counter + 2) % MEM_SIZE])));
    *first_param = *((uint16_t *)(&(cpu->memory[
    (champion->load_address + *first_param) % MEM_SIZE])));
    *second_param = cpu->memory[(champion->program_counter + 4) % MEM_SIZE];
}

static
int update_register(cpu_t *cpu, champions_t *champion, uint8_t coding_byte)
{
    uint64_t new_pc = champion->program_counter + CODING_BYTE;
    uint32_t first_param = 0;
    uint8_t second_param = 0;

    if (coding_byte >> 6 & T_DIR) {
        new_pc += 5;
        first_param = *((uint32_t *)(&(
        cpu->memory[(champion->program_counter + 2) % MEM_SIZE])));
        second_param = cpu->memory[(champion->program_counter + 6) % MEM_SIZE];
    }
    if (coding_byte >> 6 & T_IND) {
        new_pc += 3;
        assign_indirect(cpu, champion, &first_param, &second_param);
    }
    compute_register_value(champion, first_param, second_param);
    champion->program_counter = (new_pc + 1) % MEM_SIZE;
    return SUCCESS;
}

int execute_opcode_lld(cpu_t *cpu, champions_t *champion)
{
    uint8_t coding_byte = cpu->memory[champion->program_counter + 1];

    if (cpu == NULL || champion == NULL)
        return display_error("Unable to retrieve structs for ld\n");
    update_register(cpu, champion, coding_byte);
    return SUCCESS;
}
