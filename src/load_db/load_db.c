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

int			load_db(struct s_header *header, t_vec *db, int argc, char **argv)
{
	int		fd;

	if (argc == 1)
		return (new_db(header, db));
	else if (argc == 2)
	{
		fd = open(argv[1], O_RDONLY);
		if (-1 == fd)
		{
			if (errno == 2)
			{
				errno = 0;
				return (new_db(header, db));
			}
			else
				return (-1);
		}
		return (open_db(header, db, fd));
	}
	else
	{
		puts("Usage: ft_db: [DATABASE FILE]");
		return (0);
	}
}
