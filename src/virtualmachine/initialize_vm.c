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
#include "op.h"
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
    if (champion->load_address > MEM_SIZE)
        champion->load_address %= MEM_SIZE;
    champion->pre_load = TRUE;
    *i += 2;
    return SUCCESS;
}

static
int check_champions(champions_t *champion, char const *const *argv,
    size_t *i, size_t *champion_number)
{
    ssize_t len = my_strlen(argv[*i]);

    if (len <= 4)
        return 1;
    if (argv[*i][len - 1] != 'r')
        return display_error("champion must be .cor file\n");
    if (argv[*i][len - 2] != 'o')
        return display_error("champion must be .cor file\n");
    if (argv[*i][len - 3] != 'c')
        return display_error("champion must be .cor file\n");
    if (argv[*i][len - 4] != '.')
        return display_error("champion must be .cor file\n");
    champion->name = my_strdup(argv[*i]);
    champion->file_stream = fopen(argv[*i], "rb");
    champion->alive = TRUE;
    if (champion->file_stream == NULL)
        return display_error("Can't open file\n");
    *i += 1;
    *champion_number += 1;
    return SUCCESS;
}

static
int check_prog_number(champions_t *champions, char const *const *argv,
    size_t *i)
{
    if (argv[*i + 1] == NULL)
        return display_error("No argument after -n\n");
    if (my_str_isnum(argv[*i + 1]) == 0)
        return display_error("argument after -n must be a number\n");
    champions->program_counter = my_getnbr(argv[*i + 1]);
    *i += 2;
    return SUCCESS;
}

static
int retrieve_champion(cpu_t *cpu, char const *const *argv,
    size_t *i, size_t *champion_number)
{
    if (my_strcmp(argv[*i], "-a") == 0)
        if (check_load_address(cpu->champions[*champion_number], argv, i) ==
            FAILURE)
            return FAILURE;
    if (my_strcmp(argv[*i], "-n") == 0)
        if (check_prog_number(cpu->champions[*champion_number], argv, i) ==
            FAILURE)
            return FAILURE;
    if (my_strcmp(argv[*i], "-dump") == 0) {
        cpu->dump = my_getnbr(argv[*i + 1]);
        *i += 2;
        return SUCCESS;
    }
    if (check_champions(cpu->champions[*champion_number], argv, i,
        champion_number) == FAILURE)
        return FAILURE;
    return SUCCESS;
}

static
int initialize_champions(cpu_t *cpu)
{
    cpu->dump = -1;
    cpu->champions = malloc(sizeof(champions_t) * NB_CHAMPIONS + 1);
    for (size_t i = 0; i < NB_CHAMPIONS; i += 1) {
        cpu->champions[i] = malloc(sizeof(champions_t));
        if (cpu->champions[i] == NULL)
            return display_error("Unable to alloc memory to champion");
        cpu->champions[i]->header = NULL;
        cpu->champions[i]->name = NULL;
        cpu->champions[i]->file_stream = NULL;
        cpu->champions[i]->carry = 0;
        cpu->champions[i]->borrow = 0;
        cpu->champions[i]->nbr_cycles = 0;
        cpu->champions[i]->player_number = 0;
        cpu->champions[i]->pre_load = FALSE;
        cpu->champions[i]->load_address = 0;
        cpu->champions[i]->program_counter = 0;
        cpu->nb_champions += 1;
    }
    cpu->champions[4] = NULL;
    return SUCCESS;
}

static
void destroy_unused_champion(champions_t **champions)
{
    if (*champions == NULL)
        return;
    if ((*champions)->name != NULL) {
        free((*champions)->name);
        (*champions)->name = NULL;
    }
    if ((*champions)->file_stream != NULL)
        fclose((*champions)->file_stream);
    if (champions != NULL) {
        free(*champions);
        *champions = NULL;
    }
}

int initialize_vm(cpu_t *cpu, char const *const *argv)
{
    size_t champion_number = 0;
    size_t i = 1;

    if (cpu == NULL)
        return FAILURE;
    if (initialize_champions(cpu) == FAILURE)
        return FAILURE;
    if (argv == NULL)
        return FAILURE;
    while (argv[i] != NULL)
        if (retrieve_champion(cpu, argv, &i, &champion_number) == FAILURE)
            return FAILURE;
    cpu->winner = -1;
    if (champion_number <= 2)
        destroy_unused_champion(&cpu->champions[2]);
    if (champion_number <= 3)
        destroy_unused_champion(&cpu->champions[3]);
    return SUCCESS;
}
