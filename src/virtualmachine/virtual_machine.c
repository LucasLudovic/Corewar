/*
** EPITECH PROJECT, 2024
** 42sh
** File description:
** Execute the virtual machine
*/

#include <stdint.h>
#include "instructions/instructions.h"
#include "champions/champions.h"
#include "op.h"
#include "virtualmachine/initialize_vm.h"
#include "my_macros.h"
#include "my.h"

static
int execute_single_champion(cpu_t *cpu, champions_t *champion)
{
    if (champion->nbr_cycles == cpu->nb_cycle) {
        if (execute_instruction(cpu, champion) == FAILURE)
            return FAILURE;
        if (retrieve_instruction(cpu, champion) == FAILURE) {
            return FAILURE;
        }
    }
    return SUCCESS;
}

static
void execute_champions(cpu_t *cpu)
{
    for (size_t i = 0; cpu->champions[i] != NULL; i += 1) {
        if (cpu->champions[i]->alive == TRUE &&
            execute_single_champion(cpu, cpu->champions[i]) == FAILURE)
            cpu->champions[i]->alive = FALSE;
    }
}

static
void retrieve_champions_first_instructions(cpu_t *cpu)
{
    for (size_t i = 0; cpu->champions[i] != NULL && i < NB_CHAMPIONS; i += 1) {
        if (retrieve_instruction(cpu, cpu->champions[i]) == FAILURE)
            cpu->champions[i]->alive = FALSE;
    }
}

static
void display_memory(cpu_t *cpu)
{
    for (size_t i = 0; i < MEM_SIZE; i += 1) {
        my_print_hexa_maj(cpu->memory[i]);
        if (i % 32 == 0 && i != 0)
            my_putchar('\n');
    }
    my_putchar('\n');
}

static
int dump_memory(cpu_t *cpu)
{
    if (cpu->dump != -1) {
        if (cpu->dump == 0) {
            display_memory(cpu);
            return SUCCESS;
        }
        cpu->dump -= 1;
    }
    return FAILURE;
}

static
int is_last_champion_winner(cpu_t *cpu)
{
    for (size_t i = 0; cpu->champions[i] != NULL; i += 1) {
        if (cpu->champions[i]->alive == true &&
            my_strcmp(cpu->winner_name, cpu->champions[i]->header->prog_name)
            == 0)
            return true;
    }
    return false;
}

static
int get_alive_champions(cpu_t *cpu)
{
    int champion_alive = 0;

    for (size_t i = 0; cpu->champions[i] != NULL; i += 1) {
        if (cpu->champions[i]->alive == true)
            champion_alive += 1;
    }
    return champion_alive;
}

static
int check_premature_end(cpu_t *cpu)
{
    if (get_alive_champions(cpu) == 0)
        return SUCCESS;
    if (get_alive_champions(cpu) == 1 && is_last_champion_winner(cpu) == true)
        return SUCCESS;
    if (dump_memory(cpu) == SUCCESS)
        return SUCCESS;
    return FAILURE;
}

int execute_arena(cpu_t *cpu)
{
    cpu->cycle_max = CYCLE_TO_DIE;
    if (cpu == NULL)
        return display_error("Unable to access cpu informations\n");
    retrieve_champions_first_instructions(cpu);
    while (cpu->state != CPU_HALTED) {
        if (check_premature_end(cpu) == SUCCESS)
            break;
        execute_champions(cpu);
        if (cpu->nb_cycle >= cpu->cycle_max) {
            cpu->cycle_max -= CYCLE_DELTA;
            cpu->nb_cycle = 0;
        }
        if (cpu->cycle_max <= 0)
            cpu->state = CPU_HALTED;
        cpu->nb_cycle += 1;
    }
    return SUCCESS;
}
