CC		= gcc
CFLAGS	= -g -Wall -Werror -Wextra
RM		= rm -f

NAME	= pipex

LIBFT_DIR =	./libft
LIBFT =		$(LIBFT_DIR)/libft.a

INCLUDE	= pipex.h
SRC_FILES	= 	pipex.c  free.c
SRC    =   $(SRC_FILES)
OBJ		= $(SRC:.c=.o)


.PHONY: 	all clean fclean re

all: 	$(NAME)

$(NAME):	$(LIBFT) $(OBJ)  $(INCLUDE)
			$(CC) $(CFLAGS) $(OBJ) $(LIBFT) -o $(NAME)

$(LIBFT):
			$(MAKE) -C $(LIBFT_DIR)

%.o:%.c		
			$(CC) $(CFLAGS) -c $< -o $@

clean:
			$(MAKE) -C $(LIBFT_DIR) clean
			$(RM) $(OBJ)

fclean: 	clean
			$(MAKE) -C $(LIBFT_DIR) fclean
			$(RM) $(NAME)

re: 		fclean all
