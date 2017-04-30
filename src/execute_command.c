/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsmith <zsmith@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/04 18:52:02 by mburson           #+#    #+#             */
/*   Updated: 2017/04/05 13:46:56 by zsmith           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_db.h>

static int	get(struct s_header *header, struct s_command cmd,
				t_vec *entries, t_vec *db)
{
	size_t	i;
	uint8_t	*entry;

	i = 0;
	while (i < db->elmnt_count)
	{
		entry = vec_get(db, i);
		if (0 == ft_memcmp(entry + header->fields[cmd.field].offset,
			cmd.value, header->fields[cmd.field].value_size))
		{
			if (-1 == vec_add(entries, &entry))
				return (-1);
		}
		i++;
	}
	return (0);
}

static int	clear(struct s_header *header, struct s_command cmd,
				t_vec *entries, t_vec *db)
{
	(void)(header);
	(void)(cmd); //todo: only clear what we've been asked to
	(void)(db);
	entries->elmnt_count = 0;
	if (-1 == vec_realloc(entries, 4))
		return (-1);
	return (0);
}

static int	set(struct s_header *header, struct s_command cmd,
				t_vec *entries, t_vec *db)
{
	size_t	i;
	uint8_t	*entry;

	i = 0;
	while (i < db->elmnt_count)
	{
		entry = *(uint8_t**)vec_get(entries, i);
		ft_memcpy(entry + header->fields[cmd.field].offset,
			cmd.value, header->fields[cmd.field].value_size);
		i++;
	}
	return (0);
}

static int	add(struct s_header *header, struct s_command cmd,
				t_vec *entries, t_vec *db)
{
	uint8_t		*entry;

	if (db->elmnt_count == db->elmnt_max)
	{
		if (-1 == vec_realloc(db, db->elmnt_max * VECTOR_INCREASE_RATIO))
		return (-1);
	}
	db->elmnt_count++;
	entry = vec_get(db, entries->elmnt_count - 1);
	ft_bzero(entry, header->entry_size);
	ft_memcpy(entry + header->fields[cmd.field].offset,
		cmd.value, header->fields[cmd.field].value_size);
	if (-1 == vec_add(entries, &entry))
		return (-1);
	return (0);
}

int			execute_command(struct s_header *header,
				struct s_command command, t_vec *entries, t_vec *db)
{
	if (command.type == GET)
		return get(header, command, entries, db);
	else if (command.type == CLEAR)
		return clear(header, command, entries, db);
	else if (command.type == SET)
		return set(header, command, entries, db);
	else if (command.type == SET)
		return add(header, command, entries, db);
	else
	{
		ft_putstr_fd("ERROR: bad command type\n", STDERR_FILENO);
		return (-1);
	}
}
