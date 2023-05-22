NAME	= corruptor.a

SRCDIR = ./src/

SRC = $(shell find . -name "file_op.c" -o -name \
					"random_bit.c" -o -name "random_minus.c" -o -name \
					"buffer_shuffle.c" -o -type f)

CC = gcc
FLAGS = -Wall -Wextra -Werror -g

OBJ	= $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	@echo "Linking $@"
	@ar rcs $(NAME) $(OBJ)
	@echo "Done!"

%.o: %.c
	@echo "Compiling $<"
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -f $(OBJ) $(OBJB)

fclean: clean
	@rm -f $(NAME)

re: fclean all

maintest: all
	@echo "~~~ Testing with main function ~~~"
	@$(CC) $(SRC) Libft/libft.a main.c leakcheck.c $(FLAGS)
	@./a.out

maindebug: all
	@echo "~~~ Testing with main function ~~~"
	@$(CC) $(SRC) Libft/libft.a main.c -g $(FLAGS) -o prog
	@./prog

.PHONY: all clean fclean re test bonus maintest maindebug