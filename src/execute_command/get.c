/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rle <rle@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/03 15:04:35 by rle               #+#    #+#             */
/*   Updated: 2017/05/03 15:13:35 by rle              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_db.h>

static _Bool	already_held(t_vec *held_entries, uint8_t *entry)
{
	uint8_t		**held;

	held = (uint8_t**)held_entries->data;
	while (held < (uint8_t**)held_entries->data_end)
	{
		if (*held == entry)
			return (true);
		held++;
	}
	return (false);
}

int				get(struct s_header *header, struct s_command cmd,
				t_vec *entries, t_vec *db)
{
	size_t	i;
	uint8_t	*entry;

	i = 0;
	while (i < db->elmnt_count)
	{
		entry = vec_get(db, i);
		if (0 == memcmp(entry + header->fields[cmd.field].offset,
			cmd.value, header->fields[cmd.field].value_size)
			&& !already_held(entries, entry))
		{
			if (-1 == vec_add(entries, &entry))
				return (-1);
		}
		i++;
	}
	return (0);
}
