/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_entries.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rle <rle@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/04 18:52:02 by mburson           #+#    #+#             */
/*   Updated: 2017/05/05 14:03:48 by rle              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_db.h>

static int	print_entry(struct s_header *header, uint8_t *entry)
{
	size_t	i;

	i = 0;
	while (i < header->field_count)
	{
		write(1, header->fields[i].name, header->fields[i].name_size);
		write(1, ":", 1);
		write(1, entry + (i * header->fields[i].value_size),
			header->fields[i].value_size);
		write(1, "  ", 2);
		i++;
	}
	write(1, "\n", 1);
	return (0);
}

int			print_entries(struct s_header *header, t_vec *entries)
{
	size_t		i;

	write(1, "\n", 1);
	i = 0;
	while (i < entries->elmnt_count)
	{
		print_entry(header, *(uint8_t**)vec_get(entries, i));
		i++;
	}
	if (i == 0)
		write(1, "(nothing held)\n", 15);
	write(1, "\n", 1);
	return (0);
}
