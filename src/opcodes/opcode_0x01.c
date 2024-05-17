/*
** EPITECH PROJECT, 2024
** Corewar
** File description:
** Indicate that the player is alive
*/

#include <stddef.h>
#include <stdio.h>
#include "my.h"
#include "opcodes/opcodes.h"
#include "champions/champions.h"
#include "op.h"
#include "virtualmachine/initialize_vm.h"
#include "my_macros.h"

static
void display_alive(cpu_t *cpu, champions_t *champion,
    unsigned first_parameter)
{
    if (champion->nb_set == 0)
        champion->player_number = first_parameter;
    cpu->winner = champion->player_number;
    my_putstr("The player ");
    my_put_nbr(champion->player_number);
    my_putchar('(');
    my_putstr(champion->header->prog_name);
    my_putstr(") is alive.\n");
}

int execute_opcode_live(cpu_t *cpu, champions_t *champion)
{
    unsigned first_parameter = 0;

    if (cpu == NULL || champion == NULL)
        return display_error("Unable to retrieve structs in opcode live\n");
    first_parameter = cpu->memory[(champion->program_counter + 1) % MEM_SIZE];
    first_parameter <<= 8;
    first_parameter += cpu->memory[(champion->program_counter + 2) % MEM_SIZE];
    first_parameter <<= 8;
    first_parameter += cpu->memory[(champion->program_counter + 3) % MEM_SIZE];
    first_parameter <<= 8;
    first_parameter += cpu->memory[(champion->program_counter + 4) % MEM_SIZE];
    cpu->nbr_live += 1;
    champion->has_lived = true;
    display_alive(cpu, champion, first_parameter);
    champion->program_counter += 5;
    champion->program_counter %= MEM_SIZE;
    cpu->winner = champion->player_number;
    cpu->winner_name = champion->header->prog_name;
    return SUCCESS;
}
