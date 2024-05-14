/*
** EPITECH PROJECT, 2024
** corewar
** File description:
** set_load_address
*/

#include "champions/champions.h"
#include "my.h"
#include "my_macros.h"
#include "op.h"
#include "virtualmachine/initialize_vm.h"
#include "virtualmachine/set_load_with_two_preload.h"
#include <stdlib.h>

static
int count_champions(cpu_t *cpu)
{
    size_t nb_champions = 0;
    size_t i = 0;

    while (cpu->champions[i] != NULL) {
        i += 1;
        nb_champions += 1;
    }
    return nb_champions;
}

static
int check_preload_champion(cpu_t *cpu)
{
    size_t nb_preload = 0;

    for (size_t i = 0; cpu->champions[i] != NULL; i += 1)
        if (cpu->champions[i]->pre_load == TRUE)
            nb_preload += 1;
    return nb_preload;
}

static
int normal_load(cpu_t *cpu, size_t nb_champions)
{
    int div = MEM_SIZE;
    int load_address = 0;

    for (size_t i = 0; cpu->champions[i] != NULL; i += 1) {
        div -= cpu->champions[i]->header->prog_size;
    }
    div /= nb_champions;
    for (size_t i = 0; cpu->champions[i] != NULL; i += 1) {
        cpu->champions[i]->load_address = load_address;
        load_address += cpu->champions[i]->header->prog_size;
        load_address += div;
    }
    return SUCCESS;
}

static
int set_load_with_one_preload(cpu_t *cpu, size_t nb_champions)
{
    int div = MEM_SIZE;
    int load_address = 0;

    for (size_t i = 0; cpu->champions[i] != NULL; i += 1)
        if (cpu->champions[i]->pre_load == TRUE)
            load_address = cpu->champions[i]->load_address;
    for (size_t i = 0; cpu->champions[i] != NULL; i += 1)
        div -= cpu->champions[i]->header->prog_size;
    div /= nb_champions;
    for (size_t i = 0; cpu->champions[i] != NULL; i += 1) {
        if (cpu->champions[i]->pre_load == TRUE)
            continue;
        load_address += cpu->champions[i]->header->prog_size;
        load_address += div;
        if (load_address > MEM_SIZE)
            load_address %= MEM_SIZE;
        cpu->champions[i]->load_address = load_address;
    }
    return SUCCESS;
}

static
void retrieve_last_load_address(cpu_t *cpu, int part[3], int space[3])
{
    int load_address = 0;

    if (space[0] > space[1] && space[0] > space[2])
        load_address = part[0] + (space[0] / 2);
    if (space[1] > space[0] && space[1] > space[2])
        load_address = part[1] + (space[1] / 2);
    if (space[2] > space[0] && space[2] > space[1])
        load_address = part[2] + (space[2] / 2);
    if (part[0] == part[1] && part[0] == part[2])
        load_address = part[0] + (MEM_SIZE / 2);
    if (load_address > MEM_SIZE)
        load_address %= MEM_SIZE;
    for (size_t i = 0; cpu->champions[i] != NULL; i += 1) {
        if (cpu->champions[i]->pre_load == TRUE)
            continue;
        cpu->champions[i]->load_address = load_address;
        cpu->champions[i]->pre_load = TRUE;
    }
}

static
void find_biggest_space(cpu_t *cpu, int part[3])
{
    int space[3] = {0, 0, 0};

    for (int i = part[0]; i != part[1] && i != part[2]; i += 1) {
        if (i > MEM_SIZE)
            i = -1;
        space[0] += 1;
    }
    for (int i = part[1]; i != part[2] && i != part[0]; i += 1) {
        if (i > MEM_SIZE)
            i = -1;
        space[1] += 1;
    }
    for (int i = part[2]; i != part[0] && i != part[1]; i += 1) {
        if (i > MEM_SIZE)
            i = -1;
        space[2] += 1;
    }
    retrieve_last_load_address(cpu, part, space);
}

static
int set_load_with_three_preload(cpu_t *cpu, int nb_champions)
{
    int part[3] = {0, 0, 0};

    if (nb_champions == 3)
        return SUCCESS;
    for (size_t i = 0; cpu->champions[i] != NULL; i += 1) {
        if (cpu->champions[i]->pre_load == TRUE && part[0] == 0) {
            part[0] = cpu->champions[i]->load_address;
            continue;
        }
        if (cpu->champions[i]->pre_load == TRUE && part[0] != 0 &&
            part[1] == 0) {
            part[1] = cpu->champions[i]->load_address;
            continue;
        }
        if (cpu->champions[i]->pre_load == TRUE && part[0] != 0 &&
            part[1] != 0 && part[2] == 0)
            part[2] = cpu->champions[i]->load_address;
    }
    find_biggest_space(cpu, part);
    return SUCCESS;
}

static
int check_load_address(cpu_t *cpu)
{
    size_t nb_champions = count_champions(cpu);
    size_t nb_preload = check_preload_champion(cpu);

    printf("LOAD with %ld champions\n", nb_champions);
    if (nb_preload == 0)
        if (normal_load(cpu, nb_champions) == FAILURE)
            return FAILURE;
    if (nb_preload == 1)
        if (set_load_with_one_preload(cpu, nb_champions) == FAILURE)
            return FAILURE;
    if (nb_preload == 2)
        if (set_load_with_two_preload(cpu, nb_champions) == FAILURE)
            return FAILURE;
    if (nb_preload == 3)
        if (set_load_with_three_preload(cpu, nb_champions) == FAILURE)
            return FAILURE;
    return SUCCESS;
}

int set_load_address(cpu_t *cpu)
{
    if (cpu == NULL)
        return FAILURE;
    if (check_load_address(cpu) == FAILURE)
        return FAILURE;
    for (size_t i = 0; cpu->champions[i] != NULL; i += 1) {
        cpu->champions[i]->program_counter = cpu->champions[i]->load_address;
        cpu->champions[i]->instructions =
            cpu->memory[cpu->champions[i]->program_counter];
        printf("load address n°%ld = %d\n", i,
            cpu->champions[i]->load_address);
    }
    return SUCCESS;
}
