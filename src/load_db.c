/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_db.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rle <rle@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/04 18:52:02 by mburson           #+#    #+#             */
/*   Updated: 2017/05/01 14:49:17 by rle              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_db.h>

#define VALUE_SIZE	100


static int get_head_count(struct s_header *header, int *value_size)
{
	int n;
	char *line;

	ft_putstr("How many entries?\n");
	get_next_line(&line);
	n = ft_atoi(line);
	header->entry_size = n;

	ft_putstr("How many fields?\n");
	get_next_line(&line);
	n = ft_atoi(line);
	header->field_count = n;
	if (NULL == (header->fields = malloc(sizeof(*header->fields) * n)))
		return (-1);
	ft_putstr("Value size?\n");
	get_next_line(&line);
	*value_size = ft_atoi(line);
	return (0);
}

static int	new_db(struct s_header *header, t_vec *db)
{
	int i;
	int value_size;
	char *line;

	i = 0;
	if (-1 == get_head_count(header, &value_size))
		return (-1);
	while (i < (int)header->field_count)
	{
		ft_putstr("Field ");
		ft_putnbr(i + 1);
		ft_putstr("?\n");
		get_next_line(&line);
		header->fields[i].name = line;
		header->fields[i].name_size = ft_strlen(header->fields[i].name);
		if (i == 0)
			header->fields[i].offset = 0;
		else
			header->fields[i].offset = header->fields[i - 1].offset + value_size;
		header->fields[i].value_size = value_size;
		i++;
	}
	vec_init(db, header->entry_size);
	vec_add(db, "bob\0\0blue\0");
	vec_add(db, "sam\0\0red\0\0");
	vec_add(db, "foo\0\0bar\0\0");
	return (0);
}

int			load_db(struct s_header *header, t_vec *db,
			int argc, char **argv)
{
	(void)(argc);
	(void)(argv);
	new_db(header, db);
	return (0);
}
