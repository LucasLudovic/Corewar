/*
** EPITECH PROJECT, 2024
** Corewar
** File description:
** P1 = P2, update the carry
*/

#include <stddef.h>
#include "virtualmachine/initialize_vm.h"
#include "corewar.h"
#include "my.h"
#include "my_macros.h"

int execute_opcode_ld(cpu_t *cpu, champions_t *champion)
{
    if (cpu == NULL || champion == NULL)
        return display_error("Unable to retrieve structs for ld\n");
    return SUCCESS;
}
