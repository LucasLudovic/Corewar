/*
** EPITECH PROJECT, 2024
** Corewar
** File description:
** Header for the opcodes
*/

#ifndef OPCODES_H_
    #define OPCODES_H_
    #include "../virtualmachine/initialize_vm.h"

extern int (*instruction[])(cpu_t *cpu, champions_t *champion);

int retrieve_first_parameter(cpu_t *cpu, champions_t *champion,
    int *first_parameter, int byte_read);
int retrieve_second_parameter(cpu_t *cpu, champions_t *champion,
    int *first_parameter, int byte_read);
int retrieve_third_parameter(cpu_t *cpu, champions_t *champion,
    int *first_parameter, int byte_read);
int execute_opcode_live(cpu_t *cpu, champions_t *champion);
int execute_opcode_ld(cpu_t *cpu, champions_t *champion);
int execute_opcode_st(cpu_t *cpu, champions_t *champion);
int execute_opcode_add(cpu_t *cpu, champions_t *champion);
int execute_opcode_sub(cpu_t *cpu, champions_t *champion);
int execute_opcode_ldd(cpu_t *cpu, champions_t *champion);

#endif
