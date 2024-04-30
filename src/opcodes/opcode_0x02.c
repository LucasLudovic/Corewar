/*
** EPITECH PROJECT, 2024
** Corewar
** File description:
** P1 = P2, update the carry
*/

#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include "virtualmachine/initialize_vm.h"
#include "corewar.h"
#include "my.h"
#include "my_macros.h"

int execute_opcode_ld(cpu_t *cpu, champions_t *champion)
{
    int coding_byte = 0;
    uint32_t first_param = 0;
    uint8_t second_param = 0;

    if (cpu == NULL || champion == NULL)
        return display_error("Unable to retrieve structs for ld\n");
    if (champion->file_stream == NULL)
        return display_error("Unable to access champion file\n");
    if (fread(&coding_byte, sizeof(uint8_t), 1, champion->file_stream) <= 0)
        return display_error("Unable to retrieve coding byte in opcode ld\n");
    if ((coding_byte >> 6 & T_DIR || coding_byte >> 6 & T_IND) == FALSE)
        return display_error("Wrong type for the first parameter\n");
    if (coding_byte >> 6 & T_DIR) {
        if (fread(&first_param, sizeof(int), 1, champion->file_stream) <= 0)
            return display_error("Unable to get the first param for ld\n");
        champion->registers[second_param] = first_param;
    }
    if (coding_byte >> 6 & T_IND)
        champion->registers[second_param] = cpu->memory[first_param];
    return SUCCESS;
}
