/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_command.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rle <rle@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/28 14:04:53 by rle               #+#    #+#             */
/*   Updated: 2017/05/01 14:01:17 by rle              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_db.h"

int		compare_string(char *big, char *little)
{
	int i;

	i = 0;
	while (big[i] && little[i] && (big[i] == little[i]))
		i++;
	if (!little[i])
		return (1);
	return (0);
}

int		get_command_type(char *line, struct s_command *command)
{
	if (compare_string(line, "CLOSE"))
		command->type = CLOSE;
	if (compare_string(line, "GET"))
		command->type = GET;
	if (compare_string(line, "SET"))
		command->type = SET;
	if (compare_string(line, "ADD"))
		command->type = ADD;
	if (compare_string(line, "CLEAR"))
		command->type = CLEAR;
	if (command->type == NONE)
		return (0);
	return (1);
}

int		get_field(char *line, struct s_header *header)
{
	int		i;
	int		j;
	char	*field;

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
	while (++i < (int)header->field_count)
		if (compare_string(header->fields[i].name, field))
			return (i);
	return (-1);
}

int		get_value(char *line, struct s_command *command,
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

/*
	Too large
	Bad command
*/

size_t	value_size(char *line)
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

int		get_next_command(struct s_command *command, struct s_header *header)
{
	char *line;

	ft_bzero(command, sizeof(*command));
	if (-1 == get_next_line(&line))
		return (-1);
	if (get_command_type(line, command))
	{
		if (command->type == CLOSE || command->type == CLEAR)
			return (1);
		if (-1 == (command->field = get_field(line, header)))
		{
			ft_putstr("Invalid field\n");
			return (get_next_command(command, header));
		}
		if (value_size(line) > header->fields[command->field].value_size)
		{
			ft_putstr("Value size is too large\n");
			return (get_next_command(command, header));
		}
		if (!get_value(line, command, header))
			return (-1);
		return (1);
	}
	else
	{
		ft_putstr("Bad Command\n");
		free(line);
		return (get_next_command(command, header));
	}
	return (-1);
}
