/*
** EPITECH PROJECT, 2024
** Corewar
** File description:
** Indicate that the player is alive
*/

#include <stddef.h>
#include <stdio.h>
#include "my.h"
#include "champions/champions.h"
#include "virtualmachine/initialize_vm.h"
#include "my_macros.h"

int execute_opcode_live(cpu_t *cpu, champions_t *champion)
{
    if (cpu == NULL || champion == NULL || champion->name == NULL)
        return display_error("Unable to retrieve structs in opcode live\n");
    my_putstr("The player ");
    my_put_nbr(champion->player_number);
    my_putchar('(');
    my_putstr(champion->name);
    my_putstr(") is alive.\n");
    champion->program_counter += 5;
    return SUCCESS;
}
