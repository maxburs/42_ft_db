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

int delete(struct s_header *header, struct s_command cmd, 
					t_vec *entries, t_vec *db)
{
	size_t	i;
	size_t	j;
	uint8_t	*entry;

	(void)(db);
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