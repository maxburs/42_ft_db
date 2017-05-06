/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rle <rle@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/03 15:03:52 by rle               #+#    #+#             */
/*   Updated: 2017/05/03 15:15:33 by rle              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_db.h>

int		getall(struct s_header *header, struct s_command *cmd,
			t_vec *entries, t_vec *db)
{
	size_t		i;
	uint8_t		*entry;

	(void)(header);
	(void)(cmd);
	free(entries->data);
	entries->elmnt_count = db->elmnt_count;
	entries->elmnt_max = db->elmnt_max;
	entries->data = malloc(entries->elmnt_count * entries->elmnt_size);
	if (NULL == entries->data)
		return (-1);
	entries->data_end = (uint8_t*)entries->data
		+ (entries->elmnt_count * entries->elmnt_size);
	i = 0;
	while (i < db->elmnt_count)
	{
		entry = vec_get(db, i);
		vec_set(entries, i, &entry);
		i++;
	}
	return (0);
}
