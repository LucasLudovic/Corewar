/*
** EPITECH PROJECT, 2024
** 42sh
** File description:
** Execute the virtual machine
*/

#include "virtualmachine/dump.h"
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
        if (cpu->champions[i]->alive == false)
            continue;
        if (execute_single_champion(cpu, cpu->champions[i]) == FAILURE)
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

static
void set_champion_live(cpu_t *cpu)
{
    for (size_t i = 0; cpu->champions[i] != NULL; i += 1) {
        cpu->champions[i]->has_lived = false;
    }
}

static
void kill_champion(cpu_t *cpu)
{
    for (size_t i = 0; cpu->champions[i] != NULL; i += 1) {
        if (cpu->champions[i]->has_lived == false)
            cpu->champions[i]->alive = false;
    }
}

static
void stop_program(cpu_t *cpu)
{
    if (cpu->nb_cycle >= cpu->cycle_max) {
        kill_champion(cpu);
        set_champion_live(cpu);
        cpu->nb_cycle = 0;
    }
    if (cpu->cycle_max <= 1)
        cpu->state = CPU_HALTED;
}

int execute_arena(cpu_t *cpu)
{
    if (cpu == NULL)
        return display_error("Unable to access cpu informations\n");
    cpu->cycle_max = CYCLE_TO_DIE;
    retrieve_champions_first_instructions(cpu);
    while (cpu->state != CPU_HALTED) {
        if (check_premature_end(cpu) == SUCCESS)
            break;
        execute_champions(cpu);
        cpu->nb_cycle += 1;
        if (cpu->nbr_live >= 40) {
            cpu->nbr_live = 0;
            cpu->cycle_max -= CYCLE_DELTA;
        }
        stop_program(cpu);
    }
    return SUCCESS;
}
