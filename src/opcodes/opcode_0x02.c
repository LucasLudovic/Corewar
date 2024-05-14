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
int update_register(cpu_t *cpu, champions_t *champion, uint8_t coding_byte)
{
    uint32_t first_param = 0;
    uint8_t second_param = 0;

    if (coding_byte >> 6 & T_DIR) {
        first_param = *((uint32_t *)(&(
        cpu->memory[(champion->program_counter + 2) % MEM_SIZE])));
        second_param = cpu->memory[(champion->program_counter + 6) % MEM_SIZE];
    }
    if (coding_byte >> 6 & T_IND) {
        first_param = *((uint16_t *)(&(
        cpu->memory[(champion->program_counter + 2) % MEM_SIZE])));
        first_param = *((uint16_t *)(&(cpu->memory[
        (champion->load_address + first_param) % MEM_SIZE])));
        second_param = cpu->memory[(champion->program_counter + 4) % MEM_SIZE];
    }
    champion->registers[second_param] = champion->program_counter;
    champion->registers[second_param] += (first_param % IDX_MOD);
    champion->carry = !champion->carry;
    return SUCCESS;
}

int execute_opcode_ld(cpu_t *cpu, champions_t *champion)
{
    uint8_t coding_byte = cpu->memory[champion->program_counter + 1];

    if (cpu == NULL || champion == NULL)
        return display_error("Unable to retrieve structs for ld\n");
    update_register(cpu, champion, coding_byte);
    return SUCCESS;
}
