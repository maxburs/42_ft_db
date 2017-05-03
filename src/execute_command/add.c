/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rle <rle@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/03 15:03:52 by rle               #+#    #+#             */
/*   Updated: 2017/05/03 15:13:31 by rle              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_db.h>

int	add(struct s_header *header, struct s_command cmd,
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
	bzero(entry, header->entry_size);
	memcpy(entry + header->fields[cmd.field].offset,
		cmd.value, header->fields[cmd.field].value_size);
	if (-1 == vec_add(entries, &entry))
		return (-1);
	return (0);
}