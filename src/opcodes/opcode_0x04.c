/*
** EPITECH PROJECT, 2024
** Corewar
** File description:
** Instructions for opcode add
*/

#include <stdint.h>
#include "champions/champions.h"
#include "op.h"
#include "virtualmachine/initialize_vm.h"
#include "my.h"
#include "my_macros.h"

static
void update_champion(champions_t *champion, int first_param, int second_param)
{
    champion->carry = false;
    if (first_param + second_param == 0)
        champion->carry = true;
    champion->program_counter += CODING_BYTE + 3 + 1;
    champion->program_counter %= MEM_SIZE;
}

static
void check_params(champions_t *champion, size_t first_parameter,
    size_t second_parameter, size_t third_parameter)
{
    if (first_parameter >= REG_NUMBER || second_parameter >= REG_NUMBER ||
        third_parameter >= REG_NUMBER) {
        champion->alive = FALSE;
        return;
    }
    champion->registers[third_parameter] =
        champion->registers[first_parameter] +
        champion->registers[second_parameter];
}

int execute_opcode_add(cpu_t *cpu, champions_t *champion)
{
    size_t current_counter = 0;
    int first_parameter = 0;
    int second_parameter = 0;
    int third_parameter = 0;

    if (cpu == NULL || champion == NULL)
        return display_error("Unable to retrieve structs for add\n");
    champion->index = false;
    current_counter = (champion->program_counter + CODING_BYTE + 1) % MEM_SIZE;
    first_parameter = cpu->memory[current_counter];
    current_counter = (current_counter + 1) % MEM_SIZE;
    second_parameter = cpu->memory[current_counter];
    current_counter = (current_counter + 1) % MEM_SIZE;
    third_parameter = cpu->memory[current_counter];
    check_params(champion, first_parameter, second_parameter, third_parameter);
    update_champion(champion, first_parameter, second_parameter);
    return SUCCESS;
}
