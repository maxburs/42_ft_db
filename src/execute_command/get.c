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

int	get(struct s_header *header, struct s_command cmd,
				t_vec *entries, t_vec *db)
{
	size_t	i;
	uint8_t	*entry;

	i = 0;
	while (i < db->elmnt_count)
	{
		entry = vec_get(db, i);
		if (0 == memcmp(entry + header->fields[cmd.field].offset,
			cmd.value, header->fields[cmd.field].value_size))
		{
			if (-1 == vec_add(entries, &entry))
				return (-1);
		}
		i++;
	}
	return (0);
}