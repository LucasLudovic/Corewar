/*
** EPITECH PROJECT, 2024
** Main
** File description:
** Main function for the Robot Factory
*/

#include <stddef.h>
#include "corewar.h"
#include "my.h"
#include "my_macros.h"

static
int display_help(void)
{
    my_putstr("USAGE\n");
    my_putstr("./asm file_name[.s]\n");
    my_putstr("DESCRIPTION\n");
    my_putstr("file_name file in assembly language to be converted into ");
    my_putstr("file_name.cor, an executable in the Virtual Machine.\n");
    return SUCCESS;
}

int main(const int argc, char const *const *const argv)
{
    if (argc != 2 || argv == NULL || argv[1] == NULL)
        return display_error("Arguments not valid !\n");
    if (my_strcmp(argv[1], "-h") == 0)
        return display_help();
    return execute_corewar();
}
