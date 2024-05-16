/*
** EPITECH PROJECT, 2024
** corewar
** File description:
** opcode_0x0c
*/

#include <stdlib.h>
#include <endian.h>
#include "champions/champions.h"
#include "instructions/instructions.h"
#include "my_macros.h"
#include "op.h"
#include "my_alloc.h"
#include "virtualmachine/initialize_vm.h"

static
void copy_champion(cpu_t *cpu, champions_t *copy, champions_t *last_champion)
{
    copy->header = malloc(sizeof(header_t));
    copy->header = last_champion->header;
    copy->alive = last_champion->alive;
    copy->carry = last_champion->carry;
    copy->index = last_champion->index;
    copy->borrow = last_champion->borrow;
    copy->pre_load = last_champion->pre_load;
    for (size_t i = 0; i < 16; i += 1)
        copy->registers[i] = last_champion->registers[i];
    copy->file_stream = last_champion->file_stream;
    retrieve_instruction(cpu, copy);
    copy->player_number = last_champion->player_number;
    copy->previous_cycle = last_champion->previous_cycle;
}

int execute_opcode_fork(cpu_t *cpu, champions_t *champion)
{
    size_t parameter = cpu->memory[(champion->program_counter + 1) % MEM_SIZE];
    char *copy = malloc(sizeof(char) * champion->header->prog_size);

    if (copy == NULL)
        return FAILURE;
    parameter <<= 8;
    parameter += cpu->memory[(champion->program_counter + 2) % MEM_SIZE];
    for (int i = 0; i < champion->header->prog_size; i += 1) {
        copy[i] = cpu->memory[(champion->load_address + i) % MEM_SIZE];
    }
    for (int i = 0; i < champion->header->prog_size; i += 1)
        cpu->memory[(champion->program_counter + parameter + i) % IDX_MOD] =
            copy[i];
    free(copy);
    cpu->champions = my_realloc(cpu->champions, (cpu->nb_champions + 2) *
        sizeof(champions_t *), (cpu->nb_champions + 1) * sizeof(champions_t *));
    printf("nb champ = %ld\n", cpu->nb_champions);
    cpu->champions[cpu->nb_champions] = malloc(sizeof(champions_t));
    copy_champion(cpu, cpu->champions[cpu->nb_champions], champion);
    cpu->champions[cpu->nb_champions]->load_address = (champion->program_counter + parameter) % IDX_MOD;
    printf("name = %s\n", champion->header->prog_name);
    printf("first load address = %ld\n", champion->program_counter);
    printf("param = %lu\n", parameter);
    printf("load address = %d\n", cpu->champions[cpu->nb_champions]->load_address);
    cpu->champions[cpu->nb_champions]->program_counter = cpu->champions[cpu->nb_champions]->load_address;
    cpu->champions[cpu->nb_champions + 1] = NULL;
    cpu->nb_champions += 1;
    champion->program_counter = (champion->program_counter + 3)
        % MEM_SIZE;
    return SUCCESS;
}
