/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_db.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rle <rle@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/04 18:52:02 by mburson           #+#    #+#             */
/*   Updated: 2017/04/30 17:22:47 by rle              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_db.h>

/*
** TODO: add commands SET and ADD
** TODO: let user initialize database
**    right now starts with fields i picked and a db i made)
** TODO: save database in file and load from file
** TODO: decide on error handling scheme
** BUG: SET is busted add is broken?
*/

int		main(int argc, char **argv)
{
	struct s_header		header;
	struct s_command	command;
	t_vec				db;
	t_vec				held_entries;

	if (-1 == load_db(&header, &db, argc, argv)
		|| vec_init(&held_entries, sizeof(void*)))
		return (1);
	command.value = NULL;
	while (true)
	{
		if (-1 == get_next_command(&command, &header)
			|| command.type == CLOSE
			|| -1 == execute_command(&header, command, &held_entries, &db))
			break ;
		free(command.value);
		print_entries(header.entry_size, &held_entries);
	}
	free(command.value);
	vec_del(&db);
	vec_del(&held_entries);
	free(header.fields);
	return (0);
}
