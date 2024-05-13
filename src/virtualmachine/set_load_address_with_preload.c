/*
** EPITECH PROJECT, 2024
** corewar
** File description:
** set_load_address_with_preload.c
*/

#include "virtualmachine/set_load_address.h"

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
