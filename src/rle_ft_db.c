/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rle_ft_db.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rle <rle@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/04 18:52:02 by mburson           #+#    #+#             */
/*   Updated: 2017/04/30 13:23:00 by rle              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_db.h>
#include <stdio.h>

void	do_nothing(void *ptr)
{
	(void)(ptr);
}

int open_db(t_db_info *db, int argc, char **argv)
{
	/*
		program takes one argument on init
		./program filename
	*/
	if (argc != 2)
	{
		printf("Invalid number of arguments\n");
		exit(1);
	}
	if (!(db->fd = open(argv[1], O_RDWR)))
		return (-2);
	else
	{
		open(argv[1], O_CREAT);
		(db->fd = open(argv[1], O_RDWR));
	}
	return (1);
}

int	init_db(t_db_info *db, int argc, char **argv)
{
	ft_putstr_fd("wef", db->fd);
	return (1);
}

int		main(int argc, char **argv)
{
	t_db_info			db;
	int					ret;
	_Bool				close;
	t_command			command;
	//t_list				entrys;

	ret = open_db(&db, argc, argv);
	//if (ret == -2)
	ret = init_db(&db, argc, argv);
	if (get_next_command(&command, &close))
	printf("field: %s find: %i set: %i\n", command.field, command.find, command.set);
	/*while (true)
	{
		get_next_command(&command, &close);
		if (close == true)
			break ;
		find_entrys(command);
		set_entrys(entrys);
		lstdel(&entrys, &do_nothing);
	}*/
	return (0);
}