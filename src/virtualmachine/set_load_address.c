/*
** EPITECH PROJECT, 2024
** corewar
** File description:
** set_load_address
*/

#include "champions/champions.h"
#include "my.h"
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
    for (size_t i = 0; cpu->champions[i] != NULL; i += 1)
        if (cpu->champions[i]->pre_load == TRUE)
            return TRUE;
    return FALSE;
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
int check_load_address(cpu_t *cpu)
{
    size_t nb_champions = count_champions(cpu);

    printf("LOAD with %ld champions\n", nb_champions);
    if (check_preload_champion(cpu) == FALSE)
        if (normal_load(cpu, nb_champions) == FAILURE)
            return FAILURE;
    return SUCCESS;
}

int set_load_address(cpu_t *cpu)
{
    if (cpu == NULL)
        return FAILURE;
    if (check_load_address(cpu) == FAILURE)
        return FAILURE;
    return SUCCESS;
}
