/*
** EPITECH PROJECT, 2024
** corewar
** File description:
** champions.h
*/

#ifndef CHAMPIONS_H_
    #define CHAMPIONS_H_
    #include <stdint.h>
    #include <stdbool.h>
    #include <stdio.h>
    #include "../op.h"

typedef struct champions {
    char *name;
    FILE *file_stream;
    uint32_t registers[REG_NUMBER];
    uint64_t program_counter;
    header_t *header;
    bool alive;
    int pre_load;
    int load_address;
    int player_number;
    int carry;
    int borrow;
    size_t nbr_cycles;
    size_t previous_cycle;
    uint8_t instructions;
} champions_t;

#endif
