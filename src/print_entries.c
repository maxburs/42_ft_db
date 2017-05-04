/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_entries.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rle <rle@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/04 18:52:02 by mburson           #+#    #+#             */
/*   Updated: 2017/05/04 14:30:09 by rle              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_db.h>

int		print_entries(size_t entry_size, t_vec *entries)
{
	size_t	i;
	uint8_t	*entry;

	i = 0;
	while (i < entries->elmnt_count)
	{
		entry = *(uint8_t**)vec_get(entries, i);
		if (-1 == write(STDOUT_FILENO, entry, entry_size)
			|| -1 == write(STDOUT_FILENO, "\n", 1))
			return (-1);
		i++;
	}
	return (0);
}
