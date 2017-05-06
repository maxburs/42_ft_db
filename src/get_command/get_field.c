/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_field.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rle <rle@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/05 22:03:40 by rle               #+#    #+#             */
/*   Updated: 2017/05/05 22:17:57 by rle              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_db.h>

int			compare_string(char *big, char *little)
{
	int i;

	i = 0;
	while (big[i] && little[i] && (big[i] == little[i]))
		i++;
	if (!little[i])
		return (1);
	return (0);
}

static char	*cpy_head_name(char *name, int size)
{
	int		i;
	char	*tmp;

	tmp = (char *)malloc(sizeof(char) * size + 1);
	i = 0;
	while (i < size)
	{
		tmp[i] = name[i];
		i++;
	}
	tmp[i] = '\0';
	return (tmp);
}

static	int	get_name(struct s_header *header, uint64_t *field_type, char *field)
{
	char		*tmp;
	uint64_t	i;

	i = -1;
	while (++i < header->field_count)
	{
		tmp = cpy_head_name(header->fields[i].name, \
			header->fields[i].name_size);
		if (compare_string(tmp, field))
		{
			*field_type = i;
			free(field);
			free(tmp);
			return (0);
		}
		free(tmp);
	}
	free(field);
	return (-1);
}

int			get_field(char *line, struct s_header *header, uint64_t *field_type)
{
	uint64_t	i;
	int			j;
	char		*field;

	j = 0;
	i = 0;
	while (line[i] && line[i] != ' ')
		i++;
	if (!line[i++])
		return (-1);
	while (line[i + j] && line[i + j] != ':')
		j++;
	if (!line[i + j])
		return (-1);
	field = (char *)malloc(sizeof(char) * j + 1);
	j = 0;
	while (line[i] && line[i] != ':')
		field[j++] = line[i++];
	field[j] = '\0';
	i = -1;
	return (get_name(header, field_type, field));
}
