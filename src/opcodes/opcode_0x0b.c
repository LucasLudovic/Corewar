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
int execute_register(champions_t *champion, int *address_to_modify,
    int byte_read, size_t second_param)
{
    if (byte_read == 3) {
        if (second_param >= REG_NUMBER) {
            champion->alive = false;
            return FAILURE;
        }
        *address_to_modify += champion->registers[second_param];
    }
    return SUCCESS;
}

static
int execute_third_param(champions_t *champion, int *address_to_modify,
    size_t third_param, int byte_read[2])
{
    if (byte_read[0] == byte_read[1] + 1) {
        if (third_param >= REG_NUMBER) {
            champion->alive = false;
            return FAILURE;
        }
        *address_to_modify += champion->registers[third_param];
    }
    return SUCCESS;
}

static
int update_address(int *address, int *new_byte, int address_to_modify)
{
    *address = address_to_modify;
    return new_byte[0];
}

static
int retrieve_address(cpu_t *cpu, champions_t *champion,
    int *address, int byte_read)
{
    size_t second_param = 0;
    size_t third_param = 0;
    int address_to_modify = 0;
    int new_byte[2] = { byte_read, 0 };

    new_byte[0] = retrieve_second_parameter(cpu, champion,
        &second_param, byte_read);
    if (execute_register(champion, &address_to_modify, new_byte[0],
        second_param)
        == FAILURE)
        return FAILURE;
    if (new_byte[0] != 3)
        address_to_modify += second_param;
    new_byte[1] = new_byte[0];
    new_byte[0] = retrieve_third_parameter(cpu, champion, &third_param,
        new_byte[0]);
    execute_third_param(champion, &address_to_modify, third_param, new_byte);
    if (new_byte[0] != new_byte[1] + 1)
        address_to_modify += third_param;
    return update_address(address, new_byte, address_to_modify);
}

static
int check_param(champions_t *champion, size_t first_param)
{
    if (first_param >= REG_NUMBER) {
        champion->alive = false;
        return FAILURE;
    }
    return SUCCESS;
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
    if (check_param(champion, first_param) == FAILURE)
        return FAILURE;
    byte_read = retrieve_address(cpu, champion, &address_to_modify, byte_read);
    if (champion->alive == false)
        return FAILURE;
    cpu->memory[(champion->program_counter + (address_to_modify % IDX_MOD))
        % MEM_SIZE] = champion->registers[first_param];
    champion->program_counter =
        (champion->program_counter + (byte_read + 1)) % MEM_SIZE;
    return SUCCESS;
}
