/*
** EPITECH PROJECT, 2023
** MY_STRLEN
** File description:
** Return the size of a string
*/

#include <stddef.h>

int my_strlen(char const *str)
{
    int i = 0;

    if (str == NULL)
        return -1;
    for (; str[i] != '\0'; i += 1);
    return i;
}
