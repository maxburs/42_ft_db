/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_value.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rle <rle@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/05 22:03:03 by rle               #+#    #+#             */
/*   Updated: 2017/05/05 22:15:52 by rle              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_db.h>

int			get_value(char *line, struct s_command *command,
	struct s_header *header)
{
	int i;
	int j;

	j = 0;
	i = 0;
	command->value = (char *)malloc(sizeof(char) * \
		header->fields[command->field].value_size);
	ft_bzero(command->value, header->fields[command->field].value_size);
	while (line[i] && line[i] != ':')
		i++;
	if (!line[i++])
		return (0);
	while (line[i])
	{
		((char *)command->value)[j] = line[i];
		i++;
		j++;
	}
	return (1);
}

uint64_t	value_size(char *line)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (line[i] && line[i] != ':')
		i++;
	if (!line[i++])
		return (-1);
	while (line[i])
	{
		i++;
		j++;
	}
	return (j);
}
