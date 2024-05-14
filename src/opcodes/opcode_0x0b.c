/*
** EPITECH PROJECT, 2024
** Corewar
** File description:
** Instructions for opcode sti
*/

#include <stdint.h>
#include "my_macros.h"
#include "op.h"
#include "virtualmachine/initialize_vm.h"
#include "champions/champions.h"
#include "opcodes/opcodes.h"
#include "my.h"

int execute_opcode_sti(cpu_t *cpu, champions_t *champion)
{
    int first_param = 0;
    int second_param = 0;
    int third_param = 0;
    int byte_read = 0;

    if (cpu == NULL || champion == NULL)
        return display_error("Unable to retrieve structs for sti\n");
    byte_read = retrieve_first_parameter(cpu, champion, &first_param,
        byte_read);
    byte_read = retrieve_second_parameter(cpu, champion,
        &second_param, byte_read);
    byte_read = retrieve_third_parameter(cpu, champion,
        &third_param, byte_read);
    return SUCCESS;
}
