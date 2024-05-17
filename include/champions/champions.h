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
    FILE *file_stream;
    uint32_t registers[REG_NUMBER];
    uint64_t program_counter;
    header_t *header;
    int pre_load;
    int load_address;
    int player_number;
    bool carry;
    bool has_lived;
    bool alive;
    bool index;
    bool nb_set;
    int nbr_cycles;
    uint8_t instructions;
} champions_t;

#endif
