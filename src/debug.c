/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_db.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rle <rle@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/04 18:52:02 by mburson           #+#    #+#             */
/*   Updated: 2017/05/04 22:39:55 by rle              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_db.h>

void	debug_header(struct s_header *header)
{
	(void)(header);
}

void	debug_db(t_vec *db)
{
	(void)(db);
}

void	debug_command(struct s_command *command)
{
	(void)(command);
}

void	debug_entries(t_vec *db, t_vec *entries)
{
	size_t		j;
	size_t		i;
	uint8_t		*entry;

	i = 0;
	while (i < entries->elmnt_count)
	{
		entry = *(uint8_t**)vec_get(entries, i);
		j = (entry - db->data) / db->elmnt_size;
		printf("entry: %zu\n", i);
		printf("entry offset: %ju\n", entry - db->data);
		printf("entry fixed offset: %ju\n", j);
		printf("db elmnt size: %ju\n", db->elmnt_size);
		putchar('\n');
		i++;
	}
}

void	debug_print(struct s_header *header, t_vec *db,
					struct s_command *command, t_vec *held_entries)
{
	debug_header(header);
	debug_db(db);
	debug_command(command);
	debug_entries(db, held_entries);
}