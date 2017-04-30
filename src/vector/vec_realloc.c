/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsmith <zsmith@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/04 18:52:02 by mburson           #+#    #+#             */
/*   Updated: 2017/04/05 13:46:56 by zsmith           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vector.h>
#include <stdlib.h>
#include <libft.h>

int				vec_realloc(t_vec *vec, size_t new_size)
{
	uint8_t		*new_data;

	if (vec->elmnt_max > new_size)
		return (-1);
	if (NULL == (new_data = malloc(vec->elmnt_size * new_size)))
		return (-1);
	ft_memcpy(new_data, vec->data, vec->elmnt_size * vec->elmnt_count);
	free(vec->data);
	vec->elmnt_max = new_size;
	vec->data = new_data;
	vec->data_end = new_data + (vec->elmnt_size * vec->elmnt_count);
	return (0);
}
