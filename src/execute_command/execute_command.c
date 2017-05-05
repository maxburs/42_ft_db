/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rle <rle@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/04 18:52:02 by mburson           #+#    #+#             */
/*   Updated: 2017/05/04 14:49:22 by rle              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_db.h>

static int	none(struct s_header *header, struct s_command cmd,
					t_vec *entries, t_vec *db)
{
	(void)(header);
	(void)(cmd);
	(void)(entries);
	(void)(db);
	return (0);
}

static int	(*const g_commands[])(struct s_header *header, struct s_command cmd,
				t_vec *entries, t_vec *db) =
{
	&none,
	&none,
	&get,
	&set,
	&add,
	&delete,
	&filter,
	&getall,
	&clear
};

int			execute_command(struct s_header *header,
				struct s_command command, t_vec *entries, t_vec *db)
{
	if (command.type < COMMAND_COUNT)
		return (g_commands[command.type](header, command, entries, db));
	else
	{
		g_error = "ERROR: bad command type\n";
		return (-1);
	}
}
