/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_db.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rle <rle@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/04 18:52:02 by mburson           #+#    #+#             */
/*   Updated: 2017/05/01 18:20:41 by rle              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_db.h>

static char		*pick_file(int argc, char **argv)
{
	if (argc == 1)
		return (DEFAULT_FILE);
	else if (argc == 2)
		return (argv[1]);
	else
	{
		g_error = "Usage: ft_db: [DATABASE FILE]";
		return (NULL);
	}
}

int				load_db(struct s_header *header, t_vec *db, int argc,
					char **argv)
{
	int		fd;
	char	*file;

	if (NULL == (file = pick_file(argc, argv)))
		return (-1);
	fd = open(file, O_RDONLY);
	if (-1 == fd)
	{
		if (errno == 2)
		{
			errno = 0;
			printf("\e[1mnew db: %s\e[0m\n", file);
			return (new_db(header, db));
		}
		else
			return (-1);
	}
	else
	{
		printf("\e[1mopening: %s\e[0m\n\n", file);
		return (open_db(header, db, fd));
	}
}
