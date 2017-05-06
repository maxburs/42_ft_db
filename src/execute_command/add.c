/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rle <rle@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/03 15:03:52 by rle               #+#    #+#             */
/*   Updated: 2017/05/05 22:39:59 by rle              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_db.h>

static void		repoint(t_vec *entries, t_vec *db, uint8_t *old_data)
{
	uint8_t		**entry;

	entry = (uint8_t**)entries->data;
	while (entry < (uint8_t**)entries->data_end)
	{
		*entry = vec_get(db, (*entry - old_data) / db->elmnt_size);
		entry++;
	}
	entries->data_end = (void*)entry;
}

int				add(struct s_header *header, struct s_command *cmd,
				t_vec *entries, t_vec *db)
{
	uint8_t		*entry;

	if (db->elmnt_count == db->elmnt_max)
	{
		entry = db->data;
		if (-1 == vec_realloc(db, db->elmnt_max * VECTOR_INCREASE_RATIO))
			return (-1);
		repoint(entries, db, entry);
	}
	entry = vec_get(db, db->elmnt_count);
	db->elmnt_count++;
	db->data_end = (uint8_t*)db->data_end + db->elmnt_size;
	bzero(entry, header->entry_size);
	memcpy(entry + header->fields[cmd->field].offset,
		cmd->value, header->fields[cmd->field].value_size);
	if (-1 == vec_add(entries, &entry))
		return (-1);
	return (0);
}
