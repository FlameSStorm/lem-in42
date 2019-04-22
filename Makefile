FLAGS = -Werror -Wall -Wextra

NAME = lem-in 

FILES = main.c \
		save_links.c \
		paths_tools.c \
		save_paths.c \
		release_ants.c \
		tools.c \
		help_save_paths.c \
		tools_deluxe.c \
		tools_extra.c

OBJSRC = $(FILES:.c=.o)

OBJ = $(addprefix obj/, $(OBJSRC))

SRC = $(addprefix src/, $(FILES))

.PHONY: re all clean fclean
.NOTPARALLEL: re all clean fclean

all: $(NAME)

$(NAME):
	@make -C libft/
	@mkdir obj
	@gcc $(FLAGS) -c $(SRC) -I includes
	@mv *.o obj/
	@gcc -o $(NAME) $(FLAGS) $(OBJ) libft/libft.a -I includes 
	@echo "\033[32mCreated $(NAME) executable\033[0m"

clean:
	@/bin/rm -rf $(OBJ) obj
	@make -C libft/ clean
	@echo "\033[31mRemoved lem-in object files\033[0m"

fclean: clean
	@/bin/rm -rf $(NAME)
	@make -C libft/ fclean
	@echo "\033[31mRemoved lem-in executable\033[0m"

sex: all clean

re: fclean all
