##
## EPITECH PROJECT, 2023
## MAKEFILE
## File description:
## Makefile for my lib
##

SRC	=	src/main.c
SRC	+=	src/corewar.c
SRC	+=	src/op.c
SRC	+=	src/virtualmachine/initialize_vm.c
SRC	+=	src/virtualmachine/champions.c
SRC	+=	src/virtualmachine/virtual_machine.c
SRC	+=	src/virtualmachine/set_load_address.c
SRC	+=	src/instructions/instructions.c
SRC	+=	src/opcodes/opcode.c
SRC	+=	src/opcodes/opcode_0x01.c
SRC	+=	src/opcodes/opcode_0x02.c
SRC	+=	src/opcodes/opcode_0x03.c
SRC	+=	src/opcodes/opcode_0x04.c
SRC	+=	src/opcodes/opcode_0x05.c
SRC	+=	src/opcodes/opcode_0x06.c
SRC	+=	src/opcodes/opcode_0x07.c
SRC	+=	src/opcodes/opcode_0x08.c
SRC	+=	src/opcodes/opcode_0x09.c
SRC	+=	src/opcodes/opcode_0x0a.c
SRC	+=	src/opcodes/opcode_0x0b.c
SRC	+=	src/opcodes/opcode_0x0c.c
SRC	+=	src/opcodes/opcode_0x0d.c
SRC	+=	src/opcodes/opcode_0x0e.c
SRC	+=	src/opcodes/opcode_0x0f.c
SRC	+=	src/opcodes/opcode_0x10.c
SRC	+=	src/virtualmachine/dump.c
SRC	+=	src/virtualmachine/set_load_address_with_preload.c

OBJ	=	$(SRC:.c=.o)

NAME	=	corewar

CC	=	gcc -g

CFLAGS	=	-W -Wall -Wextra -Wpedantic

CPPFLAGS	=	-I include

LDFLAGS	=	-L lib -lmy	-lmy_alloc

all:	$(NAME)

$(NAME):	$(OBJ)
	@make -C lib/my
	@make clean -C lib/my
	@make -C lib/my_alloc
	@make clean -C lib/my_alloc
	$(CC) -o $(NAME) $(OBJ) $(CFLAGS) $(LDFLAGS) $(CPPFLAGS)

clean:
	@rm -f $(OBJ)

fclean:	clean
	@make fclean -C lib/my
	@make fclean -C lib/my_alloc
	@make fclean -C tests/
	@rm -f $(NAME)

re: fclean all

debug:	$(OBJ)
	@make -C lib/my
	@make clean -C lib/my
	@$(CC) -g3 -o $(NAME) $(OBJ) $(LDFLAGS) $(CPPFLAGS)

tests_run:	re
	@make re -C tests/
	@make clean -C tests/
	./unit_tests

.PHONY:	clean fclean re all tests_run
