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
void store_value(cpu_t *cpu, champions_t *champion, uint8_t coding_byte)
{
    uint32_t first_param = 0;
    uint32_t second_param = 0;

    first_param = cpu->memory[(champion->program_counter + 2) % MEM_SIZE];
    if ((coding_byte << 2) >> 6 & T_REG) {
        second_param = cpu->memory[(champion->program_counter + 6) % MEM_SIZE];
        champion->registers[second_param] = champion->registers[first_param];
    }
    else {
        second_param = cpu->memory[(champion->program_counter) % MEM_SIZE];
        cpu->memory[(champion->program_counter + second_param) % IDX_MOD] = champion->registers[first_param]; 
    }

}

int execute_opcode_st(cpu_t *cpu, champions_t *champion)
{
    uint8_t coding_byte = cpu->memory[champion->program_counter + 1];

    if (cpu == NULL || champion == NULL)
        return display_error("Unable to retrieve structs for st\n");
    store_value(cpu, champion, coding_byte);
    return SUCCESS;
}
