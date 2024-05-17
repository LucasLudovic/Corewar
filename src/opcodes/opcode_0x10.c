/*
** EPITECH PROJECT, 2024
** Corewar
** File description:
** Instructions for opcode aff
*/

#include "op.h"
#include "opcodes/opcodes.h"
#include "virtualmachine/initialize_vm.h"
#include "champions/champions.h"
#include "my.h"

int execute_opcode_aff(cpu_t *cpu, champions_t *champion)
{
    size_t first_parameter = 0;
    int byte_read = 0;

    if (cpu == NULL || champion == NULL)
        return display_error("Unable to retrieve structs in opcode aff\n");
    byte_read = retrieve_first_parameter(cpu, champion, &first_parameter, 1);
    if (first_parameter >= REG_SIZE) {
        champion->alive = false;
        return SUCCESS;
    }
    my_putchar(champion->registers[first_parameter] % 256);
    champion->program_counter += byte_read + 1;
    champion->program_counter %= MEM_SIZE;
    return SUCCESS;
}
