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

OBJ	=	$(SRC:.c=.o)

NAME	=	corewar

CC	=	gcc -g

CFLAGS	=	-W -Wall -Wextra -Wpedantic

CPPFLAGS	=	-I include

LDFLAGS	=	-L lib -lmy

all:	$(NAME)

$(NAME):	$(OBJ)
	@make -C lib/my
	@make clean -C lib/my
	$(CC) -o $(NAME) $(OBJ) $(CFLAGS) $(LDFLAGS) $(CPPFLAGS)

clean:
	@rm -f $(OBJ)

fclean:	clean
	@make fclean -C lib/my
	@make fclean -C tests/
	@find .. -name *.gcno -delete
	@find .. -name *.gcda -delete
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
