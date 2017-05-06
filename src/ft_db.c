/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_db.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rle <rle@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/04 18:52:02 by mburson           #+#    #+#             */
/*   Updated: 2017/05/04 22:43:51 by rle              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_db.h>

/*
** TODO: Let user know if db is loading or initializing
**
** BUG: right now the default db save will overwrite the last one,
**     need to generage new name if deafult exists (db, db(1), db(2), ...)
**
** BUG: shit hits the fan when we delete
*/

char	*g_error;

static void		print_error(void)
{
	if (g_error)
		dprintf(STDERR_FILENO, "ERROR: %s\n", g_error);
	else
		perror("ERROR");
}

static int		manip_loop(struct s_header *header, t_vec *db,
					struct s_command *command, t_vec *held_entries)
{
	while (true)
	{
		if (DEBUG)
			debug_print(header, db, command, held_entries);
		if ((-1 == get_next_command(command, header))
			|| -1 == execute_command(header, command, held_entries, db))
		{
			return (1);
		}
		if (command->type == CLOSE)
			return (0);
		if (-1 == print_entries(header, held_entries))
		{
			return (1);
		}
		ft_memdel(&command->value);
	}
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
	ret = manip_loop(header, db, &command, &held_entries);
	vec_del(&held_entries);
	free(command.value);
	return (ret);
}

void			free_header(struct s_header *header)
{
	size_t	i;

	i = 0;
	while (i < header->field_count)
	{
		free(header->fields[i].name);
		i++;
	}
	free(header->fields);
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
	free_header(&header);
	return (ret);
}
