/*
** EPITECH PROJECT, 2024
** Corewar
** File description:
** Retrieve the champions
*/

#include <stdint.h>
#include <stdio.h>
#include "my_macros.h"
#include "virtualmachine/initialize_vm.h"
#include "champions/champions.h"
#include "op.h"
#include "my.h"

static
int retrieve_champion_header(UNUSED cpu_t *vm, UNUSED const size_t champion_number)
{
    return SUCCESS;
}

static
int retrieve_champion_body(cpu_t *vm, const size_t champion_number)
{
    uint8_t octet = 0;
    size_t memory_address = 0;
    champions_t *champion = vm->champions[champion_number];

    while (fread(&octet, sizeof(uint8_t), 1, champion->file_stream) == 0) {
        memory_address = (octet + (vm->nb_champions - champion_number)) % MEM_SIZE;
        vm->memory[memory_address] = octet;
    }
    return SUCCESS;
}

static
int retrieve_single_champion(cpu_t *vm, const size_t champion_number)
{
    if (retrieve_champion_header(vm, champion_number) == FAILURE)
        return display_error("Unable to retrieve a chamion header\n");
    if (retrieve_champion_body(vm, champion_number) == FAILURE)
        return display_error("Unable to retrieve a champion body\n");
    return SUCCESS;
}

int retrieve_champions(cpu_t *virtual_machine)
{
    if (virtual_machine == NULL || virtual_machine->champions == NULL)
        return display_error("Unable to retrieve the champions\n");
    for (size_t i = 0; i < NB_CHAMPIONS &&
        virtual_machine->champions[i] != NULL; i += 1) {
        if (retrieve_single_champion(virtual_machine, i) == FAILURE)
            return display_error("Unable to retrieve one of the champions");
    }
    return SUCCESS;
}
