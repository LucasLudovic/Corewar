/*
** EPITECH PROJECT, 2024
** corewar
** File description:
** opcode_0x06.c
*/

#include "champions/champions.h"
#include "my.h"
#include "op.h"
#include "virtualmachine/initialize_vm.h"
#include <stdint.h>

static
void make_operation_with_register(cpu_t *cpu, champions_t *champion)
{
    uint8_t first_param = 0;
    uint8_t second_param = 0;
    uint8_t third_param = 0;

    first_param = cpu->memory[(champion->program_counter + CODING_BYTE + 1)
        % MEM_SIZE];
    second_param = cpu->memory[(champion->program_counter +
        CODING_BYTE + 2) % MEM_SIZE];
    third_param = cpu->memory[(champion->program_counter +
        CODING_BYTE + 3) % MEM_SIZE];
    champion->registers[third_param] = champion->registers[first_param] &
        champion->registers[second_param];
}

static
void make_operation_with_register_and_direct(cpu_t *cpu, champions_t *champion)
{
    uint8_t first_param = 0;
    uint16_t second_param = 0;
    uint8_t third_param = 0;

    first_param = cpu->memory[(champion->program_counter + CODING_BYTE + 1)
        % MEM_SIZE];
    second_param = cpu->memory[(champion->program_counter + CODING_BYTE + 2)
        % MEM_SIZE];
    second_param <<= 2;
    second_param += cpu->memory[(champion->program_counter + CODING_BYTE + 3)
        % MEM_SIZE];
    third_param = cpu->memory[(champion->program_counter + CODING_BYTE + 4)
        % MEM_SIZE];
    champion->registers[third_param] = champion->registers[first_param]
        & second_param;
}

static
void make_operation_with_register_and_indirect(cpu_t *cpu,
    champions_t *champion)
{
    uint8_t first_param = 0;
    uint32_t second_param = 0;
    uint8_t third_param = 0;

    first_param = cpu->memory[(champion->program_counter + 2) % MEM_SIZE];
    second_param = cpu->memory[(champion->program_counter + CODING_BYTE + 2)
        % MEM_SIZE];
    second_param <<= 2;
    second_param += cpu->memory[(champion->program_counter + CODING_BYTE + 3)
        % MEM_SIZE];
    second_param <<= 2;
    second_param += cpu->memory[(champion->program_counter + CODING_BYTE + 4)
        % MEM_SIZE];
    second_param <<= 2;
    second_param += cpu->memory[(champion->program_counter + CODING_BYTE + 5)
        % MEM_SIZE];
    third_param = cpu->memory[(champion->program_counter + CODING_BYTE + 6)
        % MEM_SIZE];
    champion->registers[third_param] = champion->registers[first_param]
        & second_param;
}

static
void make_operation_with_direct_and_register(cpu_t *cpu, champions_t *champion)
{
    uint8_t first_param = 0;
    uint32_t second_param = 0;
    uint8_t third_param = 0;

    first_param = cpu->memory[(champion->program_counter + CODING_BYTE + 1)
        % MEM_SIZE];
    first_param <<= 2;
    first_param += cpu->memory[(champion->program_counter + CODING_BYTE + 2)
        % MEM_SIZE];
    second_param = cpu->memory[(champion->program_counter + CODING_BYTE + 3)
        % MEM_SIZE];
    third_param = cpu->memory[(champion->program_counter + CODING_BYTE + 4)
        % MEM_SIZE];
    champion->registers[third_param] = first_param
        & champion->registers[second_param];
}

static
void make_operation_with_direct_and_direct(cpu_t *cpu, champions_t *champion)
{
    uint8_t first_param = 0;
    uint32_t second_param = 0;
    uint8_t third_param = 0;

    first_param = cpu->memory[(champion->program_counter + CODING_BYTE + 1)
        % MEM_SIZE];
    first_param <<= 2;
    first_param += cpu->memory[(champion->program_counter + CODING_BYTE + 2)
        % MEM_SIZE];
    second_param = cpu->memory[(champion->program_counter + CODING_BYTE + 3)
        % MEM_SIZE];
    second_param <<= 2;
    second_param += cpu->memory[(champion->program_counter + CODING_BYTE + 4)
        % MEM_SIZE];
    third_param = cpu->memory[(champion->program_counter + CODING_BYTE + 5)
        % MEM_SIZE];
    champion->registers[third_param] = first_param & second_param;
}

static
void make_operation_with_direct_and_indirect(cpu_t *cpu, champions_t *champion)
{
    uint8_t first_param = 0;
    uint32_t second_param = 0;
    uint8_t third_param = 0;

    first_param = cpu->memory[(champion->program_counter + 2) % MEM_SIZE];
    first_param <<= 2;
    first_param += cpu->memory[(champion->program_counter + 3) % MEM_SIZE];
    second_param = cpu->memory[(champion->program_counter + 4) % MEM_SIZE];
    second_param <<= 2;
    second_param += cpu->memory[(champion->program_counter + 5) % MEM_SIZE];
    second_param <<= 2;
    second_param += cpu->memory[(champion->program_counter + 6) % MEM_SIZE];
    second_param <<= 2;
    second_param += cpu->memory[(champion->program_counter + 7) % MEM_SIZE];
    third_param = cpu->memory[(champion->program_counter + 8) % MEM_SIZE];
    champion->registers[third_param] = first_param & second_param;
}

