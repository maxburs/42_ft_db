/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_type.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rle <rle@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/05 22:07:49 by rle               #+#    #+#             */
/*   Updated: 2017/05/05 23:09:36 by rle              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_db.h>

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
	if (compare_string(line, "DELETE"))
		command->type = DELETE;
	if (compare_string(line, "FILTER"))
		command->type = FILTER;
	if (compare_string(line, "GETALL"))
		command->type = GETALL;
	if (compare_string(line, "DROP"))
		command->type = DROP;
	if (command->type == NONE)
		return (0);
	return (1);
}
