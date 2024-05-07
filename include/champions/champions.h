/*
** EPITECH PROJECT, 2024
** corewar
** File description:
** champions.h
*/

#ifndef CHAMPIONS_H_
    #define CHAMPIONS_H_

    #include <stdint.h>
    #include "../op.h"

typedef struct champions {
    char *name;
    int nbr_cycles;
    uint32_t registers[REG_SIZE];
    uint64_t program_counter;
    int load_address;
    int play_number;
    int carry;
    int borrow;
} champions_t;

#endif
