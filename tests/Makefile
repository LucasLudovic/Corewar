##
## EPITECH PROJECT, 2023
## make create
## File description:
## make
##

SRC	=	../src/robot_factory.c
SRC	+=	test.c

OBJ	=	$(SRC:.c=.o)

NAME	=	unit_tests

CFLAGS	=	-W -Wall -Wextra
CFLAGS	+=	--coverage -lcriterion

CPPFLAGS	=	-I ../include/

LDFLAGS	=	-L ../lib/ -lmy

CC	=	gcc -g3

all:	$(NAME)

$(NAME)	:	$(OBJ)
	@	$(CC) -o $(NAME) $(OBJ) $(CFLAGS) $(CPPFLAGS) $(LDFLAGS)
	@	mv $(NAME) ../

clean:
	@	rm -f $(OBJ)
	@	rm -f ../*.o

fclean:	clean
	@	rm -f $(NAME)
	@	rm -f ../src/*.gcno
	@	rm -f ../src/*.gcda
	@	rm -f *.gcno
	@	rm -f *.gcda
	@	rm -f ../$(NAME)

re:	fclean all

.PHONY:	all clean fclean re
