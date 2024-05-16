/*
** EPITECH PROJECT, 2024
** corewar
** File description:
** initializeVM.h
*/

#ifndef INITIALIZE_VM_H_
    #define INITIALIZE_VM_H_

    #include <stdint.h>
    #include "../op.h"
    #include "../champions/champions.h"
    #include "../my_macros.h"

typedef enum state {
    CPU_IDLE,
    CPU_RUNNING,
    CPU_HALTED
} cpu_state_t;

typedef struct cpu_s {
    uint8_t memory[MEM_SIZE];
    size_t init_champ;
    size_t nb_champions;
    champions_t **champions;
    cpu_state_t state;
    int nb_cycle;
    int dump;
    int cycle_max;
    int winner;
    char *winner_name;
} cpu_t;

int initialize_vm(cpu_t *cpu, char const *const *argv);
int retrieve_champions_instructions(cpu_t *virtual_machine);
int execute_arena(cpu_t *vm);

#endif
