/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_command.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rle <rle@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/28 14:04:53 by rle               #+#    #+#             */
/*   Updated: 2017/05/05 22:17:46 by rle              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_db.h"

static int	parse_commmand(char *line, struct
				s_command *command, struct s_header *header)
{
	if (get_command_type(line, command))
	{
		if (command->type == CLOSE || command->type == CLEAR \
			|| command->type == DELETE || command->type == GETALL)
			return (1);
		else if (-1 == get_field(line, header, &command->field))
		{
			write(1, "Invalid field\n", 14);
			return (0);
		}
		else if (value_size(line) > header->fields[command->field].value_size)
		{
			write(1, "Value size is too large\n", 24);
			return (0);
		}
		else if (!get_value(line, command, header))
			return (0);
		return (1);
	}
	return (0);
}

int			get_next_command(struct s_command *command, struct s_header *header)
{
	char	*line;
	int		ret;

	ret = 0;
	ft_bzero(command, sizeof(*command));
	while (command->type == NONE && ret != 1)
	{
		if (-1 == get_next_line(&line))
			break ;
		ret = parse_commmand(line, command, header);
		free(line);
		if (ret == -1)
			break ;
	}
	return (ret);
}
