/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_command.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rle <rle@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/28 14:04:53 by rle               #+#    #+#             */
/*   Updated: 2017/04/28 16:06:03 by rle              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_db.h"

int valid_command(char *line, _Bool *close, int i)
{
	if (line[i] == 'x' || line[i] == 'X')
	{
		*close = true;
		return (1);
	}
	if (line[i] != 'G' && line[i] != 'S')
		return (0);
	i++;
	if (line[i++] != ' ')
		return (0);
	while (line[i] && line[i] != ':')
		i++;
	if (!line[i])
		return (1);
	if (line[i++] != ':')
		return (0);
	while (line[i] && ft_isdigit(line[i]))
		i++;
	if (!line[i] && line[0] == 'G')
		return (1);
	if (line[i++] != ' ')
		return (0);
	while (line[i] && ft_isdigit(line[i]))
		i++;
	if (!line[i])
		return (1);
	return (0);
}

void	get_field_find(t_command *command, char *line)
{
	int j;
	int i;

	i = 2;
	j = 0;
	while (line[i] && line[i] != ':')
	{
		command->field[j] = line[i];
		i++;
		j++;
	}
	command->field[j] = '\0';
	if (!line[i])
		return ;
	i++;
	while (line[i] && ft_isdigit(line[i]))
	{
		command->find *= 10;
		command->find += line[i] - '0';
		i++;
	}
}

void	get_set(t_command *command, char *line)
{
	int i;
	int j;

	j = 0;
	i = 2;
	while (line[i] && line[i] != ' ')
		i++;
	if (!line[i])
		return ;
	i++;
	while (line[i])
	{
		command->set *= 10;
		command->set += line[i] - '0';
		i++;
	}
}
void	parse_command(t_command *command, char *line)
{
	int i;
	int j;

	i = 0;
	command->option = line[i];
	while (line[i] && line[i] != ':')
		i++;
	command->field = (char *)malloc(sizeof(char) * (j - i + 1));
	get_field_find(command, line);
	if (command->option == 'S')
		get_set(command, line);
}

int	get_next_command(t_command *command, _Bool *close)
{
	char *line;
	int i;
	int j;
	char option;

	i = 0;
	j = 0;
	command->find = 0;
	command->set = 0;
	get_next_line(0, &line);
	if (valid_command(line, close, 0))
	{
		if (*close)
			return (0);
		parse_command(command, line);
		return (1);
	}
	else
		printf("invalid command\n");
	return (0);
}
