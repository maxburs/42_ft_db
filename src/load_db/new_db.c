/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_db.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rle <rle@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/04 18:52:02 by mburson           #+#    #+#             */
/*   Updated: 2017/05/04 22:07:50 by rle              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_db.h>

#define VALUE_SIZE	100

static int get_head_count(struct s_header *header)
{
	int n;
	char *line;

	write(1, "How many fields?\n", 17);
	get_next_line(&line);
	n = ft_atoi(line);
	free(line);
	while (n < 1)
	{
		write(1, "Fields must be greater than 0\n", 30);
		get_next_line(&line);
		n = ft_atoi(line);
		free(line);
	}
	header->field_count = n;
	if (NULL == (header->fields = malloc(sizeof(*header->fields) * n)))
		return (-1);
	return (0);
}

int			new_db(struct s_header *header, t_vec *db)
{
	int i;
	int j;
	int value_size;
	char *line;

	i = 0;
	if (-1 == get_head_count(header))
		return (-1);
	header->entry_size = 0;
	while (i < (int)header->field_count)
	{
		printf("Field %i?\n", i + 1);
		get_next_line(&line);
		j = 0;	
		while (j < i)
		{
			if (0 == ft_strcmp(header->fields[j].name, line))
			{
				free(line);
				write(1, "Field already exists\n", 21);
			}
			get_next_line(&line);
			j++;
		}
		header->fields[i].name = line;
		header->fields[i].name_size = ft_strlen(header->fields[i].name);
		puts("Value size?");
		get_next_line(&line);
		value_size = ft_atoi(line);
		free(line);
		while (value_size < 0)
		{
			write(1, "Value size must be 0 or greater\n", 32);
			get_next_line(&line);
			value_size = ft_atoi(line);
			free(line);
		}
		if (i == 0)
			header->fields[i].offset = 0;
		else
			header->fields[i].offset = header->fields[i - 1].offset + value_size;
		header->fields[i].value_size = value_size;
		header->entry_size += value_size;
		i++;
	}
	vec_init(db, header->entry_size);
	return (0);
}