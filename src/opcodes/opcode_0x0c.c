/*
** EPITECH PROJECT, 2024
** corewar
** File description:
** opcode_0x0c
*/

#include <stdlib.h>
#include "champions/champions.h"
#include "my_macros.h"
#include "instructions/instructions.h"
#include "my.h"
#include "my_alloc.h"
#include "op.h"
#include "virtualmachine/initialize_vm.h"

static
void add_new_champion(cpu_t *cpu, champions_t *champion, size_t parameter)
{
    champions_t *new_champion = cpu->champions[cpu->nb_champions];

    new_champion->header = malloc(sizeof(header_t));
    new_champion->header = my_memcpy(new_champion->header, champion->header,
        sizeof(header_t));
    new_champion->alive = champion->alive;
    new_champion->carry = champion->carry;
    new_champion->index = champion->index;
    new_champion->pre_load = champion->pre_load;
    new_champion->nbr_cycles = 0;
    new_champion->nb_set = champion->nb_set;
    new_champion->has_lived = false;
    for (size_t i = 0; i < REG_NUMBER; i += 1)
        new_champion->registers[i] = champion->registers[i];
    new_champion->player_number = champion->player_number;
    new_champion->load_address = ((champion->program_counter + parameter)
        % IDX_MOD) % MEM_SIZE;
    new_champion->program_counter = new_champion->load_address;
    retrieve_instruction(cpu, new_champion);
}

static
void fork_champion(cpu_t *cpu, champions_t *champion)
{
    size_t parameter = cpu->memory[(champion->program_counter + 1) % MEM_SIZE];

    parameter <<= 8;
    parameter += cpu->memory[(champion->program_counter + 2) % MEM_SIZE];
    for (int i = 0; i < champion->header->prog_size; i += 1)
        cpu->memory[(champion->program_counter + (parameter + i) % IDX_MOD) %
        MEM_SIZE] = cpu->memory[(champion->load_address + i) % MEM_SIZE];
    cpu->champions = my_realloc(cpu->champions, (cpu->nb_champions + 2) *
        sizeof(champions_t *), (cpu->nb_champions + 1) *
        sizeof(champions_t *));
    cpu->champions[cpu->nb_champions] = malloc(sizeof(champions_t));
    add_new_champion(cpu, champion, parameter);
    cpu->nb_champions += 1;
    cpu->champions[cpu->nb_champions] = NULL;
    champion->program_counter = (champion->program_counter + 3) % MEM_SIZE;
}

int execute_opcode_fork(cpu_t *cpu, champions_t *champion)
{
    if (cpu == NULL || champion == NULL)
        return display_error("Unable to retrieve structs for fork\n");
    fork_champion(cpu, champion);
    return SUCCESS;
}
