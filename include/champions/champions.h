/*
** EPITECH PROJECT, 2024
** corewar
** File description:
** champions.h
*/

#ifndef CHAMPIONS_H_
    #define CHAMPIONS_H_

typedef struct champions {
    char *name;
    int nbr_cycles;
    struct champions *next;
} champions_t;

#endif
