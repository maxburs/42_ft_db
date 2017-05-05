/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_entries.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rle <rle@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/04 18:52:02 by mburson           #+#    #+#             */
/*   Updated: 2017/05/04 22:44:05 by rle              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_db.h>

int		print_entries(struct s_header *header, t_vec *entries)
{
	size_t		i;
	int			j;
	uint8_t		*entry;

	write(1, "\n", 1);
	i = 0;
	while (i < entries->elmnt_count)
	{
		entry = *(uint8_t**)vec_get(entries, i);
		j = 0;
		while (j < (int)header->field_count)
		{
			write(1, header->fields[j].name, header->fields[j].name_size);
			write(1, ":", 1);
			write(1, entry + (j * header->fields[j].value_size),
				header->fields[j].value_size);
			write(1, "  ", 2);
			j++;
		}
		write(1, "\n", 1);
		i++;
	}
	if (i == 0)
		puts("(nothing held)");
	write(1, "\n", 1);
	return (0);
}
