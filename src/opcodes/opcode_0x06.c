/*
** EPITECH PROJECT, 2024
** corewar
** File description:
** opcode_0x06.c
*/

#include "my.h"
#include "virtualmachine/initialize_vm.h"

int execute_opcode_add(cpu_t *cpu, champions_t *champion)
{
    uint32_t *registers = champion->registers;
    size_t current_counter = 0;
    int first_parameter = 0;
    int second_parameter = 0;
    int third_parameter = 0;

    if (cpu == NULL || champion == NULL)
        return display_error("Unable to retrieve structs for sub\n");
    current_counter = (champion->program_counter + CODING_BYTE + 1) % MEM_SIZE;
    first_parameter = cpu->memory[current_counter];
    current_counter = (current_counter + 1) % MEM_SIZE;
    second_parameter = cpu->memory[current_counter];
    current_counter = (current_counter + 1) % MEM_SIZE;
    third_parameter = cpu->memory[current_counter];
    registers[third_parameter] =
        registers[first_parameter] + registers[second_parameter];
    champion->carry = !champion->carry;
    champion->program_counter += CODING_BYTE + 3 + 1;
    champion->program_counter %= MEM_SIZE;
    return SUCCESS;
}
