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
** TODO: say when get returns nothing
** TODO: GETALL function -> added function, untested and needs to be added to get next command
** TODO: add default save loc
** TODO: reject duplicate field names
**
** BUG: vec_add does resize properly (breaks when adding 5th element)
*/

char	*g_error;

static void		print_error(void)
{
	if (g_error)
		dprintf(STDERR_FILENO, "ERROR: %s\n", g_error);
	else
		perror("ERROR");
}

static int		manip_db(struct s_header *header, t_vec *db)
{
	struct s_command	command;
	t_vec				held_entries;
	int					ret;

	ret = 0;
	if (-1 == vec_init(&held_entries, sizeof(void*)))
	{
		print_error();
		return (-1);
	}
	while (true)
	{
		if (-1 == get_next_command(&command, header)
			|| -1 == execute_command(header, command, &held_entries, db)
			|| -1 == print_entries(header->entry_size, &held_entries))
		{
			ret = 1;
			break ;
		}
		if (command.type == CLOSE)
			break ;
		//ft_memdel(command.value);
	}
	vec_del(&held_entries);
	free(command.value);
	return (ret);
}

int				main(int argc, char **argv)
{
	struct s_header		header;
	t_vec				db;
	int					ret;

	g_error = NULL;
	ret = 0;
	if (-1 == load_db(&header, &db, argc, argv)
		|| -1 == manip_db(&header, &db)
		|| -1 == save_db(&header, &db, argc, argv))
	{
		print_error();
		ret = 1;
	}
	vec_del(&db);
	free(header.fields);
	return (ret);
}
