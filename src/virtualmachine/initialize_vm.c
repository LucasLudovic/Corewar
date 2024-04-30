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

static int check_champions(cpu_t *cpu, char const *const *argv, size_t *i)
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
    cpu->champions->name = my_strdup(argv[*i]);
    if (argv[*i + 1] != NULL)
        cpu->champions->next = malloc(sizeof(champions_t));
    cpu->champions = cpu->champions->next;
    return SUCCESS;
}

static int retrieve_champion(cpu_t *cpu, char const *const *argv, size_t *i)
{
    if (my_strcmp(argv[*i], "-a") == 0)
        if (check_load_address(cpu->champions, argv, i) == FAILURE)
            return FAILURE;
    if (check_champions(cpu, argv, i) == FAILURE)
        return FAILURE;
    return SUCCESS;
}

int initialize_vm(cpu_t *cpu, char const *const *argv)
{
    champions_t *head = NULL;

    if (argv == NULL)
        return FAILURE;
    cpu->champions = malloc(sizeof(champions_t));
    if (cpu->champions == NULL)
        return FAILURE;
    head = cpu->champions;
    for (size_t i = 1; argv[i] != NULL; i += 1) {
        if (retrieve_champion(cpu, argv, &i) == FAILURE)
            return FAILURE;
    }
    cpu->champions = head;
    return SUCCESS;
}
