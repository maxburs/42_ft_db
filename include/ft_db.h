/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_db.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rle <rle@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/04 18:52:02 by mburson           #+#    #+#             */
/*   Updated: 2017/05/03 16:32:15 by rle              ###   ########.fr       */
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

enum			e_ctype
{
	NONE = 0,
	CLOSE,
	GET,
	SET,
	ADD,
	DELETE,
	FILTER,
	SHOW,
	CLEAR
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

int				get_next_command(struct s_command *command,
					struct s_header *header); 
void			print_entries(size_t entry_size, t_vec *entries);
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
** execute_command/
*/
int				execute_command(struct s_header *header, struct s_command
					command, t_vec *entries, t_vec *db);
int				add(struct s_header *header, struct s_command cmd,
					t_vec *entries, t_vec *db);
int				clear(struct s_header *header, struct s_command cmd,
					t_vec *entries, t_vec *db);
int 			delete(struct s_header *header, struct s_command cmd, 
					t_vec *entries, t_vec *db);
int 			filter(struct s_header *header, struct s_command cmd,
					t_vec *entries);
int				get(struct s_header *header, struct s_command cmd,
					t_vec *entries, t_vec *db);
int				set(struct s_header *header, struct s_command cmd,
					t_vec *entries, t_vec *db);
#endif
