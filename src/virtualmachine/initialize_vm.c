/*
** EPITECH PROJECT, 2024
** corewar
** File description:
** initializeVM.c
*/

#include "virtualmachine/initialize_vm.h"
#include "champions/champions.h"
#include "my_macros.h"
#include "my.h"
#include <stdio.h>
#include <stdlib.h>

static
int check_load_address(champions_t *champion, char const *const *argv,
    size_t *i)
{
    if (argv[*i + 1] == NULL)
        return display_error("No argument after -a\n");
    if (my_str_isnum(argv[*i + 1]) == 0)
        return display_error("argument after -a must be a number\n");
    champion->load_address = my_getnbr(argv[*i + 1]);
    *i += 1;
    return SUCCESS;
}

static int check_champions(champions_t *champion, char const *const *argv, size_t *i, size_t *champion_number)
{
    size_t len = my_strlen(argv[*i]);

    if (len <= 4)
        return 1;
    if (argv[*i][len - 1] != 'r')
        return display_error("champion must be .cor file");
    if (argv[*i][len - 2] != 'o')
        return display_error("champion must be .cor file");
    if (argv[*i][len - 3] != 'c')
        return display_error("champion must be .cor file");
    if (argv[*i][len - 4] != '.')
        return display_error("champion must be .cor file");
    champion->name = my_strdup(argv[*i]);
    *champion_number += 1;
    return SUCCESS;
}

static
int check_prog_number(cpu_t *cpu, char const *const *argv, size_t *i)
{
    if (argv[*i + 1] == NULL)
        return display_error("No argument after -n\n");
    if (my_str_isnum(argv[*i + 1]) == 0)
        return display_error("argument after -n must be a number\n");
    return SUCCESS;
}

static int retrieve_champion(cpu_t *cpu, char const *const *argv, size_t *i, size_t *champion_number)
{
    if (my_strcmp(argv[*i], "-a") == 0)
        if (check_load_address(cpu->champions[*champion_number], argv, i) == FAILURE)
            return FAILURE;
    if (my_strcmp(argv[*i], "-n") == 0)
        if (check_prog_number(cpu, argv, i) == FAILURE)
            return FAILURE;
    if (check_champions(cpu->champions[*champion_number], argv, i, champion_number) == FAILURE)
        return FAILURE;
    return SUCCESS;
}

int initialize_vm(cpu_t *cpu, char const *const *argv)
{
    size_t champion_number = 0;

    if (cpu == NULL)
        return FAILURE;
    for (size_t i = 0; i < NB_CHAMPIONS; i += 1) {
        cpu->champions[i] = malloc(sizeof(champions_t));
        cpu->champions[i]->name = NULL;
        cpu->champions[i]->file_stream = NULL;
        cpu->champions[i]->carry = 0;
        cpu->champions[i]->borrow = 0;
        cpu->champions[i]->nbr_cycles = 0;
        cpu->champions[i]->play_number = 0;
        cpu->champions[i]->load_address = 0;
        cpu->champions[i]->program_counter = 0;
    }
    if (argv == NULL)
        return FAILURE;
    for (size_t i = 1; argv[i] != NULL; i += 1) {
        if (retrieve_champion(cpu, argv, &i, &champion_number) == FAILURE)
            return FAILURE;
    }
    return SUCCESS;
}
