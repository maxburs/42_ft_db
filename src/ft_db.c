/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_db.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rle <rle@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/04 18:52:02 by mburson           #+#    #+#             */
/*   Updated: 2017/05/04 15:01:54 by rle              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_db.h>

/*
** BUG: SET is busted add is broken?
** TODO: say when get returns nothing
** TODO: don't add duplicates to the held_entries
** TODO: GETALL function
** TODO: add default save loc
** TODO: reject duplicate field names
** TODO: Broken filter/vec_get
** BUG: after filter held_entries element count is off
*/

char	*g_error;

static void		print_error(void)
{
	if (g_error)
		dprintf(STDERR_FILENO, "ERROR: %s\n", g_error);
	else
		perror("ERROR");
}

int				main(int argc, char **argv)
{
	struct s_header		header;
	struct s_command	command;
	t_vec				db;
	t_vec				held_entries;

	g_error = NULL;
	if (-1 == load_db(&header, &db, argc, argv)
		|| vec_init(&held_entries, sizeof(void*)))
	{
		print_error();
		return (1);
	}
	while (true)
	{
		if (-1 == get_next_command(&command, &header))
		{
			print_error();
			break ;
		}
		if (command.type == CLOSE)
			break ;
		if (-1 == execute_command(&header, command, &held_entries, &db)
			|| -1 == print_entries(header.entry_size, &held_entries))
		{
			print_error();
			vec_del(&db);
			vec_del(&held_entries);
			free(header.fields);
			return (1);
		}
		//ft_memdel(command.value);
	}
	if (-1 == save_db(&header, &db, argc, argv))
	{
		print_error();
		return (1);
	}
	free(command.value);
	vec_del(&db);
	vec_del(&held_entries);
	free(header.fields);
	return (0);
}
