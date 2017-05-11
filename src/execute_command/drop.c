/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rle <rle@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/05 23:13:06 by rle               #+#    #+#             */
/*   Updated: 2017/05/05 23:26:47 by rle              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_db.h>

int			drop(struct s_header *header,
				struct s_command *cmd, t_vec *entries, t_vec *db)
{
	uint8_t		*entry;
	size_t		i;

	(void)db;
	i = 0;
	while (i < entries->elmnt_count)
	{
		entry = *(uint8_t**)vec_get(entries, i);
		if (0 == memcmp(entry + header->fields[cmd->field].offset,
			cmd->value, header->fields[cmd->field].value_size))
			vec_rm(entries, i);
		else
			i++;
	}
	return (0);
}
