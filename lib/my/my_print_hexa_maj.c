/*
** EPITECH PROJECT, 2023
** my_print_hexa
** File description:
** convert an unsigned int into an hexa
*/

#include <stdio.h>
#include <stdarg.h>
#include "my.h"

static
int my_put_hexa_maj(unsigned int nb)
{
    unsigned int counter = 0;

    if (nb < 16) {
        if (nb < 10)
            my_putchar(nb + 48);
        if (nb >= 10 && nb < 16)
            my_putchar(nb + 55);
    } else {
        counter += my_put_hexa_maj(nb / 16);
        if (nb % 16 < 10)
            my_putchar(nb % 16 + 48);
        if ((nb % 16 >= 10) && (nb % 16 < 16))
            my_putchar(nb % 16 + 55);
    }
    counter += 1;
    return counter;
}

int my_print_hexa_maj(unsigned number)
{
    return my_put_hexa_maj(number);
}
