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

typedef enum state {
    CPU_IDLE,
    CPU_RUNNING,
    CPU_HALTED
} CPU_state_t;

typedef struct CPU {
    uint8_t registers[REG_SIZE];
    uint64_t program_counter;
    uint8_t memory[MEM_SIZE];
    champions_t *champions;
    CPU_state_t state;
} CPU_t;

#endif
