/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_db.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rle <rle@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/04 18:52:02 by mburson           #+#    #+#             */
/*   Updated: 2017/05/05 22:12:06 by rle              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_DB_H
# define FT_DB_H

# include <stdbool.h>
# include <string.h>
# include <unistd.h>
# include <vector.h>
# include <libft.h>
# include <stdint.h>
# include <stdlib.h>
# include <stdio.h>
# include <errno.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>

# define DEFAULT_FILE "default.db"
# define INPUT_PROMPT "\e[33mft_db ->\e[39m "
# define DEBUG 0

# define COMMAND_COUNT 9

enum			e_ctype
{
	NONE = 0,
	CLOSE = 1,
	GET = 2,
	SET = 3,
	ADD = 4,
	DELETE = 5,
	FILTER = 6,
	GETALL = 7,
	CLEAR = 8
};

struct			s_command
{
	enum e_ctype	type;
	uint64_t		field;
	void			*value;
};

struct			s_field
{
	void		*name;
	uint64_t	name_size;
	uint64_t	offset;
	uint64_t	value_size;
};

struct			s_header
{
	uint64_t		entry_size;
	uint64_t		field_count;
	struct s_field	*fields;
};

extern char		*g_error;

int				print_entries(struct s_header *header, t_vec *entries);
int				get_next_line(char **next_line);
int				save_db(struct s_header *header, t_vec *db, int argc,
					char **argv);

/*
** load_db/
*/
int				load_db(struct s_header *header, t_vec *db, int argc,
					char **argv);
int				new_db(struct s_header *header, t_vec *db);
int				open_db(struct s_header *header, t_vec *db, int fd);

/*
** get_command/
*/
int			get_next_command(struct s_command *command, 
					struct s_header *header);
int			get_command_type(char *line, 
					struct s_command *command);
int			get_field(char *line, struct s_header *header, 
					uint64_t *field_type);
int			get_value(char *line, struct s_command *command,
					struct s_header *header);
uint64_t	value_size(char *line);
int			compare_string(char *big, char *little);
/*
** execute_command/
*/
int				execute_command(struct s_header *header,
					struct s_command *command, t_vec *entries, t_vec *db);
int				add(struct s_header *header, struct s_command *cmd,
					t_vec *entries, t_vec *db);
int				clear(struct s_header *header, struct s_command *cmd,
					t_vec *entries, t_vec *db);
int				delete(struct s_header *header, struct s_command *cmd,
					t_vec *entries, t_vec *db);
int				filter(struct s_header *header, struct s_command *cmd,
					t_vec *entries, t_vec *db);
int				get(struct s_header *header, struct s_command *cmd,
					t_vec *entries, t_vec *db);
int				getall(struct s_header *header, struct s_command *cmd,
					t_vec *entries, t_vec *db);
int				set(struct s_header *header, struct s_command *cmd,
					t_vec *entries, t_vec *db);

/*
** debug.c
*/
void			debug_print(struct s_header *header, t_vec *db,
					struct s_command *command, t_vec *held_entries);
void			debug_entries(t_vec *db, t_vec *entries);
void			debug_command(struct s_command *command);
void			debug_db(t_vec *db);
void			debug_header(struct s_header *header);

#endif
