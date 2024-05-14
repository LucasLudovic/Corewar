/*
** EPITECH PROJECT, 2024
** Corewar
** File description:
** Table to contain every opcode instructions
*/

#include "champions/champions.h"
#include "opcodes/opcodes.h"

int (*instruction_table[])(cpu_t *cpu, champions_t *champion) = {
    &execute_opcode_live,
    &execute_opcode_ld,
    &execute_opcode_st,
    &execute_opcode_add,
    &execute_opcode_sub,
    NULL
};
