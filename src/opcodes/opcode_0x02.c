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
#include "my.h"
#include "my_macros.h"

static
void compute_register_value(champions_t *champion,
    uint32_t first_param, uint8_t second_param)
{
    champion->registers[second_param] = champion->program_counter;
    champion->registers[second_param] += (first_param % IDX_MOD);
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

    if (coding_byte >> 6 == 0x02) {
        new_pc += 5;
        first_param = *((uint32_t *)(&(
        cpu->memory[(champion->program_counter + 2) % MEM_SIZE])));
        second_param = cpu->memory[(champion->program_counter + 6) % MEM_SIZE];
    }
    if (coding_byte >> 6 == 0x03) {
        new_pc += 3;
        assign_indirect(cpu, champion, &first_param, &second_param);
    }
    compute_register_value(champion, first_param, second_param);
    printf("PC : %lu\n", champion->program_counter);
    champion->program_counter = (new_pc + 1) % MEM_SIZE;
    printf("PC : %lu\n", champion->program_counter);
    return SUCCESS;
}

int execute_opcode_ld(cpu_t *cpu, champions_t *champion)
{
    uint8_t coding_byte = cpu->memory[champion->program_counter + 1];

    if (cpu == NULL || champion == NULL)
        return display_error("Unable to retrieve structs for ld\n");
    champion->index = false;
    update_register(cpu, champion, coding_byte);
    return SUCCESS;
}
