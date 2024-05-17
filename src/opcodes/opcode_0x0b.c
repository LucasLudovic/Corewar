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

static
int retrieve_address(cpu_t *cpu, champions_t *champion,
    int *address, int byte_read)
{
    size_t second_param = 0;
    size_t third_param = 0;
    int address_to_modify = 0;
    int previous_byte_read = 0;

    byte_read = retrieve_second_parameter(cpu, champion,
        &second_param, byte_read);
    if (byte_read == 3) {
        if (second_param >= REG_NUMBER) {
            champion->alive = false;
            return FAILURE;
        }
        address_to_modify += champion->registers[second_param];
    }
    else
        address_to_modify += second_param;
    previous_byte_read = byte_read;
    byte_read = retrieve_third_parameter(cpu, champion,
        &third_param, byte_read);
    if (byte_read == previous_byte_read + 1) {
        if (third_param >= REG_NUMBER) {
            champion->alive = false;
            return FAILURE;
        }
        address_to_modify += champion->registers[third_param];
    }
    else
        address_to_modify += third_param;
    *address = address_to_modify;
    return byte_read;
}

int execute_opcode_sti(cpu_t *cpu, champions_t *champion)
{
    size_t first_param = 0;
    int byte_read = 1;
    int address_to_modify = 0;

    champion->index = true;
    if (cpu == NULL || champion == NULL)
        return display_error("Unable to retrieve structs for sti\n");
    byte_read = retrieve_first_parameter(cpu, champion, &first_param,
        byte_read);
    if (first_param >= REG_NUMBER) {
        champion->alive = false;
        return FAILURE;
    }
    byte_read = retrieve_address(cpu, champion, &address_to_modify, byte_read);
    cpu->memory[(champion->program_counter + (address_to_modify % IDX_MOD))
        % MEM_SIZE] = champion->registers[first_param];
    champion->program_counter = (champion->program_counter + (byte_read + 1))
        % MEM_SIZE;
    return SUCCESS;
}
