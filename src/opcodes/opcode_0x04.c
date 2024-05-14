/*
** EPITECH PROJECT, 2024
** Corewar
** File description:
** Instructions for opcode add
*/

#include <stdint.h>
#include "op.h"
#include "virtualmachine/initialize_vm.h"
#include "my.h"
#include "my_macros.h"

int execute_opcode_add(cpu_t *cpu, champions_t *champion)
{
    uint32_t *registers = champion->registers;
    size_t current_counter = 0;
    int first_parameter = 0;
    int second_parameter = 0;
    int third_parameter = 0;

    if (cpu == NULL || champion == NULL)
        return display_error("Unable to retrieve structs for add\n");
    current_counter = (champion->program_counter + CODING_BYTE + 1) % MEM_SIZE;
    first_parameter = cpu->memory[current_counter];
    current_counter += (current_counter + 1) % MEM_SIZE;
    second_parameter = cpu->memory[current_counter];
    current_counter += (current_counter + 1) % MEM_SIZE;
    third_parameter = cpu->memory[current_counter];
    registers[third_parameter] =
        registers[first_parameter] + registers[second_parameter];
    champion->carry = !champion->carry;
    return SUCCESS;
}
