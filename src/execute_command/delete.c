/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rle <rle@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/03 15:03:52 by rle               #+#    #+#             */
/*   Updated: 2017/05/03 15:13:33 by rle              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_db.h>

_Bool	swap(uint8_t **first, uint8_t **second)
{
	uint8_t		*swap;

	if (*first < *second)
	{
		swap = *first;
		*first = *second;
		*second = swap;
		return (true);
	}
	else
		return (false);
}

void	entries_reverse_sort(t_vec *entries)
{
	size_t		i;
	_Bool		made_change;

	made_change = true;
	while (made_change)
	{
		made_change = false;
		i = 0;
		while (i + 1 < entries->elmnt_count)
		{
			made_change = made_change \
				|| swap(vec_get(entries, i), vec_get(entries, i + 1));
			i++;
		}
	}
}

int		delete(struct s_header *header, struct s_command cmd,
					t_vec *entries, t_vec *db)
{
	size_t	i;
	size_t	j;
	uint8_t	*entry;

	(void)(db);
	entries_reverse_sort(entries);
	i = 0;
	while (i < entries->elmnt_count)
	{
		entry = *(uint8_t**)vec_get(entries, i);
		j = (entry - db->data) / db->elmnt_size;
		vec_rm(db, j);
		i++;
	}
	clear(header, cmd, entries, db);
	return (0);
}
