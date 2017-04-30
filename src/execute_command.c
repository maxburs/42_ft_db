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

static int	get(struct s_header *header,
				struct s_command cmd, t_vec *entries, t_vec *db)
{
	size_t	i;
	uint8_t	*entry;

	entries->elmnt_count = 0;
	while (i < db->elmnt_count)
	{
		entry = vec_get(db, i);
		if (0 == ft_memcmp(entry + header->fields[cmd.field].offset,
			cmd.value, header->fields[cmd.field].value_size))
		{
			if (-1 == vec_add(entries, &entry))
				return (-1);
			write(1, entry, header->entry_size);
			write(1, "\n", 1);
		}
		i++;
	}
	return (0);
}

int			execute_command(struct s_header *header,
				struct s_command command, t_vec *entries, t_vec *db)
{
	if (command.type != GET)
		return (-1);
	if (-1 == get(header, command, entries, db))
		return (-1);
	return (0);
}