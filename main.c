/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agimet <agimet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/27 10:40:54 by agimet            #+#    #+#             */
/*   Updated: 2019/05/09 15:28:07 by agimet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int			ft_error(char *str)
{
	ft_putstr_fd(str, 2);
	ft_putstr_fd("\n", 2);
	return (0);
}

int			ft_prototype(int ret)
{
	ft_putstr_fd("./corewar [-dump nb] [-n nb] <champ.cor> -q ...\n", 1);
	ft_putstr_fd("\t\tARGS NEED TO BE USED IN THE PROTOTYPE'S ORDER.\n", 1);
	ft_putstr_fd("\t\t-n : Need to be set to each player, from 1 to 4.\n", 1);
	ft_putstr_fd("\t\t-dump : To use before champions' name.\n", 1);
	ft_putstr_fd("\t\t-q : To use at the end of args.\n", 1);
	return (ret);
}

int			ft_quiet_mode(t_all *a, int *ac, char **av)
{
	if (av[*ac - 1][0] && av[*ac - 1][0] == '-' && av[*ac - 1][1]
		&& av[*ac - 1][1] == 'q')
	{
		if (av[*ac - 1][2])
			return (ft_error("Wrong quiet mode param."));
		a->quiet = 1;
		(*ac)--;
	}
	return (1);
}

int			main(int ac, char **av)
{
	int		fd;
	t_all	*a;

	a = NULL;
	fd = 0;
	if (ac == 1)
		return (ft_prototype(0));
	ft_init_struct(&a);
	if (a == NULL)
		(ft_error("Malloc NULL."));
	if (!ft_quiet_mode(a, &ac, av))
		return (ft_free_all(a));
	if (!ft_valid_args(a, av, ac))
		return (ft_free_all(a));
	if (!ft_read(a, fd, av))
		return (ft_free_all(a));
	ft_init_arena(a);
	ft_lets_play(a);
	ft_free_all(a);
	return (0);
}
