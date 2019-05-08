/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fts_check_args.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agimet <agimet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/19 14:49:53 by agimet            #+#    #+#             */
/*   Updated: 2019/05/08 14:39:36 by agimet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int				ft_check_dump_param(t_all *a, char **av)
{
	int			i;

	i = -1;
	if (av[1] && av[1][0] == '-' && av[1][1] == 'd'
		&& av[1][2] == 'u' && av[1][3] == 'm' && av[1][4] == 'p')
	{
		if (av[1][5])
			return (ft_error("Wrong -dump param."));
		while (av[2] && av[2][++i])
		{
			if (av[2][i] && (av[2][i] == '-'
				|| (av[2][i] < '0' || av[2][i] > '9')))
				return (ft_error("Need number with -dump param."));
		}
		if (av[2])
		{
			a->dump_cycle = ft_atoi(av[2]);
			a->dump_param = 1;
		}
		else
			return (ft_error("Missing dump cycle."));
	}
	return (1);
}

int				ft_check_available_num(t_player pl[MAX_PLAYERS], int which_pl)
{
	int			i;

	i = 0;
	while (i < MAX_PLAYERS)
	{
		if (i != which_pl && pl[which_pl].num_player == pl[i].num_player)
			return (ft_error("Same number used twice with -n param."));
		i++;
	}
	return (1);
}

int				ft_check_num_players(t_all *a, char **av, int *i)
{
	int			j;
	static int	num = 0;

	j = 0;
	if (av[*i] && av[*i][0] == '-' && av[*i][1] == 'n')
	{
		if (av[*i][2] || !av[*i + 1] || !av[*i + 2])
			return (ft_error("Wrong -n param."));
		while (av[*i + 1][j])
		{
			if (av[*i + 1][j] < '0' || av[*i + 1][j] > '0')
				return (ft_error("Need number between 1 and 4 with -n param."));
			j++;
		}
		a->pl[num].num_player = ft_atoi(av[*i + 1]);
		if (a->pl[num].num_player > 4 || a->pl[num].num_player < 0)
			return (ft_error("-n param goes from 1 to 4."));
		if (!ft_check_available_num(a->pl, num))
			return (0);
		num++;
		a->num_param += 1;
		*i += 2;
	}
	return (1);
}

int				ft_valib_nb_players(t_all *a)
{
	int			i;

	i = 0;
	if (a->nb_pl == 0)
		return (ft_error("Missing player."));
	if (a->nb_pl == 1)
		return (ft_error("Not funny to play alone."));
	if (a->nb_pl > 4)
		return (ft_error("Too much players"));
	while (i < a->nb_pl)
	{
		if (a->pl[i++].num_player > a->nb_pl)
			return (ft_error("No logic in -n param."));
	}
	return (1);
}

int				ft_valid_args(t_all *a, char **av, int ac)
{
	int			len;
	int			i;

	i = 1;
	len = 0;
	if (!ft_check_dump_param(a, av))
		return (0);
	a->dump_param == 1 ? (i += 2) : (0);
	while (i < ac)
	{
		if (!ft_check_num_players(a, av, &i))
			return (0);
		len = ft_strlen(av[i]);
		if (len < 5 || av[i][len - 4] != '.' || av[i][len - 3] != 'c'
			|| av[i][len - 2] != 'o' || av[i][len - 1] != 'r')
			return (ft_error("Wrong syntax of champion's name."));
		else
			a->nb_pl++;
		i++;
	}
	if (!ft_valib_nb_players(a))
		return (0);
	if (a->num_param != 0 && a->nb_pl != a->num_param)
		return (ft_error("Nb of -n param must be equal to nb players."));
	return (1);
}
