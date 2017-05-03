/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filter.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rle <rle@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/03 15:03:52 by rle               #+#    #+#             */
/*   Updated: 2017/05/03 15:20:22 by rle              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_db.h>

int filter(struct s_header *header, struct s_command cmd,
				t_vec *entries)
{
	size_t	i;
	uint8_t	*entry;

	i = 0;
	while (i < entries->elmnt_count)
	{
		entry = *(uint8_t**)vec_get(entries, i);
		if (0 == memcmp(entry + header->fields[cmd.field].offset,
			cmd.value, header->fields[cmd.field].value_size))
			vec_rm(entries, i);
		i++;
	}
	return (0);
}