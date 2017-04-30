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

#define VALUE_SIZE	100

static int	new_db(struct s_header *header, t_vec *db)
{
	if (NULL == (header->fields = malloc(sizeof *header->fields * 2)))
		return (-1);
	header->entry_size = 10;
	header->field_count = 2;
	header->fields[0].name = "name";
	header->fields[0].name_size = 5;
	header->fields[0].offset = 0;
	header->fields[0].value_size = 5;
	header->fields[0].name = "color";
	header->fields[0].name_size = 6;
	header->fields[0].offset = 5;
	header->fields[0].value_size = 5;
	vec_init(db, header->entry_size);
	vec_add(db, "bob\0\0blue\0");
	vec_add(db, "sam\0\0red\0\0");
	vec_add(db, "foo\0\0bar\0");
	return (0);
}

int		load_db(struct s_header *header, t_vec *db,
			int argc, char **argv)
{
	(void)(argc);
	(void)(argv);
	new_db(header, db);
	return (0);
}