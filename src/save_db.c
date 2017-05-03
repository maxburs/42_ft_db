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

/*
** db format:
** header
** fields
** names
** db struct
** db data
*/

int				save_db(struct s_header *header, t_vec *db, int argc,
					char **argv)
{
	int			fd;
	ssize_t		size;
	size_t		i;

	if (argc == 1)
		return (0);
	if (argc > 2)
	{
		g_error = "bad useage in save (how did this even happen\?\?)";
		return (-1);
	}
	if (-1 == (fd = open(argv[1], O_WRONLY | O_CREAT | O_TRUNC)))
		return (-1);

	if (-1 == (size = write(fd, header, sizeof(*header))))
		return (-1);
	if (size != sizeof(*header))
	{
		g_error = "not everything got written\?\?";
		return (-1);
	}

	if (-1 == (size = write(fd, header->fields, sizeof(*header->fields) * header->field_count)))
		return (-1);
	//TODO: is this cast bad? how should I do this?
	if ((size_t)size != sizeof(*header->fields) * header->field_count)
	{
		g_error = "not everything got written\?\?";
		return (-1);
	}

	i = 0;
	while (i < header->field_count)
	{
		if (-1 == (size = write(fd, header->fields[i].name, header->fields[i].name_size)))
			return (-1);
		if ((size_t)size != header->fields[i].name_size)
		{
			g_error = "not everything got written\?\?";
			return (-1);
		}
		i++;
	}

	if (-1 == (size = write(fd, db, sizeof(*db))))
		return (-1);
	if (size != sizeof(*db))
	{
		g_error = "not everything got written\?\?";
		return (-1);
	}

	if (-1 == (size = write(fd, db->data, db->elmnt_count * db->elmnt_size)))
		return (-1);
	if ((size_t)size != db->elmnt_count * db->elmnt_size)
	{
		g_error = "not everything got written\?\?";
		return (-1);
	}

	return (close(fd));
}
