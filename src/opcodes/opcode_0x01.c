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
    size_t player_number = 0;

    if (cpu == NULL || champion == NULL)
        return display_error("Unable to retrieve structs in opcode live\n");
    if (champion->name == NULL)
        return display_error("Unable to retrieve champion name for live\n");
    if (champion->file_stream == NULL)
        return display_error("Unable to access the champion file stream\n");
    if (fread(&player_number, sizeof(int), 1, champion->file_stream) <= 0)
        return display_error("You arrived to the end of the file for live\n");
    if (player_number <= 0)
        return display_error("Couldn't retrieve the right player's number\n");
    my_putstr("The player ");
    my_put_nbr(player_number);
    my_putchar('(');
    my_putstr(champion->name);
    my_putstr(") is alive.\n");
    return SUCCESS;
}
