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
    printf("div = %d\n", div);
    div /= nb_champions;
    for (size_t i = 0; cpu->champions[i] != NULL; i += 1) {
        cpu->champions[i]->load_address = load_address;
        load_address += cpu->champions[i]->header->prog_size;
        load_address += div;
    }
    for (size_t i = 0; cpu->champions[i] != NULL; i += 1) {
        printf("champion n°%ld = %d\n", i, cpu->champions[i]->load_address);
    }
    printf("memory = %d\n", MEM_SIZE);
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
void handle_big_space(cpu_t *cpu, int first_part, int first_space,
    int nb_champions)
{
    int div = first_space;
    int load_address = first_part;

    for (size_t i = 0; cpu->champions[i] != NULL; i += 1) {
        if (cpu->champions[i]->pre_load == TRUE)
            continue;
        div -= cpu->champions[i]->header->prog_size;
    }
    div /= (nb_champions - 1);
    for (size_t i = 0; cpu->champions[i] != NULL; i += 1) {
        if (cpu->champions[i]->pre_load == TRUE)
            continue;
        load_address += cpu->champions[i]->header->prog_size;
        load_address += div;
        if (load_address > MEM_SIZE)
            load_address %= MEM_SIZE;
        cpu->champions[i]->load_address = load_address;
        cpu->champions[i]->pre_load = TRUE;
    }
}

static
void handle_each_side(cpu_t *cpu, int first_part, int first_space)
{
    int load_address = 0;

    for (size_t i = 0; cpu->champions[i] != NULL; i += 1) {
        if (cpu->champions[i]->pre_load == TRUE)
            continue;
        load_address = first_part + (first_space / 2);
        if (load_address > MEM_SIZE)
            load_address %= MEM_SIZE;
        cpu->champions[i]->load_address = load_address;
        cpu->champions[i]->pre_load = TRUE;
        break;
    }
}

static
void handle_each_side_second(cpu_t *cpu, int second_part, int second_space)
{
    int load_address = 0;

    for (size_t i = 0; cpu->champions[i] != NULL; i += 1) {
        if (cpu->champions[i]->pre_load == TRUE)
            continue;
        load_address = second_part + (second_space / 2);
        if (load_address > MEM_SIZE)
            load_address %= MEM_SIZE;
        cpu->champions[i]->load_address = load_address;
        cpu->champions[i]->pre_load = TRUE;
        break;
    }
}

static
void find_distance(cpu_t *cpu, int first_part, int second_part,
    int nb_champions)
{
    size_t first_space = 0;
    size_t second_space = 0;

    for (int i = first_part; i != second_part; i += 1) {
        if (i > MEM_SIZE)
            i = 1;
        first_space += 1;
    }
    for (int i = second_part; i != first_part; i += 1) {
        if (i > MEM_SIZE)
            i = 1;
        second_space += 1;
    }
    if (first_space / 3 >= second_space)
        handle_big_space(cpu, first_part, first_space, nb_champions);
    if (second_space / 3 >= first_space)
        handle_big_space(cpu, second_part, second_space, nb_champions);
    handle_each_side(cpu, first_part, first_space);
    handle_each_side_second(cpu, second_part, second_space);
}

static
int set_load_with_two_preload(cpu_t *cpu, int nb_champions)
{
    int first_part = 0;
    int second_part = 0;

    for (size_t i = 0; cpu->champions[i] != NULL; i += 1) {
        if (cpu->champions[i]->pre_load == TRUE && first_part == 0) {
            first_part = cpu->champions[i]->load_address;
            continue;
        }
        if (cpu->champions[i]->pre_load == TRUE && first_part != 0) {
            second_part = cpu->champions[i]->load_address;
            break;
        }
    }
    find_distance(cpu, first_part, second_part, nb_champions);
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
        printf("load address n°%ld = %d\n", i, cpu->champions[i]->load_address);
    }
    return SUCCESS;
}