static
void make_operation_with_indirect_and_register(cpu_t *cpu,
    champions_t *champion)
{
    uint8_t first_param = 0;
    uint32_t second_param = 0;
    uint8_t third_param = 0;

    first_param = cpu->memory[(champion->program_counter + 2) % MEM_SIZE];
    first_param <<= 2;
    first_param += cpu->memory[(champion->program_counter + 3) % MEM_SIZE];
    first_param <<= 2;
    first_param += cpu->memory[(champion->program_counter + 4) % MEM_SIZE];
    first_param <<= 2;
    first_param += cpu->memory[(champion->program_counter + 5) % MEM_SIZE];
    second_param = cpu->memory[(champion->program_counter + 6) % MEM_SIZE];
    third_param = cpu->memory[(champion->program_counter + 7) % MEM_SIZE];
    champion->registers[third_param] = first_param &
        champion->registers[second_param];
}

static
void make_operation_with_indirect_and_direct(cpu_t *cpu,
    champions_t *champion)
{
    uint8_t first_param = 0;
    uint32_t second_param = 0;
    uint8_t third_param = 0;

    first_param = cpu->memory[(champion->program_counter + 2) % MEM_SIZE];
    first_param <<= 2;
    first_param += cpu->memory[(champion->program_counter + 3) % MEM_SIZE];
    first_param <<= 2;
    first_param += cpu->memory[(champion->program_counter + 4) % MEM_SIZE];
    first_param <<= 2;
    first_param += cpu->memory[(champion->program_counter + 5) % MEM_SIZE];
    second_param = cpu->memory[(champion->program_counter + 6) % MEM_SIZE];
    second_param <<= 2;
    second_param += cpu->memory[(champion->program_counter + 7) % MEM_SIZE];
    third_param = cpu->memory[(champion->program_counter + 8) % MEM_SIZE];
    champion->registers[third_param] = first_param
        & champion->registers[second_param];
}

static
void make_operation_with_indirect_and_indirect(cpu_t *cpu,
    champions_t *champion)
{
    uint8_t first_param = 0;
    uint32_t second_param = 0;
    uint8_t third_param = 0;

    first_param = cpu->memory[(champion->program_counter + 2) % MEM_SIZE];
    first_param <<= 2;
    first_param += cpu->memory[(champion->program_counter + 3) % MEM_SIZE];
    first_param <<= 2;
    first_param += cpu->memory[(champion->program_counter + 4) % MEM_SIZE];
    first_param <<= 2;
    first_param += cpu->memory[(champion->program_counter + 5) % MEM_SIZE];
    second_param = cpu->memory[(champion->program_counter + 6) % MEM_SIZE];
    second_param <<= 2;
    second_param += cpu->memory[(champion->program_counter + 7) % MEM_SIZE];
    second_param <<= 2;
    second_param += cpu->memory[(champion->program_counter + 8) % MEM_SIZE];
    second_param <<= 2;
    second_param += cpu->memory[(champion->program_counter + 9) % MEM_SIZE];
    third_param = cpu->memory[(champion->program_counter + 10) % MEM_SIZE];
    champion->registers[third_param] = first_param
        & champion->registers[second_param];
}

static
void make_operation(cpu_t *cpu, champions_t *champion, int coding_byte)
{
    if ((coding_byte >> 6 & T_REG) && ((coding_byte << 2) >> 6 & T_REG))
        make_operation_with_register(cpu, champion);
    if ((coding_byte >> 6 & T_REG) && ((coding_byte << 2) >> 6) & T_DIR)
        make_operation_with_register_and_direct(cpu, champion);
    if ((coding_byte >> 6 & T_REG) && ((coding_byte << 2) >> 6) & T_IND)
        make_operation_with_register_and_indirect(cpu, champion);
    if ((coding_byte >> 6 & T_DIR) && ((coding_byte << 2) >> 6) & T_REG)
        make_operation_with_direct_and_register(cpu, champion);
    if ((coding_byte >> 6 & T_DIR) && ((coding_byte << 2) >> 6) & T_DIR)
        make_operation_with_direct_and_direct(cpu, champion);
    if ((coding_byte >> 6 & T_DIR) && ((coding_byte << 2) >> 6) & T_IND)
        make_operation_with_direct_and_indirect(cpu, champion);
    if ((coding_byte >> 6 & T_IND) && ((coding_byte << 2) >> 6) & T_REG)
        make_operation_with_indirect_and_register(cpu, champion);
    if ((coding_byte >> 6 & T_IND) && ((coding_byte << 2) >> 6) & T_DIR)
        make_operation_with_indirect_and_direct(cpu, champion);
    if ((coding_byte >> 6 & T_IND) && ((coding_byte << 2) >> 6) & T_DIR)
        make_operation_with_indirect_and_indirect(cpu, champion);
}

int execute_opcode_and(cpu_t *cpu, champions_t *champion)
{
    int coding_byte = cpu->memory[champion->program_counter + 1];

    if (cpu == NULL || champion == NULL)
        return display_error("Unable to retrieve structs for st\n");
    champion->index = false;
    make_operation(cpu, champion, coding_byte);
    return SUCCESS;
}
