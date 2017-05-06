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

static t_lstr	*next_lstr(void)
{
	t_lstr		*line;
	char		buff[BUFF_SIZE + 1];
	ssize_t		ret;

	line = NULL;
	while (true)
	{
		if (-1 == (ret = read(0, buff, BUFF_SIZE)))
		{
			if (errno == 4)
			{
				errno = 0;
				continue ;
			}
			free(lstr_finish(&line));
			return (NULL);
		}
		buff[ret] = '\0';
		lstr_add(&line, ft_strdup(buff), false);
		if (ret == 0 || ft_strchr(buff, '\n'))
			return (line);
	}
}

int				get_next_line(char **next_line)
{
	t_lstr	*line;
	char	*swap;
	char	*c;

	ft_putstr(INPUT_PROMPT);
	line = next_lstr();
	if (line == NULL)
		return (-1);
	if (NULL == (swap = lstr_finish(&line)))
		return (-1);
	if (NULL == (c = ft_strchr(swap, '\n')))
	{
		*next_line = swap;
	}
	else
	{
		*next_line = ft_strndup(swap, ft_strchr(swap, '\n') - swap);
		free(swap);
		if (NULL == *next_line)
			return (-1);
	}
	return (0);
}
