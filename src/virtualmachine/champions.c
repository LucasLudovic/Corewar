/*
** EPITECH PROJECT, 2024
** Corewar
** File description:
** Retrieve the champions
*/

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <endian.h>
#include "virtualmachine/initialize_vm.h"
#include "my_macros.h"
#include "champions/champions.h"
#include "virtualmachine/set_load_address.h"
#include "op.h"
#include "my.h"

static
int retrieve_champion_header(cpu_t *vm, const size_t champion_number)
{
    header_t *buffer = NULL;
    champions_t *champions = vm->champions[champion_number];

    buffer = malloc(sizeof(header_t));
    if (buffer == NULL)
        return display_error("Unable to alloc header\n");
    fread(buffer, sizeof(header_t), 1, champions->file_stream);
    champions->header = buffer;
    champions->header->prog_size = htobe32(champions->header->prog_size);
    return SUCCESS;
}

static
int retrieve_champion_body(cpu_t *vm, const size_t champion_number)
{
    uint8_t octet = 0;
    size_t memory_address = 0;
    champions_t *champion = vm->champions[champion_number];

    if (champion->file_stream == NULL)
        return display_error("Unable to access champion filestream\n");
    memory_address = champion->load_address;
    memory_address %= MEM_SIZE;
    while (fread(&octet, sizeof(uint8_t), 1, champion->file_stream) == 1) {
        memory_address += 1;
        memory_address %= MEM_SIZE;
        vm->memory[memory_address] = octet;
    }
    return SUCCESS;
}

static
int retrieve_single_champion(cpu_t *vm, const size_t champion_number)
{
    if (retrieve_champion_header(vm, champion_number) == FAILURE)
        return display_error("Unable to retrieve a chamion header\n");
    return SUCCESS;
}

int retrieve_champions_instructions(cpu_t *virtual_machine)
{
    if (virtual_machine == NULL)
        return display_error("Unable to retrieve the champions\n");
    for (size_t i = 0; i < virtual_machine->nb_champions &&
        virtual_machine->champions[i] != NULL; i += 1) {
        if (retrieve_single_champion(virtual_machine, i) == FAILURE)
            return display_error("Unable to retrieve one of the champions");
    }
    if (set_load_address(virtual_machine) == FAILURE)
        return display_error("Unable to load address\n");
    for (size_t i = 0; i < virtual_machine->nb_champions &&
        virtual_machine->champions[i] != NULL; i += 1) {
        if (retrieve_champion_body(virtual_machine, i) == FAILURE)
            return display_error("Unable to retrieve a champion body\n");
    }
    return SUCCESS;
}
