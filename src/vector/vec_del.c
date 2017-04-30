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

void	vec_del(t_vec *vector)
{
	free(vector->data);
	ft_bzero(vector, sizeof(*vector));
}