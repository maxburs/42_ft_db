/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rle <rle@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/03 15:05:23 by rle               #+#    #+#             */
/*   Updated: 2017/05/03 15:13:32 by rle              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_db.h>

int	clear(struct s_header *header, struct s_command cmd,
				t_vec *entries, t_vec *db)
{
	(void)(header);
	(void)(cmd);
	(void)(db);
	entries->elmnt_count = 0;
	if (-1 == vec_realloc(entries, 4))
		return (-1);
	return (0);
}