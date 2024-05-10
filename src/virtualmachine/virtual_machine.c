/*
** EPITECH PROJECT, 2024
** 42sh
** File description:
** Execute the virtual machine
*/

#include "champions/champions.h"
#include "virtualmachine/initialize_vm.h"
#include "my_macros.h"
#include "my.h"
#include <stdint.h>

static
int retrieve_champions_header(cpu_t *cpu, champions_t *champion)
{
    return SUCCESS;
}

static
int execute_instruction(champions_t *champion)
{
    return SUCCESS;
}

static
int retrieve_next_instruction(cpu_t *cpu, champions_t *champion)
{
    uint8_t instructions = 0;

    if (fread(&instructions, sizeof(uint8_t), 1, champion->file_stream) == 0) {
        retrieve_champions_header(cpu, champion);
        if (fread(&instructions, sizeof(uint8_t), 1, champion->file_stream)
            <= 0)
            return display_error("Unable to retrieve next instruction\n");
    }
    return SUCCESS;
}

static
int execute_single_champion(cpu_t *cpu, champions_t *champion)
{
    if (champion->nbr_cycles == cpu->nb_cycle) {
        if (execute_instruction(champion) == FAILURE)
            return FAILURE;
        if (retrieve_next_instruction(cpu, champion) == FAILURE)
            return FAILURE;
    }
    return SUCCESS;
}

static
int execute_champions(cpu_t *cpu)
{
    for (size_t i = 0; cpu->champions[i] != NULL && i < NB_CHAMPIONS; i += 1) {
        if (execute_single_champion(cpu, cpu->champions[i]) == FAILURE)
            return FAILURE;
    }
    return SUCCESS;
}

int execute_virtual_machine(cpu_t *cpu)
{
    if (cpu == NULL)
        return display_error("Unable to access cpu informations\n");
    while (cpu->state != CPU_HALTED) {
        if (execute_champions(cpu) == FAILURE)
            return FAILURE;
        cpu->nb_cycle += 1;
    }
    return SUCCESS;
}
