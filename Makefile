# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rle <rle@student.42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/02/23 19:31:26 by mburson           #+#    #+#              #
#    Updated: 2017/04/30 16:22:07 by rle              ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_db

LIBFT = ./libft/libft.a
LIBFT_DIR = ./libft

SRC = \
	$(addprefix src/, \
		execute_command.c \
		ft_db.c \
		get_command.c \
		get_next_line.c \
		print_entries.c \
		save_db.c \
		$(addprefix load_db/, \
			load_db.c \
			new_db.c \
			open_db.c \
		) \
		$(addprefix vector/, \
			vec_add.c \
			vec_del.c \
			vec_get.c \
			vec_init.c \
			vec_realloc.c \
			vec_rm.c \
		) \
	)

OBJ = $(SRC:.c=.o)

HEADERS = -I ./include -I ./libft

CFLAGS = -Wall -Wextra -Werror -g

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT)
	gcc $(CFLAGS) -o $@ $^

%.o: %.c
	gcc $(CFLAGS) $(HEADERS) -c -o $@ $<

$(LIBFT): force
	$(MAKE) -C $(LIBFT_DIR)

$(OBJ): ./include/ft_db.h

force:
	@true

clean:
	rm -f $(OBJ)
	$(MAKE) -C $(LIBFT_DIR) fclean
fclean: clean
	rm -f $(NAME)
re: fclean all

.PHONY: all clean fclean re
