/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rle <rle@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/22 13:30:02 by rle               #+#    #+#             */
/*   Updated: 2017/04/30 16:51:34 by rle              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_db.h>

#define BUFF_SIZE 64

int		get_next_line(char **next_line)
{
	t_lstr	*line;
	int		ret;
	char	buff[BUFF_SIZE + 1];
	char	*swap;

	line = NULL;
	while (true)
	{
		if (-1 == (ret = read(0, buff, BUFF_SIZE)))
		{
			free(lstr_finish);
			return (-1);
		}
		buff[ret] = '\0';
		lstr_add(&line, ft_strdup(buff), false);
		if (ret == 0 || ft_strchr(buff, '\n'))
			break ;
	}
	swap = lstr_finish(&line);
	if (NULL == (*next_line = ft_strndup(swap, ft_strchr(swap, '\n') - swap)))
		return (-1);
	free(swap);
	return (0);
}
