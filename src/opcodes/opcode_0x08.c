/*
** EPITECH PROJECT, 2024
** corewar
** File description:
** opcode_0x08
*/

#include "champions/champions.h"
#include "my.h"
#include "op.h"
#include "virtualmachine/initialize_vm.h"
#include "opcodes/opcodes.h"

static
void first_param_register(champions_t *champion, size_t param[3], int bytes[3])
{
    if (bytes[1] == 2 && bytes[2] == 3)
        champion->registers[param[2]] = champion->registers[param[0]] ^
            champion->registers[param[1]];
    if (bytes[1] == 2 && bytes[2] == 4)
        champion->registers[param[2]] = champion->registers[param[0]] ^
            param[1];
    if (bytes[1] == 2 && bytes[2] == 6)
        champion->registers[param[2]] = champion->registers[param[0]] ^
            param[1];
}

static
void first_param_indirect(champions_t *champion, size_t param[3], int bytes[3])
{
    if (bytes[1] == 3 && bytes[2] == 4)
        champion->registers[param[2]] = param[0] ^
            champion->registers[param[1]];
    if (bytes[1] == 3 && bytes[2] == 5)
        champion->registers[param[2]] = champion->registers[param[0]] ^
            param[1];
    if (bytes[1] == 3 && bytes[2] == 7)
        champion->registers[param[2]] = param[0] ^ param[1];
}

static
void first_param_direct(champions_t *champion, size_t param[3], int bytes[3])
{
    if (bytes[1] == 5 && bytes[2] == 6)
        champion->registers[param[2]] = param[0] ^
            champion->registers[param[1]];
    if (bytes[1] == 5 && bytes[2] == 7)
        champion->registers[param[2]] = champion->registers[param[0]] ^
            param[1];
    if (bytes[1] == 5 && bytes[2] == 9)
        champion->registers[param[2]] = param[0] ^ param[1];
}

static
void make_operation(champions_t *champion, size_t param[3], int bytes[3])
{
    first_param_register(champion, param, bytes);
    first_param_direct(champion, param, bytes);
    first_param_indirect(champion, param, bytes);
}

static
void retrieve_param(cpu_t *cpu, champions_t *champion)
{
    size_t param[3] = {0, 0, 0};
    int bytes[3] = {1, 0, 0};

    bytes[0] = retrieve_first_parameter(cpu, champion, &param[0], bytes[0]);
    bytes[1] = bytes[0];
    bytes[0] = retrieve_second_parameter(cpu, champion, &param[1], bytes[0]);
    bytes[2] = bytes[0];
    bytes[0] = retrieve_third_parameter(cpu, champion, &param[2], bytes[0]);
    make_operation(champion, param, bytes);
    champion->program_counter = (champion->program_counter + (bytes[0] + 1))
        % MEM_SIZE;
}

int execute_opcode_xor(cpu_t *cpu, champions_t *champion)
{
    if (cpu == NULL || champion == NULL)
        return display_error("Unable to retrieve structs for or\n");
    champion->index = false;
    retrieve_param(cpu, champion);
    champion->carry = !champion->carry;
    return SUCCESS;
}
