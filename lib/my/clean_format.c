/*
** EPITECH PROJECT, 2024
** lib
** File description:
** string_format
*/

#include <stdio.h>
#include <stdlib.h>

static int is_clean_char(char *clean, char c)
{
    if (clean == NULL)
        return -1;
    for (size_t i = 0; clean[i] != '\0'; i += 1) {
        if (c == clean[i])
            return 1;
    }
    return 0;
}

char *clean_format(char *str, char *clean)
{
    char *new_str = NULL;
    size_t len = 0;
    size_t j = 0;

    if (str == NULL)
        return NULL;
    if (clean == NULL)
        return str;
    for (size_t i = 0; str[i] != '\0'; i += 1) {
        if (is_clean_char(clean, str[i]) == 0)
            len += 1;
    }
    new_str = malloc(sizeof(char) * len + 1);
    new_str[len] = '\0';
    for (size_t i = 0; str[i] != '\0'; i += 1)
        if (is_clean_char(clean, str[i]) == 0) {
            new_str[j] = str[i];
            j += 1;
        }
    return new_str;
}
