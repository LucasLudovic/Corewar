/*
** EPITECH PROJECT, 2024
** Corewar
** File description:
** Instructions
*/

#ifndef INSTRUCTIONS_H_
    #define INSTRUCTIONS_H_
    #include "../virtualmachine/initialize_vm.h"

extern int (*instruction_table[])(cpu_t *cpu, champions_t *champion);

int retrieve_instruction(cpu_t *cpu, champions_t *champion);
int execute_instruction(cpu_t *cpu, champions_t *champion);

#endif
