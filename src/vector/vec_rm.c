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

int				vec_rm(t_vec *vector, size_t index)
{
	ft_memcpy(vector->data + (index * vector->elmnt_size), 
		vector->data + ((index + 1) * vector->elmnt_size),
		(vector->elmnt_count - index) * vector->elmnt_size);
	vector->elmnt_count--;
	if (vector->elmnt_count * VECTOR_DECREASE_RATIO < vector->elmnt_max)
	{
		if (-1 == vec_realloc(vector, VECTOR_INCREASE_RATIO))
			return (-1);
	}
	return (0);
}