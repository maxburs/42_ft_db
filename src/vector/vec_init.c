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
#include <string.h>

int			vec_init(t_vec *vector, size_t elmnt_size)
{
	if (NULL == (vector->data = malloc(elmnt_size * VECTOR_INITIAL_SIZE)))
		return (-1);
	vector->elmnt_size = elmnt_size;
	vector->elmnt_count = 0;
	vector->elmnt_max = elmnt_size * VECTOR_INITIAL_SIZE;
	vector->data_end = vector->data;
	return (0);
}