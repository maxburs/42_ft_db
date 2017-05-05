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
**
** is casting ssize_t to size_t bad??
*/

static int	save_header(struct s_header *header, int fd)
{
	ssize_t		size;

	if (-1 == (size = write(fd, header, sizeof(*header))))
		return (-1);
	if (size != sizeof(*header))
	{
		g_error = "not everything got written\?\?";
		return (-1);
	}
	return (0);
}

static int	save_header_fields(struct s_header *header, int fd)
{
	ssize_t		size;
	size_t		i;

	if (-1 == (size = write(fd, header->fields,
		sizeof(*header->fields) * header->field_count)))
		return (-1);
	if ((size_t)size != sizeof(*header->fields) * header->field_count)
	{
		g_error = "not everything got written\?\?";
		return (-1);
	}
	i = 0;
	while (i < header->field_count)
	{
		size = write(fd, header->fields[i].name, header->fields[i].name_size);
		if (size == -1)
			return (-1);
		if ((size_t)size != header->fields[i].name_size)
		{
			g_error = "not everything got written\?\?";
			return (-1);
		}
		i++;
	}
	return (0);
}

static int	save_database(t_vec *db, int fd)
{
	ssize_t		size;

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
	return (0);
}

int			save_db(struct s_header *header, t_vec *db, int argc, char **argv)
{
	int			fd;
	char		*file;

	if (argc == 1)
		file = DEFAULT_FILE;
	else if (argc == 2)
		file = argv[1];
	else if (argc > 2)
	{
		g_error = "bad useage in save (how did this even happen\?\?)";
		return (-1);
	}
	if (-1 == (fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0666))
		|| -1 == save_header(header, fd)
		|| -1 == save_header_fields(header, fd)
		|| -1 == save_database(db, fd)
		|| -1 == close(fd))
		return (-1);
	return (0);
}
