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

    if (coding_byte >> 6 & T_DIR)
        if (fread(&first_param, DIR_SIZE, 1, champion->file_stream) <= 0)
            return display_error("Unable to get the first DIR param for ld\n");
    if (coding_byte >> 6 & T_IND) {
        if (fread(&first_param, IND_SIZE, 1, champion->file_stream) <= 0)
            return display_error("Unable to get the first IND param for ld\n");
        if (first_param >= MEM_SIZE)
            return display_error("First param too big for ld\n");
        first_param = *((uint32_t *)(&(cpu->memory[first_param
            + champion->program_counter])));
    }
    if (fread(&second_param, REG_SIZE, 1, champion->file_stream) <= 0
        || second_param >= REG_NUMBER)
        return display_error("Second param not valid for ld\n");
    champion->registers[second_param] = champion->program_counter;
    champion->registers[second_param] += (first_param % IDX_MOD);
    return SUCCESS;
}

int execute_opcode_ld(cpu_t *cpu, champions_t *champion)
{
    uint8_t coding_byte = 0;

    if (cpu == NULL || champion == NULL)
        return display_error("Unable to retrieve structs for ld\n");
    if (champion->file_stream == NULL)
        return display_error("Unable to access champion file\n");
    if (fread(&coding_byte, sizeof(uint8_t), 1, champion->file_stream) <= 0)
        return display_error("Unable to retrieve coding byte in opcode ld\n");
    if (((coding_byte >> 6 & T_DIR || coding_byte >> 6 & T_IND)
        && (coding_byte << 2 >> 6 & T_REG)) == FALSE)
        return display_error("Wrong type for the first parameter\n");
    if (update_register(cpu, champion, coding_byte) != SUCCESS)
        return FAILURE;
    return SUCCESS;
}
