/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rle <rle@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/04 18:52:02 by mburson           #+#    #+#             */
/*   Updated: 2017/05/03 15:23:39 by rle              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_db.h>

int			execute_command(struct s_header *header,
				struct s_command command, t_vec *entries, t_vec *db)
{
	if (command.type == GET)
		return (get(header, command, entries, db));
	else if (command.type == CLEAR)
		return (clear(header, command, entries, db));
	else if (command.type == SET)
		return (set(header, command, entries, db));
	else if (command.type == ADD)
		return (add(header, command, entries, db));
	else if(command.type == DELETE)
		return (delete(header, command, entries, db));
	else if (command.type == FILTER)
		return (filter(header, command, entries));
	else
	{
		g_error = "ERROR: bad command type\n";
		return (-1);
	}
}
