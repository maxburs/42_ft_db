/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsmith <zsmith@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/04 18:52:02 by mburson           #+#    #+#             */
/*   Updated: 2017/04/05 13:46:56 by zsmith           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_db.h>

/*
** TODO: add commands SET and ADD
** TODO: let user initialize database (right now starts with fields i picked and a db i made)
** TODO: save database in file and load from file
** TODO: decide on error handling scheme
*/

int		main(int argc, char **argv)
{
	struct s_header		header;
	struct s_command	command;
	t_vec				db; //will become fd?
	t_vec				entries;

	if (-1 == load_db(&header, &db, argc, argv))
		return (1);
	//because db is currently just in memory 'entries' just points to the entries that are found, will contain complete entries later
	vec_init(&entries, sizeof(void*));
	while (true)
	{
		command.type = GET;
		command.field = 0;
		command.value = "foo\0\0";
		if (/*-1 == get_next_command(&header, &command)
			|| */command.type == CLOSE
			|| -1 == execute_command(&header, command, &entries, &db))
			break ;
		print_entries(header.entry_size, &entries);
		break ;
	}
	vec_del(&db);
	vec_del(&entries);
	free(header.fields);
	return (0);
}
