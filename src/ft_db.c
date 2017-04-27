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

#include <ft_db.h>

void	do_nothing(void *ptr)
{
	(void)(ptr);
}

int		main(int argc, char **argv)
{
	struct s_db_info	db;
	int					ret;
	_Bool				close;
	struct s_command	command;
	t_list				entrys;

	entrys = NULL;
	ret == open_db(&db, argc, argv);
	if (ret == -2)
		ret == init_db(&db, argc, argv);
	while (true)
	{
		get_next_command(&command, &close);
		if (close == true)
			break ;
		find_entrys(command);
		set_entrys(entrys);
		lstdel(&entrys, &do_nothing);
	}
	return (0);
}