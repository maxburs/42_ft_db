# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rle <rle@student.42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/02/23 19:31:26 by mburson           #+#    #+#              #
#    Updated: 2017/05/05 22:11:27 by rle              ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_db

LIBFT = ./libft/libft.a
LIBFT_DIR = ./libft

SRC = \
	$(addprefix src/, \
		ft_db.c \
		get_next_line.c \
		print_entries.c \
		save_db.c \
		$(addprefix load_db/, \
			load_db.c \
			new_db.c \
			open_db.c \
		) \
		$(addprefix get_command/, \
			get_command.c \
			get_type.c \
			get_field.c \
			get_value.c \
		) \
		$(addprefix execute_command/, \
			execute_command.c \
			add.c \
			clear.c \
			delete.c \
			filter.c \
			get.c \
			getall.c \
			set.c \
		) \
		$(addprefix vector/, \
			vec_add.c \
			vec_del.c \
			vec_get.c \
			vec_init.c \
			vec_realloc.c \
			vec_rm.c \
			vec_set.c \
		) \
	)

OBJ = $(SRC:.c=.o)

HEADERS = -I ./include -I ./libft

CFLAGS = -Wall -Wextra -Werror

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
