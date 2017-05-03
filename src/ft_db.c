/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_db.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rle <rle@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/04 18:52:02 by mburson           #+#    #+#             */
/*   Updated: 2017/05/03 15:50:43 by rle              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_db.h>

/*
** BUG: SET is busted add is broken?
** TODO: say when get returns nothing
** TODO: don't add duplicates to the held_entries
** TODO: show all entries function
** TODO: add default save loc
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
		if (-1 == get_next_command(&command, &header)
			|| command.type == CLOSE //change how we handle close
			|| -1 == execute_command(&header, command, &held_entries, &db))
		{
			print_error();
			break ;
		}
		free(command.value);
		print_entries(header.entry_size, &held_entries);
	}
	if (-1 == save_db(&header, &db, argc, argv))
		print_error();
	free(command.value);
	vec_del(&db);
	vec_del(&held_entries);
	free(header.fields);
	return (0);
}
