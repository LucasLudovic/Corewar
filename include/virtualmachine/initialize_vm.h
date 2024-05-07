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
    champions_t champions[NB_CHAMPIONS];
    cpu_state_t state;
} cpu_t;

int initialize_vm(cpu_t *cpu, char const *const *argv);

#endif
